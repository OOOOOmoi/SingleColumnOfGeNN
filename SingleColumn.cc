#include "modelSpec.h"
#include "neuronModels.h"
#include<ctime>
#include "currentSourceModels.h"
#include "DefaultParam.h"
#include <string>
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
    
}