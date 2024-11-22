#include "/home/yangjinhao/GeNN/genn-master/userproject/include/spikeRecorder.h"
#include "/home/yangjinhao/GeNN/genn-master/userproject/include/timer.h"
#include "/home/yangjinhao/GeNN/genn-master/userproject/include/sharedLibraryModel.h"
#include "SingleColumn_CODE/definitions.h"
#include <map>
#include <cmath>
#include "time.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;
#define TOTAL_TIME 1000.0f
#define REPORT_TIME 100.0f
#define CALL_PULL_SPIKE(popName) pull##popName##StateFromDevice()
int main(){
    const string outDir="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/output";
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
    map<string,int> neuron_number={
            {"1", 15545},
            {"23", 60753},
            {"4", 87985},
            {"5", 25295},
            {"6", 23903},
            {"total", 213481},
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
    const float duration=1000.0;
    const float dt=0.1;
    const unsigned int timesteps = round(duration / dt);
    const string str1="./";
    const string str2="SingleColumn";
    SharedLibraryModel<float> model(str1,str2);
    model.allocateMem();
    model.allocateRecordingBuffers(timesteps);
    model.initialize();
    model.initializeSparse();
    double recordS=0.0;
    {
        Timer timer("Simulation:");
        const unsigned int tenPercentTimestep = timesteps / 10;
        for(unsigned int i = 0; i < timesteps; i++) {
            // Indicate every 10%
            if((i % tenPercentTimestep) == 0) {
                cout << i / 100 << "%" << endl;
            }
            // Simulate
            cout<<"step: "<<i<<endl;
            model.stepTime();
        }
    }
    {
        TimerAccumulate timer(recordS);

        // Download recording data from device
        model.pullRecordingBuffersFromDevice();

        // Loop through populations
        for(int i=0;i<17;i++) {
            // Get pointer to recording data
            const string name = PopList[i];
            const uint32_t *recordSpk = model.getArray<uint32_t>("recordSpk" + name);
            unsigned int recordNum=neuron_number[PopList[i]]*0.05;
            // Write to text file
            writeTextSpikeRecording(outDir + "/" + name + ".st", recordSpk, recordNum, timesteps, dt);
        }
    }
    cout << "Timing:" << endl;
    cout << "\tInit:" << *model.getScalar<double>("initTime") * 1000.0 << endl;
    cout << "\tSparse init:" << *model.getScalar<double>("initSparseTime") * 1000.0 << endl;
    cout << "\tNeuron simulation:" << *model.getScalar<double>("neuronUpdateTime") * 1000.0 << endl;
    cout << "\tSynapse simulation:" << *model.getScalar<double>("presynapticUpdateTime") * 1000.0 << endl;
    cout << "Record:" << recordS << "s" << endl;
}


// int main(){
//     map<string,int> neuron_number={
//         {"H1", 15545},
//         {"E23", 51738},
//         {"S23", 1892},
//         {"P23", 2610},
//         {"V23", 4514},
//         {"E4", 74933},
//         {"S4", 4041},
//         {"P4", 7037},
//         {"V4", 1973},
//         {"E5", 21624},
//         {"S5", 1586},
//         {"P5", 1751},
//         {"V5", 334},
//         {"E6", 20278},
//         {"S6", 1667},
//         {"P6", 1656},
//         {"V6", 302}
//     };
//     allocateMem();
//     initialize();
//     ofstream file("outputE23VoltageTime.st");
//     ofstream file_rowLengthE232E23("rowLengthE232E23.st");
//     ofstream file_indE232E23("indE232E23.st");
//     SpikeRecorder<> H1Spikes(&getH1CurrentSpikes, &getH1CurrentSpikeCount, "outputH1SpikeTime.st");
//     SpikeRecorder<> E23Spikes(&getE23CurrentSpikes, &getE23CurrentSpikeCount, "outputE23SpikeTime.st");
//     SpikeRecorder<> E6Spikes(&getE6CurrentSpikes, &getE6CurrentSpikeCount, "outputE6SpikeTime.st");
//     while (t<TOTAL_TIME){
//         pullCurrentVE23FromDevice();
//         if(t==0.0){
//             for (int i=0;i<neuron_number["E23"];i++){
//                 file<<VE23[i];
//                 if(i<neuron_number["E23"]-1){
//                     file<<" ";
//                 }
//             }
//             file<<endl;
//         }
//         stepTime();
//         pullH1CurrentSpikesFromDevice();
//         pullE23CurrentSpikesFromDevice();
//         pullE6CurrentSpikesFromDevice();
//         H1Spikes.record(t);
//         E23Spikes.record(t);
//         E6Spikes.record(t);
//         // cout<<VE23[0]<<endl;
//         // cout<<"step: "<<t<<endl;
//     }
    
//     pullE232E23ConnectivityFromDevice();
//     for (int i=0;i<neuron_number["E23"];i++){
//         file_rowLengthE232E23<<rowLengthE232E23[i];
//         if(i<neuron_number["E23"]){
//             file_rowLengthE232E23<<" ";
//         }
//         for (int j=0;j<1147;j++){
//             file_indE232E23<<indE232E23[i*1147+j];
//             if(j<1146){
//                 file_indE232E23<<" ";
//             }
//         }
//         file_indE232E23<<endl;
//     }
//     file_rowLengthE232E23<<endl;
//     file_rowLengthE232E23.close();
//     file_indE232E23.close();
//     file.close();
//     freeMem();
//     return EXIT_SUCCESS;
// }