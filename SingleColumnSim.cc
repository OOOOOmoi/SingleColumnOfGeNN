// #include "/home/yangjinhao/GeNN/userproject/include/spikeRecorder.h"
// #include "/home/yangjinhao/GeNN/userproject/include/timer.h"
// #include "/home/yangjinhao/GeNN/userproject/include/sharedLibraryModel.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "SingleColumn_CODE/definitions.h"
#include <map>
#include <cmath>
#include "time.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <memory>
#include "RecordFunc.h"
#include "DefaultParam.h"
using namespace std;
#define TOTAL_TIME 3000.0f
#define REPORT_TIME 100.0f

int main(){
    const string outDir="/home/yangjinhao/GeNN/userproject/SingleColumn/output";
    const string outDirVoltage="/home/yangjinhao/GeNN/userproject/SingleColumn/output_voltage";
    const string outDirW="/home/yangjinhao/GeNN/userproject/SingleColumn/output_W";
    const string outDirD="/home/yangjinhao/GeNN/userproject/SingleColumn/output_D";
    const string outDirI="/home/yangjinhao/GeNN/userproject/SingleColumn/output_I";
    ofstream FILE_POPLIST("PopList.txt");
    vector<string> NeuronType={"E","S","P","V"};
    vector<string> LayerList={"1","23","4","5","6"};
    string PopList[17];
    PopList[0]="H1";
    int PopNum=1;
    for (auto layer = LayerList.begin()+1; layer != LayerList.end(); layer++){
        for (auto pop = NeuronType.begin(); pop != NeuronType.end(); pop++){
                PopList[PopNum]=*pop+*layer;
                PopNum++;
        }
    }
    map<string, ofstream> outPutsTest;
    for (auto& PopName:PopList){
        string fileName=outDir+"/"+PopName+".st";
        outPutsTest.emplace(PopName,ofstream(fileName));
    }
    vector<ofstream> outPuts;
    for (auto& PopName:PopList){
        string fileName=outDir+"/"+PopName+".st";
        ofstream temp(fileName);
        if (!temp) {
            std::cerr << "Failed to open file. Check the file path!" << std::endl;
        }
        outPuts.emplace_back(ofstream(fileName));
    }
    vector<ofstream> outPutsVoltage;
    for (auto& PopName:PopList){
        string fileName=outDirVoltage+"/"+PopName+".st";
        ofstream temp(fileName);
        if (!temp) {
            std::cerr << "Failed to open file. Check the file path!" << std::endl;
        }
        outPutsVoltage.emplace_back(ofstream(fileName));
    }
    
    struct stat st;
    ifstream FILE_SYNAPSES("/home/yangjinhao/GeNN/userproject/SingleColumn/SynapsesNumber.txt",ios::in);
    map<string,map<string,ofstream>> outPutsW;
    map<string,map<string,ofstream>> outPutsD;
    map<string,map<string,ofstream>> outPutsI;
    string src,tar;
    float synNum;
    string folderDir;
    while(FILE_SYNAPSES>>src>>tar>>synNum){
        folderDir=outDirI+"/"+tar;
        if (stat(folderDir.c_str(), &st) != 0) { // 如果目录不存在
            mkdir(folderDir.c_str(), 0777);      // 创建目录
            std::cout << "Directory created: " << folderDir << std::endl;
        }
        if(synNum!=0.0){
            string fileNameI=outDirI+"/"+tar+"/"+src+"2"+tar+".st";
            outPutsI[src][tar].open(fileNameI);
        }
    }
    allocateMem();
    initialize();
    initializeSparse();
    // cout<<"Record Connection Of E232E23 Begin"<<endl;
    ofstream file_rowLength("/home/yangjinhao/GeNN/userproject/SingleColumn/connectionInfo/rowLength.st");
    ofstream file_ind("/home/yangjinhao/GeNN/userproject/SingleColumn/connectionInfo/ind.st");
    ofstream file_g("/home/yangjinhao/GeNN/userproject/SingleColumn/connectionInfo/weight.st");
    ofstream file_d("/home/yangjinhao/GeNN/userproject/SingleColumn/connectionInfo/delay.st");
    pullE232E23ConnectivityFromDevice();
    pullE232E23StateFromDevice();
    for (int i=0;i<ParaMeters::neuron_number["E23"];i++){
        file_rowLength<<rowLengthE232E23[i];
        if(i<ParaMeters::neuron_number["E23"]){
            file_rowLength<<" ";
        }
        for (int j=0;j<maxRowLengthE232E23;j++){
            file_ind<<indE232E23[i*maxRowLengthE232E23+j];
            file_g<<gE232E23[i];
            file_d<<static_cast<int>(dE232E23[i]);
            if(j<maxRowLengthE232E23-1){
                file_ind<<" ";
                file_g<<" ";
                file_d<<" ";
            }
        }
        file_ind<<endl;
        file_g<<endl;
        file_d<<endl;
    }
    file_rowLength<<endl;
    file_rowLength.close();
    file_ind.close();
    file_g.close();
    file_d.close();
    cout<<"Pull Connection Of E232E23 Complete"<<endl;
    cout<<"start Simulation"<<endl;
    clock_t start=clock();
    ofstream FileInSynE232P23("/home/yangjinhao/GeNN/userproject/SingleColumn/InSynE232P23.st");
    while (t<TOTAL_TIME){
        if(fmod(t, 100.0) == 0.0) {
            cout << t / 10.0 << "%" << endl;
        }
        if(t>=100.0 and t<110.0){
            // SaveinSyn(outPutsI);
        }
        stepTime();
        // cout<<"step: "<<t<<endl;
        // SaveSpike(outPuts);
        SaveSpikeTest(outPutsTest);
    }
    clock_t end=clock();
    cout<<"Simulation Complete, Time Using: "<<static_cast<double>(end-start)/CLOCKS_PER_SEC<<endl;
    for (auto& outFile : outPuts) {
        outFile.close();
    }
    freeMem();
    return EXIT_SUCCESS;
}