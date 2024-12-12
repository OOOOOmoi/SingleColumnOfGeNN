#pragma once
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

void IntoFile(unsigned int* Spk, unsigned int* SpkCnt, ofstream& file);
void SaveSpikeTest(map<string,ofstream>& outPuts);
void SaveSpike(vector<ofstream>& outPuts);
void VoltageIntoFile(float* V, ofstream& file, string popName);
void SaveVoltage(vector<ofstream>& outPuts);
void WeightIntoFile(ofstream& file, string PopName, const unsigned int rowLength, float* data);
void SaveWeight(map<string,map<string,ofstream>>& outPuts);
void inSynIntoFile(ofstream& file, string tarName, float* inSyn);
void SaveinSyn(map<string,map<string,ofstream>>& outPuts);

