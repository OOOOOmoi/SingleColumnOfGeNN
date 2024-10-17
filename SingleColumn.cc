#include "modelSpec.h"
#include "neuronModels.h"
#include<ctime>
#include "currentSourceModels.h"
#include "DefaultParam.h"
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
const char *FileWeight="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/SynapsesWeight.txt";
const char *FilePoissonWeight="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/ExternalSynapses.txt";
const char *FileSynapseNumber="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/SynapsesNumber.txt";

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

LIFParams NeuronParamInit(string name, float EL, float Vth, float Vreset, float Cm, float taum, float tan_syn, float t_ref){
    LIFParams Param;
    Param.NeuronName=name;
    Param.EL=El;
    Param.Vth=Vth;
    Param.Vreset=Vreset;
    Param.Cm=Cm;
    Param.taum=taum;
    Param.tau_syn=tau_syn;
    Param.t_ref=t_ref;
    return Param;
}



void modelDefinition(ModelSpec &model){
    ifstream SynapsesWeight(FileWeight,ios::in);
    ifstream PoissonWeight(FilePoissonWeight,ios::in);
    LIFParams ParamE;
    LIFParams ParamS=NeuronParamInit("S",-76.0,-50.0,-60.0,800.0,50.0,0.5,1.0);
    LIFParams ParamP=NeuronParamInit("P",-86.0,-50.0,-60.0,200.0,10.0,0.5,1.0);
    LIFParams ParamV=NeuronParamInit("V",-70.0,-50.0,-65.0,100.0,20.0,0.5,1.0);
    LIFParams ParamH=NeuronParamInit("H",-70.0,-50.0,-65.0,100.0,20.0,0.5,1.0);
    InitParam InitVoltage;
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
    map<string,map<string,float>> Ind;
    Ind=IndCompute(neuron_number);
    InitVarSnippet::Normal::ParamValues vDist(
        InitVoltage.Vmean, //mean
        InitVoltage.Vstd);  //sd
    NeuronModels::LIF::VarValues lifInit(
        initVar<InitVarSnippet::Normal>(vDist), //V
        0.0);//refractor
    for (int i = 0; i < 17; i++){
        LIFParams ParaList;
        if (PopList[i].find("E")!=string::npos){
            ParaList=ParamE;
        }else if (PopList[i].find("S")!=string::npos){
            ParaList=ParamS;
        }else if (PopList[i].find("P")!=string::npos){
            ParaList=ParamP;
        }else if (PopList[i].find("V")!=string::npos){
            ParaList=ParamV;
        }
        NeuronModels::LIF::ParamValues lifParams(
            ParaList.Cm/1000.0,//C
            ParaList.taum,//TauM
            ParaList.EL,//Vrest
            ParaList.Vreset,//Vreset
            ParaList.Vth,//Vthresh
            0.0,//Ioffset
            ParaList.t_ref);//refractor
        cout<<"Building Population: "<<PopList[i]<<" ,NeuronNumber: "<<neuron_number[PopList[i]]<<endl;
        model.addNeuronPopulation<NeuronModels::LIF>(PopList[i],neuron_number[PopList[i]],lifParams,lifInit);
        string popPoisson;
        float weightPoisson;
        PoissonWeight>>popPoisson>>weightPoisson;
        CurrentSourceModels::PoissonExp::VarValues poissonInit(0.0);
        CurrentSourceModels::PoissonExp::ParamValues poissonParams(weightPoisson/1000.0,ParamE.tau_syn,10.0);
        model.addCurrentSource<CurrentSourceModels::PoissonExp>(PopList[i]+"_Poisson",PopList[i],poissonParams,poissonInit)
        cout<<"Creating Poisson Input Of "<<PopList[i]<<endl;
    }
    map<string,map<string,WeightInfo>> W;
    W=GetWeight();
    for (auto srcPop=begin(PopList);srcPop!=end(PopList);srcPop++){
        for (auto tarPop=begin(PopList);tarPop!=end(PopList);tarPop++){
            model.addSynapsePopulation<WeightUpdateModels::StaticPulseDendriticDelay,PostsynapticModels::ExpCurr>(
                srcPop+"2"+tarPop,SynapseMatrixType::SPARSE_INDIVIDUALG,NO_DELAY,srcPop,tarPop,
                );
        }
    }
}