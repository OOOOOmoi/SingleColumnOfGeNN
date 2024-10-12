#include "modelSpec.h"
#include "neuronModels.h"
#include<ctime>
#include "currentSourceModels.h"
#include "DefaultParam.h"
#include <string>
#include <map>
#include <vector>
using namespace std;

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
    LIFParams ParamE;
    LIFParams ParamS=NeuronParamInit("S",-76.0,-50.0,-60.0,800.0,50.0,0.5,1.0);
    LIFParams ParamP=NeuronParamInit("P",-86.0,-50.0,-60.0,200.0,10.0,0.5,1.0);
    LIFParams ParamV=NeuronParamInit("V",-70.0,-50.0,-65.0,100.0,20.0,0.5,1.0);
    LIFParams ParamH=NeuronParamInit("H",-70.0,-50.0,-65.0,100.0,20.0,0.5,1.0);
    InitParam InitVoltage;
    vector<string> NeuronType={"E","S","P","H"};
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
            {"H23", 4514},
            {"E4", 74933},
            {"S4", 4041},
            {"P4", 7037},
            {"H4", 1973},
            {"E5", 21624},
            {"S5", 1586},
            {"P5", 1751},
            {"H5", 334},
            {"E6", 20278},
            {"S6", 1667},
            {"P6", 1656},
            {"H6", 302}
    };
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
        }else if (PopList[i].find("H")!=string::npos){
            ParaList=ParamH;
        }
        NeuronModels::LIF::ParamValues lifParams(
            ParaList.Cm/1000.0,//C
            ParaList.taum,//TauM
            ParaList.EL,//Vrest
            ParaList.Vreset,//Vreset
            ParaList.Vth,//Vthresh
            0.0,//Ioffset
            ParaList.t_ref);//refractor
        model.addNeuronPopulation<NeuronModels::LIF>(PopList[i],neuron_number[PopList[i]],lifParams,lifInit);
    }
    
    
}