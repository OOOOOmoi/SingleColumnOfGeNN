// #include "/home/yangjinhao/GeNN/userproject/include/spikeRecorder.h"
// #include "/home/yangjinhao/GeNN/userproject/include/timer.h"
// #include "/home/yangjinhao/GeNN/userproject/include/sharedLibraryModel.h"
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
using namespace std;
#define TOTAL_TIME 1000.0f
#define REPORT_TIME 100.0f
#define GET_SPKCNT_NAME(prefix, suffix) prefix##shuffix
#define GET_SPK_NAME(prefix, suffix) prefix##shuffix
#define CALL_PULL_SPIKE(popName) pull##popName##CurrentSpikesFromDevice()
map<string,int> neuron_number={
        {"H1", 15545},
        {"E23", 51738},
        {"S23", 1892},
        {"P23", 2610},
        {"V23", 4514},
        {"E4", 74933},
        {"S4", 4041},
        {"P4", 7037},
        {"V4", 1973},
        {"E5", 21624},
        {"S5", 1586},
        {"P5", 1751},
        {"V5", 334},
        {"E6", 20278},
        {"S6", 1667},
        {"P6", 1656},
        {"V6", 302}
    };

void IntoFile(unsigned int* SpkCnt, unsigned int* Spk, ofstream& file){
    for (unsigned int i=0;i<*SpkCnt;i++){
        file<<Spk[i];
        if(i<*SpkCnt-1){
            file<<" ";
        }
    }
    file<<endl;
}

void SaveSpikeTest(map<string,ofstream>& outPuts){
    pullH1CurrentSpikesFromDevice();
    IntoFile(glbSpkH1,glbSpkCntH1,outPuts["H1"]);
    pullE23CurrentSpikesFromDevice();
    IntoFile(glbSpkE23,glbSpkCntE23,outPuts["E23"]);
    pullS23CurrentSpikesFromDevice();
    IntoFile(glbSpkS23,glbSpkCntS23,outPuts["S23"]);
    pullP23CurrentSpikesFromDevice();
    IntoFile(glbSpkP23,glbSpkCntP23,outPuts["P23"]);
    pullV23CurrentSpikesFromDevice();
    IntoFile(glbSpkV23,glbSpkCntV23,outPuts["V23"]);
    pullE4CurrentSpikesFromDevice();
    IntoFile(glbSpkE4,glbSpkCntE4,outPuts["E4"]);
    pullS4CurrentSpikesFromDevice();
    IntoFile(glbSpkS4,glbSpkCntS4,outPuts["S4"]);
    pullP4CurrentSpikesFromDevice();
    IntoFile(glbSpkP4,glbSpkCntP4,outPuts["P4"]);
    pullV4CurrentSpikesFromDevice();
    IntoFile(glbSpkV4,glbSpkCntV4,outPuts["V4"]);
    pullE5CurrentSpikesFromDevice();
    IntoFile(glbSpkE5,glbSpkCntE5,outPuts["E5"]);
    pullS5CurrentSpikesFromDevice();
    IntoFile(glbSpkS5,glbSpkCntS5,outPuts["S5"]);
    pullP5CurrentSpikesFromDevice();
    IntoFile(glbSpkP5,glbSpkCntP5,outPuts["P5"]);
    pullV5CurrentSpikesFromDevice();
    IntoFile(glbSpkV5,glbSpkCntV5,outPuts["V5"]);
    pullE6CurrentSpikesFromDevice();
    IntoFile(glbSpkE6,glbSpkCntE6,outPuts["E6"]);
    pullS6CurrentSpikesFromDevice();
    IntoFile(glbSpkS6,glbSpkCntS6,outPuts["S6"]);
    pullP6CurrentSpikesFromDevice();
    IntoFile(glbSpkP6,glbSpkCntP6,outPuts["P6"]);
    pullV6CurrentSpikesFromDevice();
    IntoFile(glbSpkV6,glbSpkCntV6,outPuts["V6"]);
}

