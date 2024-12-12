#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedSynapseDendriticDelayUpdateGroup0
 {
    unsigned int* denDelayPtr;
    
}
;
struct MergedPresynapticUpdateGroup0
 {
    float* denDelay;
    unsigned int* denDelayPtr;
    unsigned int* srcSpkCnt;
    unsigned int* srcSpk;
    unsigned int* rowLength;
    uint32_t* ind;
    scalar* g;
    uint8_t* d;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    unsigned int rowStride;
    
}
;
__device__ __constant__ MergedSynapseDendriticDelayUpdateGroup0 d_mergedSynapseDendriticDelayUpdateGroup0[186];
void pushMergedSynapseDendriticDelayUpdateGroup0ToDevice(unsigned int idx, unsigned int* denDelayPtr) {
    MergedSynapseDendriticDelayUpdateGroup0 group = {denDelayPtr, };
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedSynapseDendriticDelayUpdateGroup0, &group, sizeof(MergedSynapseDendriticDelayUpdateGroup0), idx * sizeof(MergedSynapseDendriticDelayUpdateGroup0)));
}
__device__ __constant__ MergedPresynapticUpdateGroup0 d_mergedPresynapticUpdateGroup0[186];
void pushMergedPresynapticUpdateGroup0ToDevice(unsigned int idx, float* denDelay, unsigned int* denDelayPtr, unsigned int* srcSpkCnt, unsigned int* srcSpk, unsigned int* rowLength, uint32_t* ind, scalar* g, uint8_t* d, unsigned int numSrcNeurons, unsigned int numTrgNeurons, unsigned int rowStride) {
    MergedPresynapticUpdateGroup0 group = {denDelay, denDelayPtr, srcSpkCnt, srcSpk, rowLength, ind, g, d, numSrcNeurons, numTrgNeurons, rowStride, };
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedPresynapticUpdateGroup0, &group, sizeof(MergedPresynapticUpdateGroup0), idx * sizeof(MergedPresynapticUpdateGroup0)));
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
__device__ __constant__ unsigned int d_mergedPresynapticUpdateGroupStartID0[] = {0, 1152, 1376, 1696, 1920, 2048, 2112, 2208, 2304, 2368, 2496, 2560, 3168, 4576, 4800, 4896, 4960, 5280, 5344, 5408, 5664, 5728, 5824, 5984, 6016, 6304, 6464, 7008, 7264, 7360, 7424, 7552, 7616, 7648, 7712, 7808, 7872, 7904, 8000, 8064, 8096, 8128, 8288, 8544, 8576, 8704, 8736, 8832, 8864, 8896, 9632, 10080, 10240, 10400, 10880, 10912, 10944, 11072, 13952, 14496, 14752, 14848, 15072, 15168, 15232, 15264, 15328, 15520, 15584, 16608, 19104, 19296, 19328, 19648, 19680, 19712, 19744, 19776, 19840, 19904, 19936, 21888, 22048, 22144, 22240, 22432, 22464, 22528, 22560, 22592, 22624, 22688, 22720, 24480, 26976, 27776, 28512, 28576, 28672, 28736, 28832, 28864, 28896, 31872, 32416, 32512, 33152, 33568, 33664, 33728, 33792, 34368, 34432, 35456, 37472, 37568, 37920, 37952, 38528, 38560, 38592, 38656, 38720, 38912, 38944, 40608, 41440, 42816, 42976, 43648, 43744, 44128, 44160, 44192, 44224, 44256, 44288, 44320, 44416, 44448, 44736, 45472, 45536, 45600, 45664, 45728, 45760, 45792, 46464, 47008, 47040, 47136, 47360, 47424, 47488, 47552, 48576, 50592, 50624, 50656, 50688, 50720, 50976, 51008, 51072, 51104, 51136, 51616, 52192, 52352, 52448, 52480, 52512, 52576, 52832, 52864, 52896, 52928, 52960, 53248, 53984, 54048, 54112, 54176, 54240, 54272, };
extern "C" __global__ void synapseDendriticDelayUpdateKernel() {
    const unsigned int id = 32 * blockIdx.x + threadIdx.x;
    // merged0
    if(id < 186) {
        struct MergedSynapseDendriticDelayUpdateGroup0 *group = &d_mergedSynapseDendriticDelayUpdateGroup0[id - 0]; 
        *group->denDelayPtr = (*group->denDelayPtr + 1) % 43;
    }
    
}

extern "C" __global__ void updatePresynapticKernel(float t)
 {
    const unsigned int id = 32 * blockIdx.x + threadIdx.x; 
    __shared__ unsigned int shRowLength[32];
    __shared__ unsigned int shSpk[32];
    // merged0
    if(id < 54304) {
        unsigned int lo = 0;
        unsigned int hi = 186;
        while(lo < hi)
         {
            const unsigned int mid = (lo + hi) / 2;
            if(id < d_mergedPresynapticUpdateGroupStartID0[mid]) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        struct MergedPresynapticUpdateGroup0 *group = &d_mergedPresynapticUpdateGroup0[lo - 1]; 
        const unsigned int groupStartID = d_mergedPresynapticUpdateGroupStartID0[lo - 1];
        const unsigned int lid = id - groupStartID;
         {
            const unsigned int numSpikes = group->srcSpkCnt[0];
            const unsigned int numSpikeBlocks = (numSpikes + 32 - 1) / 32;
            for (unsigned int r = 0; r < numSpikeBlocks; r++) {
                const unsigned int numSpikesInBlock = (r == numSpikeBlocks - 1) ? ((numSpikes - 1) % 32) + 1 : 32;
                __syncthreads();
                if (threadIdx.x < numSpikesInBlock) {
                    const unsigned int spk = group->srcSpk[(r * 32) + threadIdx.x];
                    shSpk[threadIdx.x] = spk;
                    shRowLength[threadIdx.x] = group->rowLength[spk];
                }
                __syncthreads();
                // loop through all incoming spikes
                for (unsigned int j = 0; j < numSpikesInBlock; j++) {
                    // only work on existing neurons
                    if (lid < group->rowStride) {
                        const unsigned int synAddress = (shSpk[j] * group->rowStride) + lid;
                        const unsigned int npost = shRowLength[j];
                        if (lid < npost) {
                            const unsigned int ipost = group->ind[synAddress];
                            atomicAdd(&group->denDelay[(((*group->denDelayPtr + group->d[synAddress]) % 43) * group->numTrgNeurons) + ipost], group->g[synAddress]);
                        }
                    }
                }
            }
        }
        
    }
}
void updateSynapses(float t) {
     {
        const dim3 threads(32, 1);
        const dim3 grid(6, 1);
        synapseDendriticDelayUpdateKernel<<<grid, threads>>>();
        CHECK_CUDA_ERRORS(cudaPeekAtLastError());
    }
     {
        CHECK_CUDA_ERRORS(cudaEventRecord(presynapticUpdateStart));
        const dim3 threads(32, 1);
        const dim3 grid(1697, 1);
        updatePresynapticKernel<<<grid, threads>>>(t);
        CHECK_CUDA_ERRORS(cudaPeekAtLastError());
        CHECK_CUDA_ERRORS(cudaEventRecord(presynapticUpdateStop));
    }
}
