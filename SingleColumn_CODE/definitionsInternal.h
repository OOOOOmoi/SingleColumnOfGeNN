#pragma once
#include "definitions.h"

// CUDA includes
#include <curand_kernel.h>
#include <cuda_fp16.h>

// ------------------------------------------------------------------------
// Helper macro for error-checking CUDA calls
#define CHECK_CUDA_ERRORS(call) {\
    cudaError_t error = call;\
    if (error != cudaSuccess) {\
        throw std::runtime_error(__FILE__": " + std::to_string(__LINE__) + ": cuda error " + std::to_string(error) + ": " + cudaGetErrorString(error));\
    }\
}

#define SUPPORT_CODE_FUNC __device__ __host__ inline


template<typename RNG>
__device__ inline float exponentialDistFloat(RNG *rng) {
    while (true) {
        const float u = curand_uniform(rng);
        if (u != 0.0f) {
            return -logf(u);
        }
    }
}

template<typename RNG>
__device__ inline double exponentialDistDouble(RNG *rng) {
    while (true) {
        const double u = curand_uniform_double(rng);
        if (u != 0.0) {
            return -log(u);
        }
    }
}

template<typename RNG>
__device__ inline float gammaDistFloatInternal(RNG *rng, float c, float d)
 {
    float x, v, u;
    while (true) {
        do {
            x = curand_normal(rng);
            v = 1.0f + c*x;
        }
        while (v <= 0.0f);
        
        v = v*v*v;
        do {
            u = curand_uniform(rng);
        }
        while (u == 1.0f);
        
        if (u < 1.0f - 0.0331f*x*x*x*x) break;
        if (logf(u) < 0.5f*x*x + d*(1.0f - v + logf(v))) break;
    }
    
    return d*v;
}

template<typename RNG>
__device__ inline float gammaDistFloat(RNG *rng, float a)
 {
    if (a > 1)
     {
        const float u = curand_uniform (rng);
        const float d = (1.0f + a) - 1.0f / 3.0f;
        const float c = (1.0f / 3.0f) / sqrtf(d);
        return gammaDistFloatInternal (rng, c, d) * powf(u, 1.0f / a);
    }
    else
     {
        const float d = a - 1.0f / 3.0f;
        const float c = (1.0f / 3.0f) / sqrtf(d);
        return gammaDistFloatInternal(rng, c, d);
    }
}

template<typename RNG>
__device__ inline float gammaDistDoubleInternal(RNG *rng, double c, double d)
 {
    double x, v, u;
    while (true) {
        do {
            x = curand_normal_double(rng);
            v = 1.0 + c*x;
        }
        while (v <= 0.0);
        
        v = v*v*v;
        do {
            u = curand_uniform_double(rng);
        }
        while (u == 1.0);
        
        if (u < 1.0 - 0.0331*x*x*x*x) break;
        if (log(u) < 0.5*x*x + d*(1.0 - v + log(v))) break;
    }
    
    return d*v;
}

template<typename RNG>
__device__ inline float gammaDistDouble(RNG *rng, double a)
 {
    if (a > 1.0)
     {
        const double u = curand_uniform (rng);
        const double d = (1.0 + a) - 1.0 / 3.0;
        const double c = (1.0 / 3.0) / sqrt(d);
        return gammaDistDoubleInternal (rng, c, d) * pow(u, 1.0 / a);
    }
    else
     {
        const float d = a - 1.0 / 3.0;
        const float c = (1.0 / 3.0) / sqrt(d);
        return gammaDistDoubleInternal(rng, c, d);
    }
}

template<typename RNG>
__device__ inline unsigned int binomialDistFloatInternal(RNG *rng, unsigned int n, float p)
 {
    const float q = 1.0f - p;
    const float qn = expf(n * logf(q));
    const float np = n * p;
    const unsigned int bound = min(n, (unsigned int)(np + (10.0f * sqrtf((np * q) + 1.0f))));
    unsigned int x = 0;
    float px = qn;
    float u = curand_uniform(rng);
    while(u > px)
     {
        x++;
        if(x > bound) {
            x = 0;
            px = qn;
            u = curand_uniform(rng);
        }
        else {
            u -= px;
            px = ((n - x + 1) * p * px) / (x * q);
        }
    }
    return x;
}

