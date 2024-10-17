#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include </home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/DefaultParam.h>
using namespace std;
const char *FileWeight="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/SynapsesWeight.txt";
const char *FilePoissonWeight="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/ExternalSynapses.txt";
const char *FileSynapseNumber="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/SynapsesNumber.txt";
int count=17;
map<string,map<string,float>> IndCompute(map<string,int> NeuronCount){
    map<string,map<string,float>> K;
    ifstream SynapseNum(FileSynapseNumber,ios::in);
    string SrcPop,TarPop;
    float syn;
    while (SynapseNum>>SrcPop>>TarPop>>syn){
        K[SrcPop][TarPop]=syn/NeuronCount[TarPop];
    }
    return K;
}

map<string,map<string,WeightInfo>> GetWeight(){
    map<string,map<string,WeightInfo>> W;
    ifstream Weight(FileWeight,ios::in);
    string SrcPop,TarPop;
    float wAve,wSd;
    while (Weight>>SrcPop>>TarPop>>wAve>>wSd){
        W[SrcPop][TarPop].w_ave=wAve;
        W[SrcPop][TarPop].w_sd=wSd;
    }
    return W;
}


int main(){
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
    map<string,map<string,float>> K;
    K=IndCompute(neuron_number);
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            cout<<PopList[i]<<" "<<PopList[j]<<" "<<K[PopList[i]][PopList[j]]<<endl;
        }
        
    }
    map<string,map<string,WeightInfo>> W;
    W=GetWeight();
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            cout<<PopList[i]<<" "<<PopList[j]<<" "<<W[PopList[i]][PopList[j]].w_ave<<endl;
        }
        
    }
    
    return 0;
}