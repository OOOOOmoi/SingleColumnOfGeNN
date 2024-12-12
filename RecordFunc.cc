#include "RecordFunc.h"
#include <map>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <memory>
#include "SingleColumn_CODE/definitions.h"
using namespace std;

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

void IntoFile(unsigned int* Spk, unsigned int* SpkCnt, ofstream& file){
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

void WeightIntoFile(ofstream& file, string PopName, const unsigned int rowLength, float* data){
    for (int i=0;i<neuron_number[PopName];i++){
        for (int j=0;j<rowLength;j++){
            file<<data[i];
            if(j<rowLength-1){
                file<<" ";
            }
        }
        file<<endl;
    }
    file.close();
}

void SaveWeight(map<string,map<string,ofstream>>& outPuts){

}

void inSynIntoFile(ofstream& file, string tarName, float* inSyn){
    for(int i=0;i<neuron_number[tarName];i++){
        file<<inSyn[i];
        if(i<neuron_number[tarName]-1){
            file<<" ";
        }
    }
    file<<endl;
}

void SaveinSyn(map<string,map<string,ofstream>>& outPuts){
    pullinSynH12H1FromDevice();
    inSynIntoFile(outPuts["H1"]["H1"],"H1",inSynH12H1);
    pullinSynH12E23FromDevice();
    inSynIntoFile(outPuts["H1"]["E23"],"E23",inSynH12E23);
    pullinSynH12S23FromDevice();
    inSynIntoFile(outPuts["H1"]["S23"],"S23",inSynH12S23);
    pullinSynH12P23FromDevice();
    inSynIntoFile(outPuts["H1"]["P23"],"P23",inSynH12P23);
    pullinSynH12V23FromDevice();
    inSynIntoFile(outPuts["H1"]["V23"],"V23",inSynH12V23);
    pullinSynH12E4FromDevice();
    inSynIntoFile(outPuts["H1"]["E4"],"E4",inSynH12E4);
    pullinSynH12E5FromDevice();
    inSynIntoFile(outPuts["H1"]["E5"],"E5",inSynH12E5);
    pullinSynH12E6FromDevice();
    inSynIntoFile(outPuts["H1"]["E6"],"E6",inSynH12E6);
    pullinSynE232E23FromDevice();
    inSynIntoFile(outPuts["E23"]["E23"],"E23",inSynE232E23);
    pullinSynE232S23FromDevice();
    inSynIntoFile(outPuts["E23"]["S23"],"S23",inSynE232S23);
    pullinSynE232P23FromDevice();
    inSynIntoFile(outPuts["E23"]["P23"],"P23",inSynE232P23);
    pullinSynE232V23FromDevice();
    inSynIntoFile(outPuts["E23"]["V23"],"V23",inSynE232V23);
    pullinSynE232E4FromDevice();
    inSynIntoFile(outPuts["E23"]["E4"],"E4",inSynE232E4);
    pullinSynE232S4FromDevice();
    inSynIntoFile(outPuts["E23"]["S4"],"S4",inSynE232S4);
    pullinSynE232P4FromDevice();
    inSynIntoFile(outPuts["E23"]["P4"],"P4",inSynE232P4);
    pullinSynE232V4FromDevice();
    inSynIntoFile(outPuts["E23"]["V4"],"V4",inSynE232V4);
    pullinSynE232E5FromDevice();
    inSynIntoFile(outPuts["E23"]["E5"],"E5",inSynE232E5);
    pullinSynE232S5FromDevice();
    inSynIntoFile(outPuts["E23"]["S5"],"S5",inSynE232S5);
    pullinSynE232P5FromDevice();
    inSynIntoFile(outPuts["E23"]["P5"],"P5",inSynE232P5);
    pullinSynS232H1FromDevice();
    inSynIntoFile(outPuts["S23"]["H1"],"H1",inSynS232H1);
    pullinSynS232E23FromDevice();
    inSynIntoFile(outPuts["S23"]["E23"],"E23",inSynS232E23);
    pullinSynS232S23FromDevice();
    inSynIntoFile(outPuts["S23"]["S23"],"S23",inSynS232S23);
    pullinSynS232P23FromDevice();
    inSynIntoFile(outPuts["S23"]["P23"],"P23",inSynS232P23);
    pullinSynS232V23FromDevice();
    inSynIntoFile(outPuts["S23"]["V23"],"V23",inSynS232V23);
    pullinSynS232E4FromDevice();
    inSynIntoFile(outPuts["S23"]["E4"],"E4",inSynS232E4);
    pullinSynS232S4FromDevice();
    inSynIntoFile(outPuts["S23"]["S4"],"S4",inSynS232S4);
    pullinSynS232P4FromDevice();
    inSynIntoFile(outPuts["S23"]["P4"],"P4",inSynS232P4);
    pullinSynS232V4FromDevice();
    inSynIntoFile(outPuts["S23"]["V4"],"V4",inSynS232V4);
    pullinSynS232E5FromDevice();
    inSynIntoFile(outPuts["S23"]["E5"],"E5",inSynS232E5);
    pullinSynP232H1FromDevice();
    inSynIntoFile(outPuts["P23"]["H1"],"H1",inSynP232H1);
    pullinSynP232E23FromDevice();
    inSynIntoFile(outPuts["P23"]["E23"],"E23",inSynP232E23);
    pullinSynP232S23FromDevice();
    inSynIntoFile(outPuts["P23"]["S23"],"S23",inSynP232S23);
    pullinSynP232P23FromDevice();
    inSynIntoFile(outPuts["P23"]["P23"],"P23",inSynP232P23);
    pullinSynP232V23FromDevice();
    inSynIntoFile(outPuts["P23"]["V23"],"V23",inSynP232V23);
    pullinSynP232E4FromDevice();
    inSynIntoFile(outPuts["P23"]["E4"],"E4",inSynP232E4);
    pullinSynP232S4FromDevice();
    inSynIntoFile(outPuts["P23"]["S4"],"S4",inSynP232S4);
    pullinSynP232P4FromDevice();
    inSynIntoFile(outPuts["P23"]["P4"],"P4",inSynP232P4);
    pullinSynP232V4FromDevice();
    inSynIntoFile(outPuts["P23"]["V4"],"V4",inSynP232V4);
    pullinSynP232E5FromDevice();
    inSynIntoFile(outPuts["P23"]["E5"],"E5",inSynP232E5);
    pullinSynP232P5FromDevice();
    inSynIntoFile(outPuts["P23"]["P5"],"P5",inSynP232P5);
    pullinSynV232E23FromDevice();
    inSynIntoFile(outPuts["V23"]["E23"],"E23",inSynV232E23);
    pullinSynV232S23FromDevice();
    inSynIntoFile(outPuts["V23"]["S23"],"S23",inSynV232S23);
    pullinSynV232P23FromDevice();
    inSynIntoFile(outPuts["V23"]["P23"],"P23",inSynV232P23);
    pullinSynV232V23FromDevice();
    inSynIntoFile(outPuts["V23"]["V23"],"V23",inSynV232V23);
    pullinSynV232E4FromDevice();
    inSynIntoFile(outPuts["V23"]["E4"],"E4",inSynV232E4);
    pullinSynV232S4FromDevice();
    inSynIntoFile(outPuts["V23"]["S4"],"S4",inSynV232S4);
    pullinSynV232P4FromDevice();
    inSynIntoFile(outPuts["V23"]["P4"],"P4",inSynV232P4);
    pullinSynV232V4FromDevice();
    inSynIntoFile(outPuts["V23"]["V4"],"V4",inSynV232V4);
    pullinSynE42E23FromDevice();
    inSynIntoFile(outPuts["E4"]["E23"],"E23",inSynE42E23);
    pullinSynE42S23FromDevice();
    inSynIntoFile(outPuts["E4"]["S23"],"S23",inSynE42S23);
    pullinSynE42P23FromDevice();
    inSynIntoFile(outPuts["E4"]["P23"],"P23",inSynE42P23);
    pullinSynE42V23FromDevice();
    inSynIntoFile(outPuts["E4"]["V23"],"V23",inSynE42V23);
    pullinSynE42E4FromDevice();
    inSynIntoFile(outPuts["E4"]["E4"],"E4",inSynE42E4);
    pullinSynE42S4FromDevice();
    inSynIntoFile(outPuts["E4"]["S4"],"S4",inSynE42S4);
    pullinSynE42P4FromDevice();
    inSynIntoFile(outPuts["E4"]["P4"],"P4",inSynE42P4);
    pullinSynE42V4FromDevice();
    inSynIntoFile(outPuts["E4"]["V4"],"V4",inSynE42V4);
    pullinSynE42E5FromDevice();
    inSynIntoFile(outPuts["E4"]["E5"],"E5",inSynE42E5);
    pullinSynE42S5FromDevice();
    inSynIntoFile(outPuts["E4"]["S5"],"S5",inSynE42S5);
    pullinSynE42P5FromDevice();
    inSynIntoFile(outPuts["E4"]["P5"],"P5",inSynE42P5);
    pullinSynE42V5FromDevice();
    inSynIntoFile(outPuts["E4"]["V5"],"V5",inSynE42V5);
    pullinSynE42E6FromDevice();
    inSynIntoFile(outPuts["E4"]["E6"],"E6",inSynE42E6);
    pullinSynS42H1FromDevice();
    inSynIntoFile(outPuts["S4"]["H1"],"H1",inSynS42H1);
    pullinSynS42E23FromDevice();
    inSynIntoFile(outPuts["S4"]["E23"],"E23",inSynS42E23);
    pullinSynS42S23FromDevice();
    inSynIntoFile(outPuts["S4"]["S23"],"S23",inSynS42S23);
    pullinSynS42P23FromDevice();
    inSynIntoFile(outPuts["S4"]["P23"],"P23",inSynS42P23);
    pullinSynS42V23FromDevice();
    inSynIntoFile(outPuts["S4"]["V23"],"V23",inSynS42V23);
    pullinSynS42E4FromDevice();
    inSynIntoFile(outPuts["S4"]["E4"],"E4",inSynS42E4);
    pullinSynS42S4FromDevice();
    inSynIntoFile(outPuts["S4"]["S4"],"S4",inSynS42S4);
    pullinSynS42P4FromDevice();
    inSynIntoFile(outPuts["S4"]["P4"],"P4",inSynS42P4);
    pullinSynS42V4FromDevice();
    inSynIntoFile(outPuts["S4"]["V4"],"V4",inSynS42V4);
    pullinSynS42E5FromDevice();
    inSynIntoFile(outPuts["S4"]["E5"],"E5",inSynS42E5);
    pullinSynS42P5FromDevice();
    inSynIntoFile(outPuts["S4"]["P5"],"P5",inSynS42P5);
    pullinSynS42V5FromDevice();
    inSynIntoFile(outPuts["S4"]["V5"],"V5",inSynS42V5);
    pullinSynP42E23FromDevice();
    inSynIntoFile(outPuts["P4"]["E23"],"E23",inSynP42E23);
    pullinSynP42S23FromDevice();
    inSynIntoFile(outPuts["P4"]["S23"],"S23",inSynP42S23);
    pullinSynP42P23FromDevice();
    inSynIntoFile(outPuts["P4"]["P23"],"P23",inSynP42P23);
    pullinSynP42V23FromDevice();
    inSynIntoFile(outPuts["P4"]["V23"],"V23",inSynP42V23);
    pullinSynP42E4FromDevice();
    inSynIntoFile(outPuts["P4"]["E4"],"E4",inSynP42E4);
    pullinSynP42S4FromDevice();
    inSynIntoFile(outPuts["P4"]["S4"],"S4",inSynP42S4);
    pullinSynP42P4FromDevice();
    inSynIntoFile(outPuts["P4"]["P4"],"P4",inSynP42P4);
    pullinSynP42V4FromDevice();
    inSynIntoFile(outPuts["P4"]["V4"],"V4",inSynP42V4);
    pullinSynP42E5FromDevice();
    inSynIntoFile(outPuts["P4"]["E5"],"E5",inSynP42E5);
    pullinSynP42S5FromDevice();
    inSynIntoFile(outPuts["P4"]["S5"],"S5",inSynP42S5);
    pullinSynP42P5FromDevice();
    inSynIntoFile(outPuts["P4"]["P5"],"P5",inSynP42P5);
    pullinSynP42V5FromDevice();
    inSynIntoFile(outPuts["P4"]["V5"],"V5",inSynP42V5);
    pullinSynV42E23FromDevice();
    inSynIntoFile(outPuts["V4"]["E23"],"E23",inSynV42E23);
    pullinSynV42S23FromDevice();
    inSynIntoFile(outPuts["V4"]["S23"],"S23",inSynV42S23);
    pullinSynV42P23FromDevice();
    inSynIntoFile(outPuts["V4"]["P23"],"P23",inSynV42P23);
    pullinSynV42V23FromDevice();
    inSynIntoFile(outPuts["V4"]["V23"],"V23",inSynV42V23);
    pullinSynV42E4FromDevice();
    inSynIntoFile(outPuts["V4"]["E4"],"E4",inSynV42E4);
    pullinSynV42S4FromDevice();
    inSynIntoFile(outPuts["V4"]["S4"],"S4",inSynV42S4);
    pullinSynV42P4FromDevice();
    inSynIntoFile(outPuts["V4"]["P4"],"P4",inSynV42P4);
    pullinSynV42V4FromDevice();
    inSynIntoFile(outPuts["V4"]["V4"],"V4",inSynV42V4);
    pullinSynV42S5FromDevice();
    inSynIntoFile(outPuts["V4"]["S5"],"S5",inSynV42S5);
    pullinSynV42P5FromDevice();
    inSynIntoFile(outPuts["V4"]["P5"],"P5",inSynV42P5);
    pullinSynV42V5FromDevice();
    inSynIntoFile(outPuts["V4"]["V5"],"V5",inSynV42V5);
    pullinSynE52H1FromDevice();
    inSynIntoFile(outPuts["E5"]["H1"],"H1",inSynE52H1);
    pullinSynE52E23FromDevice();
    inSynIntoFile(outPuts["E5"]["E23"],"E23",inSynE52E23);
    pullinSynE52S23FromDevice();
    inSynIntoFile(outPuts["E5"]["S23"],"S23",inSynE52S23);
    pullinSynE52P23FromDevice();
    inSynIntoFile(outPuts["E5"]["P23"],"P23",inSynE52P23);
    pullinSynE52V23FromDevice();
    inSynIntoFile(outPuts["E5"]["V23"],"V23",inSynE52V23);
    pullinSynE52E4FromDevice();
    inSynIntoFile(outPuts["E5"]["E4"],"E4",inSynE52E4);
    pullinSynE52S4FromDevice();
    inSynIntoFile(outPuts["E5"]["S4"],"S4",inSynE52S4);
    pullinSynE52P4FromDevice();
    inSynIntoFile(outPuts["E5"]["P4"],"P4",inSynE52P4);
    pullinSynE52V4FromDevice();
    inSynIntoFile(outPuts["E5"]["V4"],"V4",inSynE52V4);
    pullinSynE52E5FromDevice();
    inSynIntoFile(outPuts["E5"]["E5"],"E5",inSynE52E5);
    pullinSynE52S5FromDevice();
    inSynIntoFile(outPuts["E5"]["S5"],"S5",inSynE52S5);
    pullinSynE52P5FromDevice();
    inSynIntoFile(outPuts["E5"]["P5"],"P5",inSynE52P5);
    pullinSynE52V5FromDevice();
    inSynIntoFile(outPuts["E5"]["V5"],"V5",inSynE52V5);
    pullinSynE52E6FromDevice();
    inSynIntoFile(outPuts["E5"]["E6"],"E6",inSynE52E6);
    pullinSynE52S6FromDevice();
    inSynIntoFile(outPuts["E5"]["S6"],"S6",inSynE52S6);
    pullinSynE52P6FromDevice();
    inSynIntoFile(outPuts["E5"]["P6"],"P6",inSynE52P6);
    pullinSynE52V6FromDevice();
    inSynIntoFile(outPuts["E5"]["V6"],"V6",inSynE52V6);
    pullinSynS52H1FromDevice();
    inSynIntoFile(outPuts["S5"]["H1"],"H1",inSynS52H1);
    pullinSynS52E23FromDevice();
    inSynIntoFile(outPuts["S5"]["E23"],"E23",inSynS52E23);
    pullinSynS52S23FromDevice();
    inSynIntoFile(outPuts["S5"]["S23"],"S23",inSynS52S23);
    pullinSynS52E4FromDevice();
    inSynIntoFile(outPuts["S5"]["E4"],"E4",inSynS52E4);
    pullinSynS52S4FromDevice();
    inSynIntoFile(outPuts["S5"]["S4"],"S4",inSynS52S4);
    pullinSynS52P4FromDevice();
    inSynIntoFile(outPuts["S5"]["P4"],"P4",inSynS52P4);
    pullinSynS52V4FromDevice();
    inSynIntoFile(outPuts["S5"]["V4"],"V4",inSynS52V4);
    pullinSynS52E5FromDevice();
    inSynIntoFile(outPuts["S5"]["E5"],"E5",inSynS52E5);
    pullinSynS52S5FromDevice();
    inSynIntoFile(outPuts["S5"]["S5"],"S5",inSynS52S5);
    pullinSynS52P5FromDevice();
    inSynIntoFile(outPuts["S5"]["P5"],"P5",inSynS52P5);
    pullinSynS52V5FromDevice();
    inSynIntoFile(outPuts["S5"]["V5"],"V5",inSynS52V5);
    pullinSynS52E6FromDevice();
    inSynIntoFile(outPuts["S5"]["E6"],"E6",inSynS52E6);
    pullinSynS52S6FromDevice();
    inSynIntoFile(outPuts["S5"]["S6"],"S6",inSynS52S6);
    pullinSynS52P6FromDevice();
    inSynIntoFile(outPuts["S5"]["P6"],"P6",inSynS52P6);
    pullinSynS52V6FromDevice();
    inSynIntoFile(outPuts["S5"]["V6"],"V6",inSynS52V6);
    pullinSynP52P23FromDevice();
    inSynIntoFile(outPuts["P5"]["P23"],"P23",inSynP52P23);
    pullinSynP52S4FromDevice();
    inSynIntoFile(outPuts["P5"]["S4"],"S4",inSynP52S4);
    pullinSynP52P4FromDevice();
    inSynIntoFile(outPuts["P5"]["P4"],"P4",inSynP52P4);
    pullinSynP52V4FromDevice();
    inSynIntoFile(outPuts["P5"]["V4"],"V4",inSynP52V4);
    pullinSynP52E5FromDevice();
    inSynIntoFile(outPuts["P5"]["E5"],"E5",inSynP52E5);
    pullinSynP52S5FromDevice();
    inSynIntoFile(outPuts["P5"]["S5"],"S5",inSynP52S5);
    pullinSynP52P5FromDevice();
    inSynIntoFile(outPuts["P5"]["P5"],"P5",inSynP52P5);
    pullinSynP52V5FromDevice();
    inSynIntoFile(outPuts["P5"]["V5"],"V5",inSynP52V5);
    pullinSynP52E6FromDevice();
    inSynIntoFile(outPuts["P5"]["E6"],"E6",inSynP52E6);
    pullinSynP52S6FromDevice();
    inSynIntoFile(outPuts["P5"]["S6"],"S6",inSynP52S6);
    pullinSynP52P6FromDevice();
    inSynIntoFile(outPuts["P5"]["P6"],"P6",inSynP52P6);
    pullinSynP52V6FromDevice();
    inSynIntoFile(outPuts["P5"]["V6"],"V6",inSynP52V6);
    pullinSynV52E4FromDevice();
    inSynIntoFile(outPuts["V5"]["E4"],"E4",inSynV52E4);
    pullinSynV52S4FromDevice();
    inSynIntoFile(outPuts["V5"]["S4"],"S4",inSynV52S4);
    pullinSynV52P4FromDevice();
    inSynIntoFile(outPuts["V5"]["P4"],"P4",inSynV52P4);
    pullinSynV52V4FromDevice();
    inSynIntoFile(outPuts["V5"]["V4"],"V4",inSynV52V4);
    pullinSynV52E5FromDevice();
    inSynIntoFile(outPuts["V5"]["E5"],"E5",inSynV52E5);
    pullinSynV52S5FromDevice();
    inSynIntoFile(outPuts["V5"]["S5"],"S5",inSynV52S5);
    pullinSynV52P5FromDevice();
    inSynIntoFile(outPuts["V5"]["P5"],"P5",inSynV52P5);
    pullinSynV52V5FromDevice();
    inSynIntoFile(outPuts["V5"]["V5"],"V5",inSynV52V5);
    pullinSynV52E6FromDevice();
    inSynIntoFile(outPuts["V5"]["E6"],"E6",inSynV52E6);
    pullinSynV52S6FromDevice();
    inSynIntoFile(outPuts["V5"]["S6"],"S6",inSynV52S6);
    pullinSynV52P6FromDevice();
    inSynIntoFile(outPuts["V5"]["P6"],"P6",inSynV52P6);
    pullinSynV52V6FromDevice();
    inSynIntoFile(outPuts["V5"]["V6"],"V6",inSynV52V6);
    pullinSynE62E5FromDevice();
    inSynIntoFile(outPuts["E6"]["E5"],"E5",inSynE62E5);
    pullinSynE62S5FromDevice();
    inSynIntoFile(outPuts["E6"]["S5"],"S5",inSynE62S5);
    pullinSynE62P5FromDevice();
    inSynIntoFile(outPuts["E6"]["P5"],"P5",inSynE62P5);
    pullinSynE62V5FromDevice();
    inSynIntoFile(outPuts["E6"]["V5"],"V5",inSynE62V5);
    pullinSynE62E6FromDevice();
    inSynIntoFile(outPuts["E6"]["E6"],"E6",inSynE62E6);
    pullinSynE62S6FromDevice();
    inSynIntoFile(outPuts["E6"]["S6"],"S6",inSynE62S6);
    pullinSynE62P6FromDevice();
    inSynIntoFile(outPuts["E6"]["P6"],"P6",inSynE62P6);
    pullinSynE62V6FromDevice();
    inSynIntoFile(outPuts["E6"]["V6"],"V6",inSynE62V6);
    pullinSynS62E5FromDevice();
    inSynIntoFile(outPuts["S6"]["E5"],"E5",inSynS62E5);
    pullinSynS62S5FromDevice();
    inSynIntoFile(outPuts["S6"]["S5"],"S5",inSynS62S5);
    pullinSynS62P5FromDevice();
    inSynIntoFile(outPuts["S6"]["P5"],"P5",inSynS62P5);
    pullinSynS62V5FromDevice();
    inSynIntoFile(outPuts["S6"]["V5"],"V5",inSynS62V5);
    pullinSynS62E6FromDevice();
    inSynIntoFile(outPuts["S6"]["E6"],"E6",inSynS62E6);
    pullinSynS62S6FromDevice();
    inSynIntoFile(outPuts["S6"]["S6"],"S6",inSynS62S6);
    pullinSynS62P6FromDevice();
    inSynIntoFile(outPuts["S6"]["P6"],"P6",inSynS62P6);
    pullinSynS62V6FromDevice();
    inSynIntoFile(outPuts["S6"]["V6"],"V6",inSynS62V6);
    pullinSynP62E23FromDevice();
    inSynIntoFile(outPuts["P6"]["E23"],"E23",inSynP62E23);
    pullinSynP62E4FromDevice();
    inSynIntoFile(outPuts["P6"]["E4"],"E4",inSynP62E4);
    pullinSynP62E5FromDevice();
    inSynIntoFile(outPuts["P6"]["E5"],"E5",inSynP62E5);
    pullinSynP62S5FromDevice();
    inSynIntoFile(outPuts["P6"]["S5"],"S5",inSynP62S5);
    pullinSynP62P5FromDevice();
    inSynIntoFile(outPuts["P6"]["P5"],"P5",inSynP62P5);
    pullinSynP62V5FromDevice();
    inSynIntoFile(outPuts["P6"]["V5"],"V5",inSynP62V5);
    pullinSynP62E6FromDevice();
    inSynIntoFile(outPuts["P6"]["E6"],"E6",inSynP62E6);
    pullinSynP62S6FromDevice();
    inSynIntoFile(outPuts["P6"]["S6"],"S6",inSynP62S6);
    pullinSynP62P6FromDevice();
    inSynIntoFile(outPuts["P6"]["P6"],"P6",inSynP62P6);
    pullinSynP62V6FromDevice();
    inSynIntoFile(outPuts["P6"]["V6"],"V6",inSynP62V6);
    pullinSynV62E5FromDevice();
    inSynIntoFile(outPuts["V6"]["E5"],"E5",inSynV62E5);
    pullinSynV62S5FromDevice();
    inSynIntoFile(outPuts["V6"]["S5"],"S5",inSynV62S5);
    pullinSynV62P5FromDevice();
    inSynIntoFile(outPuts["V6"]["P5"],"P5",inSynV62P5);
    pullinSynV62V5FromDevice();
    inSynIntoFile(outPuts["V6"]["V5"],"V5",inSynV62V5);
    pullinSynV62E6FromDevice();
    inSynIntoFile(outPuts["V6"]["E6"],"E6",inSynV62E6);
    pullinSynV62S6FromDevice();
    inSynIntoFile(outPuts["V6"]["S6"],"S6",inSynV62S6);
    pullinSynV62P6FromDevice();
    inSynIntoFile(outPuts["V6"]["P6"],"P6",inSynV62P6);
    pullinSynV62V6FromDevice();
    inSynIntoFile(outPuts["V6"]["V6"],"V6",inSynV62V6);
}