void SaveSpike(vector<ofstream>& outPuts){
    pullH1SpikesFromDevice();
    for (int i=0;i<*glbSpkCntH1;i++){
        outPuts[0]<<glbSpkH1[i];
        if(i<*glbSpkCntH1-1){
            outPuts[0]<<" ";
        }
    }
    outPuts[0]<<endl;
    pullE23SpikesFromDevice();
    for (int i=0;i<*glbSpkCntE23;i++){
        outPuts[1]<<glbSpkE23[i];
        if(i<*glbSpkCntE23-1){
            outPuts[1]<<" ";
        }
    }
    outPuts[1]<<endl;
    pullS23SpikesFromDevice();
    for (int i=0;i<*glbSpkCntS23;i++){
        outPuts[2]<<glbSpkS23[i];
        if(i<*glbSpkCntS23-1){
            outPuts[2]<<" ";
        }
    }
    outPuts[2]<<endl;
    pullP23SpikesFromDevice();
    for (int i=0;i<*glbSpkCntP23;i++){
        outPuts[3]<<glbSpkP23[i];
        if(i<*glbSpkCntP23-1){
            outPuts[3]<<" ";
        }
    }
    outPuts[3]<<endl;
    pullV23SpikesFromDevice();
    for (int i=0;i<*glbSpkCntV23;i++){
        outPuts[4]<<glbSpkV23[i];
        if(i<*glbSpkCntV23-1){
            outPuts[4]<<" ";
        }
    }
    outPuts[4]<<endl;
    pullE4SpikesFromDevice();
    for (int i=0;i<*glbSpkCntE4;i++){
        outPuts[5]<<glbSpkE4[i];
        if(i<*glbSpkCntE4-1){
            outPuts[5]<<" ";
        }
    }
    outPuts[5]<<endl;
    pullS4SpikesFromDevice();
    for (int i=0;i<*glbSpkCntS4;i++){
        outPuts[6]<<glbSpkS4[i];
        if(i<*glbSpkCntS4-1){
            outPuts[6]<<" ";
        }
    }
    outPuts[6]<<endl;
    pullP4SpikesFromDevice();
    for (int i=0;i<*glbSpkCntP4;i++){
        outPuts[7]<<glbSpkP4[i];
        if(i<*glbSpkCntP4-1){
            outPuts[7]<<" ";
        }
    }
    outPuts[7]<<endl;
    pullV4SpikesFromDevice();
    for (int i=0;i<*glbSpkCntV4;i++){
        outPuts[8]<<glbSpkV4[i];
        if(i<*glbSpkCntV4-1){
            outPuts[8]<<" ";
        }
    }
    outPuts[8]<<endl;
    pullE5SpikesFromDevice();
    for (int i=0;i<*glbSpkCntE5;i++){
        outPuts[9]<<glbSpkE5[i];
        if(i<*glbSpkCntE5-1){
            outPuts[9]<<" ";
        }
    }
    outPuts[9]<<endl;
    pullS5SpikesFromDevice();
    for (int i=0;i<*glbSpkCntS5;i++){
        outPuts[10]<<glbSpkS5[i];
        if(i<*glbSpkCntS5-1){
            outPuts[10]<<" ";
        }
    }
    outPuts[10]<<endl;
    pullP5SpikesFromDevice();
    for (int i=0;i<*glbSpkCntP5;i++){
        outPuts[11]<<glbSpkP5[i];
        if(i<*glbSpkCntP5-1){
            outPuts[11]<<" ";
        }
    }
    outPuts[11]<<endl;
    pullV5SpikesFromDevice();
    for (int i=0;i<*glbSpkCntV5;i++){
        outPuts[12]<<glbSpkV5[i];
        if(i<*glbSpkCntV5-1){
            outPuts[12]<<" ";
        }
    }
    outPuts[12]<<endl;
    pullE6SpikesFromDevice();
    for (int i=0;i<*glbSpkCntE6;i++){
        outPuts[13]<<glbSpkE6[i];
        if(i<*glbSpkCntE6-1){
            outPuts[13]<<" ";
        }
    }
    outPuts[13]<<endl;
    pullS6SpikesFromDevice();
    for (int i=0;i<*glbSpkCntS6;i++){
        outPuts[14]<<glbSpkS6[i];
        if(i<*glbSpkCntS6-1){
            outPuts[14]<<" ";
        }
    }
    outPuts[14]<<endl;
    pullP6SpikesFromDevice();
    for (int i=0;i<*glbSpkCntP6;i++){
        outPuts[15]<<glbSpkP6[i];
        if(i<*glbSpkCntP6-1){
            outPuts[15]<<" ";
        }
    }
    outPuts[15]<<endl;
    pullV6SpikesFromDevice();
    for (int i=0;i<*glbSpkCntV6;i++){
        outPuts[16]<<glbSpkV6[i];
        if(i<*glbSpkCntV6-1){
            outPuts[16]<<" ";
        }
    }
    outPuts[16]<<endl;
}