template<typename RNG>
__device__ inline unsigned int binomialDistFloat(RNG *rng, unsigned int n, float p)
 {
    if(p <= 0.5f) {
        return binomialDistFloatInternal(rng, n, p);
    }
    else {
        return (n - binomialDistFloatInternal(rng, n, 1.0f - p));
    }
}
template<typename RNG>
__device__ inline unsigned int binomialDistDoubleInternal(RNG *rng, unsigned int n, double p)
 {
    const double q = 1.0 - p;
    const double qn = exp(n * log(q));
    const double np = n * p;
    const unsigned int bound = min(n, (unsigned int)(np + (10.0 * sqrt((np * q) + 1.0))));
    unsigned int x = 0;
    double px = qn;
    double u = curand_uniform_double(rng);
    while(u > px)
     {
        x++;
        if(x > bound) {
            x = 0;
            px = qn;
            u = curand_uniform_double(rng);
        }
        else {
            u -= px;
            px = ((n - x + 1) * p * px) / (x * q);
        }
    }
    return x;
}

template<typename RNG>
__device__ inline unsigned int binomialDistDouble(RNG *rng, unsigned int n, double p)
 {
    if(p <= 0.5) {
        return binomialDistDoubleInternal(rng, n, p);
    }
    else {
        return (n - binomialDistDoubleInternal(rng, n, 1.0 - p));
    }
}
// ------------------------------------------------------------------------
// merged group structures
// ------------------------------------------------------------------------
struct MergedSynapseConnectivityHostInitGroup0
 {
    uint16_t** preCalcRowLength;
    uint16_t** d_preCalcRowLength;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    unsigned int rowStride;
    scalar total;
    
}
;
extern "C" {
// ------------------------------------------------------------------------
// global variables
// ------------------------------------------------------------------------
EXPORT_VAR __device__ curandStatePhilox4_32_10_t d_rng;

// ------------------------------------------------------------------------
// timers
// ------------------------------------------------------------------------
EXPORT_VAR cudaEvent_t neuronUpdateStart;
EXPORT_VAR cudaEvent_t neuronUpdateStop;
EXPORT_VAR cudaEvent_t presynapticUpdateStart;
EXPORT_VAR cudaEvent_t presynapticUpdateStop;
EXPORT_VAR cudaEvent_t initStart;
EXPORT_VAR cudaEvent_t initStop;
EXPORT_VAR cudaEvent_t initSparseStart;
EXPORT_VAR cudaEvent_t initSparseStop;

// ------------------------------------------------------------------------
// merged group arrays for host initialisation
// ------------------------------------------------------------------------
EXPORT_VAR MergedSynapseConnectivityHostInitGroup0 mergedSynapseConnectivityHostInitGroup0[186]; 
// ------------------------------------------------------------------------
// local neuron groups
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// copying merged group structures to device
// ------------------------------------------------------------------------
EXPORT_FUNC void pushMergedNeuronInitGroup0ToDevice(unsigned int idx, float* inSynInSyn10, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn6, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, float* inSynInSyn11, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, float* inSynInSyn12, float* denDelayInSyn12, unsigned int* denDelayPtrInSyn12, float* inSynInSyn13, float* denDelayInSyn13, unsigned int* denDelayPtrInSyn13, float* denDelayInSyn2, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* inSynInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronInitGroup1ToDevice(unsigned int idx, float* inSynInSyn3, unsigned int* denDelayPtrInSyn7, float* denDelayInSyn7, float* inSynInSyn7, unsigned int* denDelayPtrInSyn6, float* denDelayInSyn6, float* inSynInSyn6, unsigned int* denDelayPtrInSyn5, float* denDelayInSyn5, float* inSynInSyn5, unsigned int* denDelayPtrInSyn4, float* denDelayInSyn4, float* inSynInSyn4, unsigned int* denDelayPtrInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn2, float* denDelayInSyn2, float* inSynInSyn2, unsigned int* denDelayPtrInSyn1, float* denDelayInSyn1, float* inSynInSyn1, unsigned int* denDelayPtrInSyn0, float* denDelayInSyn0, float* inSynInSyn0, scalar* RefracTime, scalar* V, unsigned int* spk, unsigned int* spkCnt, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronInitGroup2ToDevice(unsigned int idx, float* inSynInSyn2, unsigned int* denDelayPtrInSyn5, float* denDelayInSyn5, float* inSynInSyn5, unsigned int* denDelayPtrInSyn4, float* denDelayInSyn4, float* inSynInSyn4, unsigned int* denDelayPtrInSyn3, float* denDelayInSyn3, float* inSynInSyn3, unsigned int* denDelayPtrInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn1, float* denDelayInSyn1, float* inSynInSyn1, unsigned int* denDelayPtrInSyn0, float* denDelayInSyn0, float* inSynInSyn0, scalar* RefracTime, scalar* V, unsigned int* spk, unsigned int* spkCnt, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronInitGroup3ToDevice(unsigned int idx, float* inSynInSyn11, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, unsigned int* denDelayPtrInSyn6, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, float* inSynInSyn12, float* denDelayInSyn12, unsigned int* denDelayPtrInSyn12, float* inSynInSyn13, float* denDelayInSyn13, unsigned int* denDelayPtrInSyn13, float* inSynInSyn14, float* denDelayInSyn14, unsigned int* denDelayPtrInSyn14, unsigned int* denDelayPtrInSyn2, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* inSynInSyn2, float* denDelayInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronInitGroup4ToDevice(unsigned int idx, float* denDelayInSyn9, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, unsigned int* denDelayPtrInSyn5, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, float* inSynInSyn11, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, float* inSynInSyn12, float* denDelayInSyn12, unsigned int* denDelayPtrInSyn12, float* inSynInSyn2, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronInitGroup5ToDevice(unsigned int idx, float* inSynInSyn8, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, unsigned int* denDelayPtrInSyn4, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, unsigned int* denDelayPtrInSyn1, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, float* inSynInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronInitGroup6ToDevice(unsigned int idx, float* inSynInSyn7, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn4, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* denDelayInSyn1, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, unsigned int* denDelayPtrInSyn1, float* inSynInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronInitGroup7ToDevice(unsigned int idx, unsigned int* denDelayPtrInSyn8, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, float* inSynInSyn5, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, float* inSynInSyn11, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, unsigned int* denDelayPtrInSyn1, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, float* inSynInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, unsigned int numNeurons);
EXPORT_FUNC void pushMergedSynapseConnectivityInitGroup0ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, uint16_t* preCalcRowLength, unsigned int numSrcNeurons, unsigned int numTrgNeurons, unsigned int rowStride);
EXPORT_FUNC void pushMergedSynapseConnectivityInit0preCalcRowLengthToDevice(unsigned int idx, uint16_t* value);
EXPORT_FUNC void pushMergedSynapseSparseInitGroup0ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, scalar* g, uint8_t* d, unsigned int numSrcNeurons, unsigned int numTrgNeurons, unsigned int rowStride, unsigned int colStride, scalar meang, scalar sdg, scalar ming, scalar maxg, scalar meanTimestepd, scalar sdTimestepd, scalar maxTimestepd);
EXPORT_FUNC void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, float* inSynInSyn3, unsigned int* denDelayPtrInSyn7, float* denDelayInSyn7, float* inSynInSyn7, unsigned int* denDelayPtrInSyn6, float* denDelayInSyn6, float* inSynInSyn6, unsigned int* denDelayPtrInSyn5, float* denDelayInSyn5, float* inSynInSyn5, unsigned int* denDelayPtrInSyn4, float* denDelayInSyn4, float* inSynInSyn4, unsigned int* denDelayPtrInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn2, float* denDelayInSyn2, float* inSynInSyn2, unsigned int* denDelayPtrInSyn1, float* denDelayInSyn1, float* inSynInSyn1, unsigned int* denDelayPtrInSyn0, float* denDelayInSyn0, float* inSynInSyn0, scalar* RefracTime, scalar* V, unsigned int* spk, unsigned int* spkCnt, unsigned int numNeurons, scalar Ioffset);
EXPORT_FUNC void pushMergedNeuronUpdateGroup1ToDevice(unsigned int idx, float* inSynInSyn10, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn6, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, float* inSynInSyn11, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, float* inSynInSyn12, float* denDelayInSyn12, unsigned int* denDelayPtrInSyn12, float* inSynInSyn13, float* denDelayInSyn13, unsigned int* denDelayPtrInSyn13, float* denDelayInSyn2, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* inSynInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronUpdateGroup2ToDevice(unsigned int idx, float* inSynInSyn8, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, unsigned int* denDelayPtrInSyn4, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, unsigned int* denDelayPtrInSyn1, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, float* inSynInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronUpdateGroup3ToDevice(unsigned int idx, float* inSynInSyn2, unsigned int* denDelayPtrInSyn5, float* denDelayInSyn5, float* inSynInSyn5, unsigned int* denDelayPtrInSyn4, float* denDelayInSyn4, float* inSynInSyn4, unsigned int* denDelayPtrInSyn3, float* denDelayInSyn3, float* inSynInSyn3, unsigned int* denDelayPtrInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn1, float* denDelayInSyn1, float* inSynInSyn1, unsigned int* denDelayPtrInSyn0, float* denDelayInSyn0, float* inSynInSyn0, scalar* RefracTime, scalar* V, unsigned int* spk, unsigned int* spkCnt, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronUpdateGroup4ToDevice(unsigned int idx, float* inSynInSyn11, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, unsigned int* denDelayPtrInSyn6, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, float* inSynInSyn12, float* denDelayInSyn12, unsigned int* denDelayPtrInSyn12, float* inSynInSyn13, float* denDelayInSyn13, unsigned int* denDelayPtrInSyn13, float* inSynInSyn14, float* denDelayInSyn14, unsigned int* denDelayPtrInSyn14, unsigned int* denDelayPtrInSyn2, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* inSynInSyn2, float* denDelayInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronUpdateGroup5ToDevice(unsigned int idx, float* denDelayInSyn9, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, unsigned int* denDelayPtrInSyn5, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, float* inSynInSyn11, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, float* inSynInSyn12, float* denDelayInSyn12, unsigned int* denDelayPtrInSyn12, float* inSynInSyn2, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronUpdateGroup6ToDevice(unsigned int idx, float* inSynInSyn7, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn4, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn1, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* inSynInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, unsigned int numNeurons, scalar Ioffset);
EXPORT_FUNC void pushMergedNeuronUpdateGroup7ToDevice(unsigned int idx, unsigned int* denDelayPtrInSyn8, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int* denDelayPtrInSyn7, float* inSynInSyn8, float* denDelayInSyn8, float* inSynInSyn5, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, float* inSynInSyn11, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, unsigned int* denDelayPtrInSyn1, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, float* inSynInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* inSynInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, unsigned int numNeurons, scalar Ioffset);
EXPORT_FUNC void pushMergedPresynapticUpdateGroup0ToDevice(unsigned int idx, float* denDelay, unsigned int* denDelayPtr, unsigned int* srcSpkCnt, unsigned int* srcSpk, unsigned int* rowLength, uint32_t* ind, scalar* g, uint8_t* d, unsigned int numSrcNeurons, unsigned int numTrgNeurons, unsigned int rowStride);
EXPORT_FUNC void pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt);
EXPORT_FUNC void pushMergedSynapseDendriticDelayUpdateGroup0ToDevice(unsigned int idx, unsigned int* denDelayPtr);
}  // extern "C"
