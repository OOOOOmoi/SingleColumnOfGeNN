#include <map>
#include <string>
using namespace std;

struct LIFParams{
    string NeuronName = "E";
    float EL = -70.0;
    float Vth = -50.0;
    float Vreset = -60.0;
    float Cm = 500.0;
    float taum = 20.0;
    float tau_syn = 0.5;
    float t_ref = 2.0;
};

struct InitParam{
    float Vmean=-150.0;
    float Vstd=50.0;
};

struct WeightInfo{
    float w_ave;
    float w_sd;
};