#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedNeuronUpdateGroup0
 {
    float* inSynInSyn9;
    unsigned int* denDelayPtrInSyn11;
    float* denDelayInSyn11;
    float* inSynInSyn11;
    unsigned int* denDelayPtrInSyn10;
    float* denDelayInSyn10;
    float* inSynInSyn10;
    unsigned int* denDelayPtrInSyn9;
    float* denDelayInSyn9;
    float* inSynInSyn12;
    unsigned int* denDelayPtrInSyn8;
    float* denDelayInSyn8;
    float* inSynInSyn8;
    unsigned int* denDelayPtrInSyn7;
    float* denDelayInSyn7;
    float* inSynInSyn7;
    unsigned int* denDelayPtrInSyn6;
    float* denDelayInSyn6;
    float* denDelayInSyn12;
    unsigned int* denDelayPtrInSyn12;
    float* inSynInSyn13;
    float* denDelayInSyn13;
    unsigned int* denDelayPtrInSyn13;
    float* inSynInSyn14;
    float* denDelayInSyn14;
    unsigned int* denDelayPtrInSyn14;
    float* inSynInSyn15;
    float* denDelayInSyn15;
    unsigned int* denDelayPtrInSyn15;
    float* inSynInSyn16;
    float* denDelayInSyn16;
    unsigned int* denDelayPtrInSyn16;
    uint32_t* recordSpk;
    float* inSynInSyn1;
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* V;
    scalar* RefracTime;
    float* inSynInSyn0;
    float* denDelayInSyn0;
    unsigned int* denDelayPtrInSyn0;
    float* denDelayInSyn1;
    unsigned int* denDelayPtrInSyn1;
    float* inSynInSyn2;
    float* denDelayInSyn2;
    float* inSynInSyn3;
    float* inSynInSyn6;
    unsigned int* denDelayPtrInSyn5;
    float* denDelayInSyn5;
    float* inSynInSyn5;
    unsigned int* denDelayPtrInSyn4;
    float* denDelayInSyn4;
    float* inSynInSyn4;
    unsigned int* denDelayPtrInSyn3;
    float* denDelayInSyn3;
    unsigned int* denDelayPtrInSyn2;
    scalar Rmembrane;
    scalar ExpTC;
    scalar TauRefrac;
    scalar Ioffset;
    scalar Vreset;
    scalar Vrest;
    scalar TauM;
    scalar C;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup0
 {
    unsigned int* spkCnt;
    
}
;
__device__ __constant__ MergedNeuronSpikeQueueUpdateGroup0 d_mergedNeuronSpikeQueueUpdateGroup0[17];
void pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt) {
    MergedNeuronSpikeQueueUpdateGroup0 group = {spkCnt, };
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedNeuronSpikeQueueUpdateGroup0, &group, sizeof(MergedNeuronSpikeQueueUpdateGroup0), idx * sizeof(MergedNeuronSpikeQueueUpdateGroup0)));
}
__device__ __constant__ MergedNeuronUpdateGroup0 d_mergedNeuronUpdateGroup0[17];
void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, float* inSynInSyn9, unsigned int* denDelayPtrInSyn11, float* denDelayInSyn11, float* inSynInSyn11, unsigned int* denDelayPtrInSyn10, float* denDelayInSyn10, float* inSynInSyn10, unsigned int* denDelayPtrInSyn9, float* denDelayInSyn9, float* inSynInSyn12, unsigned int* denDelayPtrInSyn8, float* denDelayInSyn8, float* inSynInSyn8, unsigned int* denDelayPtrInSyn7, float* denDelayInSyn7, float* inSynInSyn7, unsigned int* denDelayPtrInSyn6, float* denDelayInSyn6, float* denDelayInSyn12, unsigned int* denDelayPtrInSyn12, float* inSynInSyn13, float* denDelayInSyn13, unsigned int* denDelayPtrInSyn13, float* inSynInSyn14, float* denDelayInSyn14, unsigned int* denDelayPtrInSyn14, float* inSynInSyn15, float* denDelayInSyn15, unsigned int* denDelayPtrInSyn15, float* inSynInSyn16, float* denDelayInSyn16, unsigned int* denDelayPtrInSyn16, uint32_t* recordSpk, float* inSynInSyn1, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* inSynInSyn2, float* denDelayInSyn2, float* inSynInSyn3, float* inSynInSyn6, unsigned int* denDelayPtrInSyn5, float* denDelayInSyn5, float* inSynInSyn5, unsigned int* denDelayPtrInSyn4, float* denDelayInSyn4, float* inSynInSyn4, unsigned int* denDelayPtrInSyn3, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn2, scalar Rmembrane, scalar ExpTC, scalar TauRefrac, scalar Ioffset, scalar Vreset, scalar Vrest, scalar TauM, scalar C, unsigned int numNeurons) {
    MergedNeuronUpdateGroup0 group = {inSynInSyn9, denDelayPtrInSyn11, denDelayInSyn11, inSynInSyn11, denDelayPtrInSyn10, denDelayInSyn10, inSynInSyn10, denDelayPtrInSyn9, denDelayInSyn9, inSynInSyn12, denDelayPtrInSyn8, denDelayInSyn8, inSynInSyn8, denDelayPtrInSyn7, denDelayInSyn7, inSynInSyn7, denDelayPtrInSyn6, denDelayInSyn6, denDelayInSyn12, denDelayPtrInSyn12, inSynInSyn13, denDelayInSyn13, denDelayPtrInSyn13, inSynInSyn14, denDelayInSyn14, denDelayPtrInSyn14, inSynInSyn15, denDelayInSyn15, denDelayPtrInSyn15, inSynInSyn16, denDelayInSyn16, denDelayPtrInSyn16, recordSpk, inSynInSyn1, spkCnt, spk, V, RefracTime, inSynInSyn0, denDelayInSyn0, denDelayPtrInSyn0, denDelayInSyn1, denDelayPtrInSyn1, inSynInSyn2, denDelayInSyn2, inSynInSyn3, inSynInSyn6, denDelayPtrInSyn5, denDelayInSyn5, inSynInSyn5, denDelayPtrInSyn4, denDelayInSyn4, inSynInSyn4, denDelayPtrInSyn3, denDelayInSyn3, denDelayPtrInSyn2, Rmembrane, ExpTC, TauRefrac, Ioffset, Vreset, Vrest, TauM, C, numNeurons, };
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedNeuronUpdateGroup0, &group, sizeof(MergedNeuronUpdateGroup0), idx * sizeof(MergedNeuronUpdateGroup0)));
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
void pushMergedNeuronUpdate0recordSpkToDevice(unsigned int idx, uint32_t* value) {
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedNeuronUpdateGroup0, &value, sizeof(value), (sizeof(MergedNeuronUpdateGroup0) * (idx)) + offsetof(MergedNeuronUpdateGroup0, recordSpk)));
}

