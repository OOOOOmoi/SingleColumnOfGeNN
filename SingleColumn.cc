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

class changeableDC : public CurrentSourceModels::Base
{
public:
    DECLARE_MODEL(changeableDC, 1, 0);
    SET_INJECTION_CODE(
        "if (t > 800 && t<1600)\n"
        "   $(injectCurrent, 0.001 * $(magnitude));\n"
        "else \n"
        "   $(injectCurrent, 0);\n");
    SET_PARAM_NAMES({"magnitude"});
};
IMPLEMENT_MODEL(changeableDC);

map<string,map<string,int>> getSynNum(){
    ifstream file(FileSynapseNumber, ios::in);
    string srcPop, tarPop;
    float synNum;
    map<string,map<string,int>> SynNumber;
    while(file>>srcPop>>tarPop>>synNum){
        SynNumber[tarPop][srcPop]=static_cast<int>(synNum);
    }
    file.close();
    return SynNumber;
}

map<string,map<string,ParaMeters::weightInfo>> getSynWeight(){
    ifstream file(FileWeight,ios::in);
    string srcPop, tarPop;
    double wAve, wSd;
    map<string,map<string,ParaMeters::weightInfo>> SynWeight;
    while(file>>srcPop>>tarPop>>wAve>>wSd){
        SynWeight[tarPop][srcPop].wAve=wAve/1000;
        SynWeight[tarPop][srcPop].wSd=wSd/1000;
    }
    file.close();
    return SynWeight;
}

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
    map<string,int> NeuronNumberMap=ParaMeters::neuron_number;
    InitVarSnippet::Normal::ParamValues vDist(
        ParaMeters::Vmean, //mean
        ParaMeters::Vsd);  //sd
    NeuronModels::LIF::VarValues lifInit(
        initVar<InitVarSnippet::Normal>(vDist), //V
        0.0);//refractor
    ifstream PoissonWeight(FilePoissonWeight,ios::in);
    map<string,map<string,float>> K;
    K=IndCompute(ParaMeters::neuron_number);
    for (int pop=0;pop<ParaMeters::PopulationMax;pop++){
        string popName=ParaMeters::populationNames[pop];
        cout<<"Create Group:"<<popName<<", Neuron Number="<<NeuronNumberMap[popName]<<endl;
        float ioffset=ParaMeters::input[ParaMeters::populationNames[pop]]/1000;
        NeuronModels::LIF::ParamValues lifParams(
            ParaMeters::lifParam.Cm/1000.0,//C
            ParaMeters::lifParam.taum,//TauM
            ParaMeters::lifParam.EL,//Vrest
            ParaMeters::lifParam.Vreset,//Vreset
            ParaMeters::lifParam.Vth,//Vthresh
            ioffset,//Ioffset
            ParaMeters::lifParam.t_ref);//refractor
        auto *Neu=model.addNeuronPopulation<NeuronModels::LIF>(popName,NeuronNumberMap[popName],lifParams,lifInit);
        if(popName=="E23"){
            changeableDC::ParamValues DCpara(
                500);  // 0 - magnitude
            model.addCurrentSource<changeableDC>("CurrE23",popName,DCpara,{});
        }
        if(SpikeRecord==true){
            Neu->setSpikeRecordingEnabled(true);
        }
        if (PoissionInput==true){
            string popPoisson;
            float weightPoisson;
            PoissonWeight>>popPoisson>>weightPoisson;
            CurrentSourceModels::PoissonExp::VarValues poissonInit(0.0);
            CurrentSourceModels::PoissonExp::ParamValues poissonParams(weightPoisson/1000.0,ParaMeters::lifParam.tau_syn,1*K["external"][popName]);
            model.addCurrentSource<CurrentSourceModels::PoissonExp>(popName+"_Poisson",popName,poissonParams,poissonInit);
            cout<<"Creating Poisson Input Of "<<popName<<endl;
        }
    }
    PostsynapticModels::ExpCurr::ParamValues excitatoryExpCurrParams(
        0.5);  // 0 - TauSyn (ms)

    PostsynapticModels::ExpCurr::ParamValues inhibitoryExpCurrParams(
        0.5);  // 0 - TauSyn (ms)
    double Wave,Wsd;
    const double quantile = 0.9999;
    const double maxDelayMs[ParaMeters::typeMax] = {
        ParaMeters::meanDelay[ParaMeters::typeE] + (ParaMeters::delaySD[ParaMeters::typeI] * normalCDFInverse(quantile)),
        ParaMeters::meanDelay[ParaMeters::typeE] + (ParaMeters::delaySD[ParaMeters::typeI] * normalCDFInverse(quantile))};
    const unsigned int maxDendriticDelaySlots = (unsigned int)rint(max(maxDelayMs[ParaMeters::typeE], maxDelayMs[ParaMeters::typeI])  / ParaMeters::dtMs);
    map<string,map<string,int>> SynNumMap=getSynNum();
    map<string,map<string,ParaMeters::weightInfo>> SynWeightMap=getSynWeight();
    for (int tarPop=0;tarPop<ParaMeters::PopulationMax;tarPop++){
        string tarName=ParaMeters::populationNames[tarPop];
        for (int srcPop=0;srcPop<ParaMeters::PopulationMax;srcPop++){
            string srcName=ParaMeters::populationNames[srcPop];
            int SynNum=SynNumMap[tarName][srcName];
            string SynName=ParaMeters::getSynName(tarPop,srcPop);
            if(SynNum==0){
                cout<<"There are no connection from "<<srcName<<" to "<<tarName<<endl;
                continue;
            }
            cout<<"Create Synapses of "<<SynName<<", synNum="<<SynNum<<endl;
            Wave=SynWeightMap[tarName][srcName].wAve;
            Wsd=SynWeightMap[tarName][srcName].wSd;
            InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement::ParamValues synapseNum(
                SynNum);
            if(srcName.find("E") == string::npos){
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
                    SynName,SynapseMatrixType::SPARSE_INDIVIDUALG,NO_DELAY,srcName,tarName,
                    {},staticSynapsesInit,inhibitoryExpCurrParams,{},
                    initConnectivity<InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement>(synapseNum));
                syn->setMaxDendriticDelayTimesteps(maxDendriticDelaySlots);
            }else{
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
                    SynName,SynapseMatrixType::SPARSE_INDIVIDUALG,NO_DELAY,srcName,tarName,
                    {},staticSynapsesInit,excitatoryExpCurrParams,{},
                    initConnectivity<InitSparseConnectivitySnippet::FixedNumberTotalWithReplacement>(synapseNum));
                syn->setMaxDendriticDelayTimesteps(maxDendriticDelaySlots);
            }
        }
    }
}