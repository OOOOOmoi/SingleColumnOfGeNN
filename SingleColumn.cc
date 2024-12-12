#include "modelSpec.h"
#include "neuronModels.h"
#include<ctime>
#include "currentSourceModels.h"
#include "DefaultParam.h"
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <limits>
#include <chrono>
#include <iostream>
#include "../include/normalDistribution.h"
using namespace std;
const bool PoissionInput=false;
const bool SpikeRecord=false;
const char *FileWeight="/home/yangjinhao/GeNN/userproject/SingleColumn/SynapsesWeight.txt";
const char *FilePoissonWeight="/home/yangjinhao/GeNN/userproject/SingleColumn/ExternalSynapses.txt";
const char *FileSynapseNumber="/home/yangjinhao/GeNN/userproject/SingleColumn/SynapsesNumber.txt";
const char *FileSynapseNumberExternal="/home/yangjinhao/GeNN/userproject/SingleColumn/SynapsesNumberEx.txt";
const char *FileInd="/home/yangjinhao/GeNN/userproject/SingleColumn/SynapsesInd.txt";

void SaveInd(map<string,map<string,float>>& K, string PopList[]){
    ofstream file(FileInd);
    for (int i=0;i<17;i++){
        string src=PopList[i];
        for (int j=0;j<17;j++){
            string tar=PopList[j];
            file<<src<<" "<<tar<<" "<<K[src][tar]<<endl;
        }
    }
    file.close();
}

map<string,map<string,float>> IndCompute(map<string,int> NeuronCount){
    map<string,map<string,float>> K;
    ifstream SynapseNum(FileSynapseNumber,ios::in);
    ifstream SynapsesNumberExternal(FileSynapseNumberExternal,ios::in);
    string SrcPop,TarPop;
    float syn;
    while (SynapseNum>>SrcPop>>TarPop>>syn){
        K[SrcPop][TarPop]=syn/NeuronCount[TarPop];
    }
    while (SynapsesNumberExternal>>TarPop>>syn){
        K["external"][TarPop]=syn/NeuronCount[TarPop];
    }
    SynapseNum.close();
    SynapsesNumberExternal.close();
    return K;
}

map<string,map<string,WeightInfo>> GetWeight(){
    map<string,map<string,WeightInfo>> W;
    ifstream Weight(FileWeight,ios::in);
    string SrcPop,TarPop;
    float wAve,wSd;
    while (Weight>>SrcPop>>TarPop>>wAve>>wSd){
        W[SrcPop][TarPop].w_ave=wAve/1000;
        W[SrcPop][TarPop].w_sd=wSd/1000;
    }
    Weight.close();
    return W;
}