void VoltageIntoFile(float* V, ofstream& file, string popName){
    for (int i=0;i<neuron_number[popName];i++){
        file<<V[i];
        if(i<neuron_number[popName]-1){
            file<<" ";
        }
    }
    file<<endl;
}

void SaveVoltage(vector<ofstream>& outPuts){
    pullCurrentVH1FromDevice();
    VoltageIntoFile(VH1,outPuts[0],"H1");
    pullCurrentVE23FromDevice();
    VoltageIntoFile(VE23,outPuts[1],"E23");
    pullCurrentVS23FromDevice();
    VoltageIntoFile(VS23,outPuts[2],"S23");
    pullCurrentVP23FromDevice();
    VoltageIntoFile(VP23,outPuts[3],"P23");
    pullCurrentVV23FromDevice();
    VoltageIntoFile(VV23,outPuts[4],"V23");
    pullCurrentVE4FromDevice();
    VoltageIntoFile(VE4,outPuts[5],"E4");
    pullCurrentVS4FromDevice();
    VoltageIntoFile(VS4,outPuts[6],"S4");
    pullCurrentVP4FromDevice();
    VoltageIntoFile(VP4,outPuts[7],"P4");
    pullCurrentVV4FromDevice();
    VoltageIntoFile(VV4,outPuts[8],"V4");
    pullCurrentVE5FromDevice();
    VoltageIntoFile(VE5,outPuts[9],"E5");
    pullCurrentVS5FromDevice();
    VoltageIntoFile(VS5,outPuts[10],"S5");
    pullCurrentVP5FromDevice();
    VoltageIntoFile(VP5,outPuts[11],"P5");
    pullCurrentVV5FromDevice();
    VoltageIntoFile(VV5,outPuts[12],"V5");
    pullCurrentVE6FromDevice();
    VoltageIntoFile(VE6,outPuts[13],"E6");
    pullCurrentVS6FromDevice();
    VoltageIntoFile(VS6,outPuts[14],"S6");
    pullCurrentVP6FromDevice();
    VoltageIntoFile(VP6,outPuts[15],"P6");
    pullCurrentVV6FromDevice();
    VoltageIntoFile(VV6,outPuts[16],"V6");
}

int main(){
    const string outDir="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/output";
    const string outDirVoltage="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/output_voltage";
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
        outPuts.emplace_back(ofstream(fileName));
    }
    vector<ofstream> outPutsVoltage;
    for (auto& PopName:PopList){
        string fileName=outDirVoltage+"/"+PopName+".st";
        outPutsVoltage.emplace_back(ofstream(fileName));
    }
    allocateMem();
    initialize();
    // cout<<"Record Connection Of E232E23 Begin"<<endl;
    // pullE232E23ConnectivityFromDevice();
    // cout<<"Pull Connection Of E232E23 Complete"<<endl;
    // for (int i=0;i<neuron_number["E23"];i++){
    //     file_rowLengthE232E23<<rowLengthE232E23[i];
    //     if(i<neuron_number["E23"]){
    //         file_rowLengthE232E23<<" ";
    //     }
    //     for (int j=0;j<1147;j++){
    //         file_indE232E23<<indE232E23[i*1147+j];
    //         if(j<1146){
    //             file_indE232E23<<" ";
    //         }
    //     }
    //     file_indE232E23<<endl;
    // }
    // file_rowLengthE232E23<<endl;
    // file_rowLengthE232E23.close();
    // file_indE232E23.close();
    cout<<"start Simulation"<<endl;
    clock_t start=clock();
    ofstream FileInSynE232P23("/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/InSynE232P23.st");
    while (t<TOTAL_TIME){
        if(fmod(t, 100.0) == 0.0) {
            cout << t / 10.0 << "%" << endl;
        }
        if(t>=900.0 and t<910.0){
            SaveVoltage(outPutsVoltage);
            pullinSynE232P23FromDevice();
            for(int i=0;i<neuron_number["P23"];i++){
                FileInSynE232P23<<inSynE232P23[i];
                if(i<neuron_number["P23"]-1){
                    FileInSynE232P23<<" ";
                }
            }
            FileInSynE232P23<<endl;
        }
        stepTime();
        // cout<<"step: "<<t<<endl;
        SaveSpike(outPuts);
        // SaveSpikeTest(outPutsTest);
    }
    clock_t end=clock();
    cout<<"Simulation Complete, Time Using: "<<static_cast<double>(end-start)/CLOCKS_PER_SEC<<endl;
    for (auto& outFile : outPuts) {
        outFile.close();
    }
    freeMem();
    return EXIT_SUCCESS;
}