__device__ __constant__ unsigned int d_mergedNeuronUpdateGroupStartID0[] = {0, 51776, 126720, 148352, 168640, 184192, 186816, 193856, 195648, 197312, 199232, 203328, 204928, 206656, 211200, 213184, 213568, };

extern "C" __global__ void neuronSpikeQueueUpdateKernel() {
    const unsigned int id = 32 * blockIdx.x + threadIdx.x;
    if(id < 17) {
        struct MergedNeuronSpikeQueueUpdateGroup0 *group = &d_mergedNeuronSpikeQueueUpdateGroup0[id - 0]; 
        group->spkCnt[0] = 0;
    }
}

extern "C" __global__ void updateNeuronsKernel(float t, unsigned int recordingTimestep)
 {
    const unsigned int id = 64 * blockIdx.x + threadIdx.x; 
    __shared__ unsigned int shSpk[64];
    __shared__ unsigned int shPosSpk;
    __shared__ unsigned int shSpkCount;
    if (threadIdx.x == 0) {
        shSpkCount = 0;
    }
    
    __shared__ uint32_t shSpkRecord[2];
    if (threadIdx.x < 2) {
        shSpkRecord[threadIdx.x] = 0;
    }
    __syncthreads();
    // merged0
    if(id < 213888) {
        unsigned int lo = 0;
        unsigned int hi = 17;
        while(lo < hi)
         {
            const unsigned int mid = (lo + hi) / 2;
            if(id < d_mergedNeuronUpdateGroupStartID0[mid]) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        struct MergedNeuronUpdateGroup0 *group = &d_mergedNeuronUpdateGroup0[lo - 1]; 
        const unsigned int groupStartID = d_mergedNeuronUpdateGroupStartID0[lo - 1];
        const unsigned int lid = id - groupStartID;
        
        if(lid < group->numNeurons) {
            scalar lV = group->V[lid];
            scalar lRefracTime = group->RefracTime[lid];
            
            float Isyn = 0;
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn0[lid];
                float *denDelayFront = &group->denDelayInSyn0[(*group->denDelayPtrInSyn0 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn0[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn1[lid];
                float *denDelayFront = &group->denDelayInSyn1[(*group->denDelayPtrInSyn1 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn1[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn2[lid];
                float *denDelayFront = &group->denDelayInSyn2[(*group->denDelayPtrInSyn2 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn2[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn3[lid];
                float *denDelayFront = &group->denDelayInSyn3[(*group->denDelayPtrInSyn3 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn3[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn4[lid];
                float *denDelayFront = &group->denDelayInSyn4[(*group->denDelayPtrInSyn4 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn4[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn5[lid];
                float *denDelayFront = &group->denDelayInSyn5[(*group->denDelayPtrInSyn5 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn5[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn6[lid];
                float *denDelayFront = &group->denDelayInSyn6[(*group->denDelayPtrInSyn6 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn6[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn7[lid];
                float *denDelayFront = &group->denDelayInSyn7[(*group->denDelayPtrInSyn7 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn7[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn8[lid];
                float *denDelayFront = &group->denDelayInSyn8[(*group->denDelayPtrInSyn8 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn8[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn9[lid];
                float *denDelayFront = &group->denDelayInSyn9[(*group->denDelayPtrInSyn9 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn9[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn10[lid];
                float *denDelayFront = &group->denDelayInSyn10[(*group->denDelayPtrInSyn10 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn10[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn11[lid];
                float *denDelayFront = &group->denDelayInSyn11[(*group->denDelayPtrInSyn11 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn11[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn12[lid];
                float *denDelayFront = &group->denDelayInSyn12[(*group->denDelayPtrInSyn12 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn12[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn13[lid];
                float *denDelayFront = &group->denDelayInSyn13[(*group->denDelayPtrInSyn13 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn13[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn14[lid];
                float *denDelayFront = &group->denDelayInSyn14[(*group->denDelayPtrInSyn14 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn14[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn15[lid];
                float *denDelayFront = &group->denDelayInSyn15[(*group->denDelayPtrInSyn15 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn15[lid] = linSyn;
            }
             {
                // pull inSyn values in a coalesced access
                float linSyn = group->inSynInSyn16[lid];
                float *denDelayFront = &group->denDelayInSyn16[(*group->denDelayPtrInSyn16 * group->numNeurons) + lid];
                linSyn += *denDelayFront;
                *denDelayFront = 0.000000000e+00f;
                Isyn += (9.06346234610090895e-01f) * linSyn;
                linSyn *= (8.18730753077981821e-01f);
                group->inSynInSyn16[lid] = linSyn;
            }
            // test whether spike condition was fulfilled previously
            // calculate membrane potential
            if (lRefracTime <= 0.0f) {
              scalar alpha = ((Isyn + group->Ioffset) * group->Rmembrane) + group->Vrest;
              lV = alpha - (group->ExpTC * (alpha - lV));
            }
            else {
              lRefracTime -= DT;
            }
            
            // test for and register a true spike
            if (lRefracTime <= 0.0f && lV >= (-5.00000000000000000e+01f)) {
                const unsigned int spkIdx = atomicAdd(&shSpkCount, 1);
                shSpk[spkIdx] = lid;
                atomicOr(&shSpkRecord[threadIdx.x / 32], 1 << (threadIdx.x % 32));
                // spike reset code
                lV = group->Vreset;
                lRefracTime = group->TauRefrac;
                
            }
            group->V[lid] = lV;
            group->RefracTime[lid] = lRefracTime;
        }
        __syncthreads();
        if(threadIdx.x == 0) {
            if (shSpkCount > 0) {
                shPosSpk = atomicAdd(&group->spkCnt[0], shSpkCount);
            }
        }
        __syncthreads();
        if(threadIdx.x < shSpkCount) {
            const unsigned int n = shSpk[threadIdx.x];
            group->spk[shPosSpk + threadIdx.x] = n;
        }
        if(threadIdx.x < 2) {
            const unsigned int numRecordingWords = (group->numNeurons + 31) / 32;
            const unsigned int popWordIdx = (lid / 32) + threadIdx.x;
            if(popWordIdx < numRecordingWords) {
                group->recordSpk[(recordingTimestep * numRecordingWords * 1) + popWordIdx] = shSpkRecord[threadIdx.x];
            }
        }
    }
}
void updateNeurons(float t, unsigned int recordingTimestep) {
     {
        const dim3 threads(32, 1);
        const dim3 grid(1, 1);
        neuronSpikeQueueUpdateKernel<<<grid, threads>>>();
        CHECK_CUDA_ERRORS(cudaPeekAtLastError());
    }
     {
        const dim3 threads(64, 1);
        const dim3 grid(3342, 1);
        updateNeuronsKernel<<<grid, threads>>>(t, recordingTimestep);
        CHECK_CUDA_ERRORS(cudaPeekAtLastError());
    }
}
