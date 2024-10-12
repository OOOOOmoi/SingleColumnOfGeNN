#include "/home/yangjinhao/GeNN/genn-master/userproject/include/spikeRecorder.h"
#include "/home/yangjinhao/GeNN/genn-master/userproject/include/timer.h"
#include <cmath>
#include "time.h"
using namespace std;
#include <iostream>
#include <fstream>
#include "EI_balance_CODE/definitions.h"
#define TOTAL_TIME 1000.0f
#define REPORT_TIME 200.0f
int main(){
    allocateMem();
    initialize();
}