LIFParams NeuronParamInit(string name, float EL, float Vth, float Vreset, float Cm, float taum, float tau_syn, float t_ref){
    LIFParams Param;
    Param.NeuronName=name;
    Param.EL=EL;
    Param.Vth=Vth;
    Param.Vreset=Vreset;
    Param.Cm=Cm;
    Param.taum=taum;
    Param.tau_syn=tau_syn;
    Param.t_ref=t_ref;
    return Param;
}
void modelDefinition(ModelSpec &model){
    model.setDT(ParaMeters::dtMs);
    model.setName("SingleColumn");
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    model.setSeed(seed);
    model.setTiming(ParaMeters::measureTiming);
    // model.setDefaultVarLocation(VarLocation::HOST_DEVICE);
    // model.setDefaultSparseConnectivityLocation(VarLocation::HOST_DEVICE);
    // model.setMergePostsynapticModels(true);
    // model.setDefaultNarrowSparseIndEnabled(true);
    ifstream PoissonWeight(FilePoissonWeight,ios::in);
    ifstream SynapsesNumber(FileSynapseNumber,ios::in);
    LIFParams ParamE;
    LIFParams ParamS;
    LIFParams ParamP;
    LIFParams ParamV;
    LIFParams ParamH;
    // LIFParams ParamS=NeuronParamInit("S",-76.0,-50.0,-60.0,800.0,50.0,0.5,1.0);
    // LIFParams ParamP=NeuronParamInit("P",-86.0,-50.0,-60.0,200.0,10.0,0.5,1.0);
    // LIFParams ParamV=NeuronParamInit("V",-70.0,-50.0,-65.0,100.0,20.0,0.5,1.0);
    // LIFParams ParamH=NeuronParamInit("H",-70.0,-50.0,-65.0,100.0,20.0,0.5,1.0);
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
    map<string,float> input={
        {"H1", 501.0},
        {"V23", 501.0-10.0},
        {"S23", 501.0},
        {"E23", 501.0+50.0},
        {"P23", 501.0},
        {"V4", 501.0-50.0},
        {"S4", 501.0},
        {"E4", 501.0+50.0},
        {"P4", 501.0+10.0},
        {"V5", 501.0-10.0},
        {"S5", 501.0},
        {"E5", 501.0+10.0},
        {"P5", 501.0},
        {"V6", 501.0-10.0},
        {"S6", 501.0},
        {"E6", 501.0+50.0},
        {"P6", 501.0}
    };
    InitVarSnippet::Normal::ParamValues vDist(
        InitVoltage.Vmean, //mean
        InitVoltage.Vstd);  //sd
    NeuronModels::LIF::VarValues lifInit(
        initVar<InitVarSnippet::Normal>(vDist), //V
        0.0);//refractor
    map<string,map<string,float>> K;
    K=IndCompute(neuron_number);
    SaveInd(K,PopList);
    double ioffset;
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
        }else if (PopList[i].find("H")!=string::npos){
            ParaList=ParamH;
        }
        if (PoissionInput==false){
            ioffset=input[PopList[i]]/1000.0;
        }
        NeuronModels::LIF::ParamValues lifParams(
            ParaList.Cm/1000.0,//C
            ParaList.taum,//TauM
            ParaList.EL,//Vrest
            ParaList.Vreset,//Vreset
            ParaList.Vth,//Vthresh
            ioffset,//Ioffset
            ParaList.t_ref);//refractor
        
        cout<<"Building Population: "<<PopList[i]<<" ,NeuronNumber: "<<neuron_number[PopList[i]]<<", Ioffset="<<ioffset<<endl;
        auto *Neu=model.addNeuronPopulation<NeuronModels::LIF>(PopList[i],neuron_number[PopList[i]],lifParams,lifInit);
        
        if(SpikeRecord==true){
            Neu->setSpikeRecordingEnabled(true);
        }
        if (PoissionInput==true){
            string popPoisson;
            float weightPoisson;
            PoissonWeight>>popPoisson>>weightPoisson;
            CurrentSourceModels::PoissonExp::VarValues poissonInit(0.0);
            CurrentSourceModels::PoissonExp::ParamValues poissonParams(weightPoisson/1000.0,ParamE.tau_syn,1*K["external"][PopList[i]]);
            model.addCurrentSource<CurrentSourceModels::PoissonExp>(PopList[i]+"_Poisson",PopList[i],poissonParams,poissonInit);
            cout<<"Creating Poisson Input Of "<<PopList[i]<<endl;
        }
    }
    PostsynapticModels::ExpCurr::ParamValues excitatoryExpCurrParams(
        0.5);  // 0 - TauSyn (ms)

    PostsynapticModels::ExpCurr::ParamValues inhibitoryExpCurrParams(
        0.5);  // 0 - TauSyn (ms)
    map<string,map<string,WeightInfo>> W;
    W=GetWeight();
    float syn_num;
    string temp1,temp2;
    double Wave,Wsd;
    const double quantile = 0.9999;
    const double maxDelayMs[ParaMeters::PopulationMax] = {
        ParaMeters::meanDelay[ParaMeters::PopulationE] + (ParaMeters::delaySD[ParaMeters::PopulationE] * normalCDFInverse(quantile)),
        ParaMeters::meanDelay[ParaMeters::PopulationI] + (ParaMeters::delaySD[ParaMeters::PopulationI] * normalCDFInverse(quantile))};
    const unsigned int maxDendriticDelaySlots = (unsigned int)rint(max(maxDelayMs[ParaMeters::PopulationE], maxDelayMs[ParaMeters::PopulationI])  / ParaMeters::dtMs);
    for (auto srcPop=begin(PopList);srcPop!=end(PopList);srcPop++){
        for (auto tarPop=begin(PopList);tarPop!=end(PopList);tarPop++){
            SynapsesNumber>>temp1>>temp2>>syn_num;
            int SynNum=static_cast<int>(syn_num);
            string SynName=*srcPop+"2"+*tarPop;
            if(syn_num==0.0){
                cout<<"There are no connection from "<<*srcPop<<" to "<<*tarPop<<endl;
                continue;
            }
            Wave=static_cast<double>(W[*srcPop][*tarPop].w_ave);
            Wsd=static_cast<double>(W[*srcPop][*tarPop].w_sd);
            cout<<"AveDelay= "<<ParaMeters::meanDelay[0]<<" "<<ParaMeters::meanDelay[1]<<", maxDelay="<<maxDelayMs[0]<<" "<<maxDelayMs[1]<<endl;
            InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement::ParamValues synapseNum(
                SynNum);
            if (srcPop->find("E") != string::npos){
                cout<<"Creating Connect of "<<*srcPop<<" to "<<*tarPop<<", SynapseNumber="<<static_cast<int>(syn_num)<<", AveWeight="<<Wave<<endl;
                InitVarSnippet::NormalClipped::ParamValues wDist(
                    Wave,
                    Wsd,
                    0,
                    numeric_limits<float>::max());
                InitVarSnippet::NormalClippedDelay::ParamValues dDist(
                    ParaMeters::meanDelay[0],
                    ParaMeters::delaySD[0],
                    0.0,
                    maxDelayMs[0]);
                WeightUpdateModels::StaticPulseDendriticDelay::VarValues staticSynapsesInit(
                    initVar<InitVarSnippet::NormalClipped>(wDist),
                    initVar<InitVarSnippet::NormalClippedDelay>(dDist));
                auto* syn=model.addSynapsePopulation<WeightUpdateModels::StaticPulseDendriticDelay,PostsynapticModels::ExpCurr>(
                    SynName,SynapseMatrixType::SPARSE_INDIVIDUALG,NO_DELAY,*srcPop,*tarPop,
                    {},staticSynapsesInit,excitatoryExpCurrParams,{},
                    initConnectivity<InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement>(synapseNum));
                syn->setMaxDendriticDelayTimesteps(maxDendriticDelaySlots);
            }else if(srcPop->find("S") != string::npos){
                cout<<"Creating Connect of "<<*srcPop<<" to "<<*tarPop<<", SynapseNumber="<<static_cast<int>(syn_num)<<", AveWeight="<<Wave<<", AveDelay="<<endl;
                InitVarSnippet::NormalClipped::ParamValues wDist(
                    Wave,
                    Wsd,
                    -numeric_limits<float>::max(),
                    0);
                InitVarSnippet::NormalClippedDelay::ParamValues dDist(
                    ParaMeters::meanDelay[1],
                    ParaMeters::delaySD[1],
                    0.0,
                    maxDelayMs[1]);
                WeightUpdateModels::StaticPulseDendriticDelay::VarValues staticSynapsesInit(
                    initVar<InitVarSnippet::NormalClipped>(wDist),
                    initVar<InitVarSnippet::NormalClippedDelay>(dDist));
                auto* syn=model.addSynapsePopulation<WeightUpdateModels::StaticPulseDendriticDelay,PostsynapticModels::ExpCurr>(
                    *srcPop+"2"+*tarPop,SynapseMatrixType::SPARSE_INDIVIDUALG,NO_DELAY,*srcPop,*tarPop,
                    {},staticSynapsesInit,inhibitoryExpCurrParams,{},
                    initConnectivity<InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement>(synapseNum));
                syn->setMaxDendriticDelayTimesteps(maxDendriticDelaySlots);
            }else if(srcPop->find("P") != string::npos){
                cout<<"Creating Connect of "<<*srcPop<<" to "<<*tarPop<<", SynapseNumber="<<static_cast<int>(syn_num)<<", AveWeight="<<Wave<<endl;
                InitVarSnippet::NormalClipped::ParamValues wDist(
                    Wave,
                    Wsd,
                    -numeric_limits<float>::max(),
                    0);
                InitVarSnippet::NormalClippedDelay::ParamValues dDist(
                    ParaMeters::meanDelay[1],
                    ParaMeters::delaySD[1],
                    0.0,
                    maxDelayMs[1]);
                WeightUpdateModels::StaticPulseDendriticDelay::VarValues staticSynapsesInit(
                    initVar<InitVarSnippet::NormalClipped>(wDist),
                    initVar<InitVarSnippet::NormalClippedDelay>(dDist));
                auto* syn=model.addSynapsePopulation<WeightUpdateModels::StaticPulseDendriticDelay,PostsynapticModels::ExpCurr>(
                    SynName,SynapseMatrixType::SPARSE_INDIVIDUALG,NO_DELAY,*srcPop,*tarPop,
                    {},staticSynapsesInit,inhibitoryExpCurrParams,{},
                    initConnectivity<InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement>(synapseNum));
                syn->setMaxDendriticDelayTimesteps(maxDendriticDelaySlots);
            }else if(srcPop->find("V") != string::npos){
                cout<<"Creating Connect of "<<*srcPop<<" to "<<*tarPop<<", SynapseNumber="<<static_cast<int>(syn_num)<<", AveWeight="<<Wave<<endl;
                InitVarSnippet::NormalClipped::ParamValues wDist(
                    Wave,
                    Wsd,
                    -numeric_limits<float>::max(),
                    0);
                InitVarSnippet::NormalClippedDelay::ParamValues dDist(
                    ParaMeters::meanDelay[1],
                    ParaMeters::delaySD[1],
                    0.0,
                    maxDelayMs[1]);
                WeightUpdateModels::StaticPulseDendriticDelay::VarValues staticSynapsesInit(
                    initVar<InitVarSnippet::NormalClipped>(wDist),
                    initVar<InitVarSnippet::NormalClippedDelay>(dDist));
                auto* syn=model.addSynapsePopulation<WeightUpdateModels::StaticPulseDendriticDelay,PostsynapticModels::ExpCurr>(
                    SynName,SynapseMatrixType::SPARSE_INDIVIDUALG,NO_DELAY,*srcPop,*tarPop,
                    {},staticSynapsesInit,inhibitoryExpCurrParams,{},
                    initConnectivity<InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement>(synapseNum));
                syn->setMaxDendriticDelayTimesteps(maxDendriticDelaySlots);
            }else if(srcPop->find("H") != string::npos){
                cout<<"Creating Connect of "<<*srcPop<<" to "<<*tarPop<<", SynapseNumber="<<static_cast<int>(syn_num)<<", AveWeight="<<Wave<<endl;
                InitVarSnippet::NormalClipped::ParamValues wDist(
                    Wave,
                    Wsd,
                    -numeric_limits<float>::max(),
                    0);
                InitVarSnippet::NormalClippedDelay::ParamValues dDist(
                    ParaMeters::meanDelay[1],
                    ParaMeters::delaySD[1],
                    0.0,
                    maxDelayMs[1]);
                WeightUpdateModels::StaticPulseDendriticDelay::VarValues staticSynapsesInit(
                    initVar<InitVarSnippet::NormalClipped>(wDist),
                    initVar<InitVarSnippet::NormalClippedDelay>(dDist));
                auto* syn=model.addSynapsePopulation<WeightUpdateModels::StaticPulseDendriticDelay,PostsynapticModels::ExpCurr>(
                    SynName,SynapseMatrixType::SPARSE_INDIVIDUALG,NO_DELAY,*srcPop,*tarPop,
                    {},staticSynapsesInit,inhibitoryExpCurrParams,{},
                    initConnectivity<InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement>(synapseNum));
                syn->setMaxDendriticDelayTimesteps(maxDendriticDelaySlots);
            }
        }
    }
    PoissonWeight.close();
    SynapsesNumber.close();
}