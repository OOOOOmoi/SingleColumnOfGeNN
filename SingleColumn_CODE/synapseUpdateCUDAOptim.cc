#include "definitionsInternalCUDAOptim.h"
#include "supportCodeCUDAOptim.h"

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
__device__ __constant__ unsigned int d_mergedPresynapticUpdateGroupStartID0[] = {0, 1152, 1408, 1728, 1984, 2112, 2176, 2304, 2432, 2496, 2624, 2688, 3328, 4736, 4992, 5120, 5184, 5504, 5568, 5632, 5888, 5952, 6080, 6272, 6336, 6656, 6848, 7424, 7680, 7808, 7872, 8000, 8064, 8128, 8192, 8320, 8384, 8448, 8576, 8640, 8704, 8768, 8960, 9216, 9280, 9408, 9472, 9600, 9664, 9728, 10496, 10944, 11136, 11328, 11840, 11904, 11968, 12096, 14976, 15552, 15808, 15936, 16192, 16320, 16384, 16448, 16512, 16704, 16768, 17792, 20288, 20480, 20544, 20864, 20928, 20992, 21056, 21120, 21184, 21248, 21312, 23296, 23488, 23616, 23744, 23936, 24000, 24064, 24128, 24192, 24256, 24320, 24384, 26176, 28672, 29504, 30272, 30336, 30464, 30528, 30656, 30720, 30784, 33792, 34368, 34496, 35136, 35584, 35712, 35776, 35840, 36416, 36480, 37504, 39552, 39680, 40064, 40128, 40704, 40768, 40832, 40896, 40960, 41152, 41216, 42880, 43712, 45120, 45312, 46016, 46144, 46528, 46592, 46656, 46720, 46784, 46848, 46912, 47040, 47104, 47424, 48192, 48256, 48320, 48384, 48448, 48512, 48576, 49280, 49856, 49920, 50048, 50304, 50368, 50432, 50496, 51520, 53568, 53632, 53696, 53760, 53824, 54080, 54144, 54208, 54272, 54336, 54848, 55424, 55616, 55744, 55808, 55872, 55936, 56192, 56256, 56320, 56384, 56448, 56768, 57536, 57600, 57664, 57728, 57792, 57856, };
extern "C" __global__ void synapseDendriticDelayUpdateKernel() {
    const unsigned int id = 64 * blockIdx.x + threadIdx.x;
    // merged0
    if(id < 186) {
        struct MergedSynapseDendriticDelayUpdateGroup0 *group = &d_mergedSynapseDendriticDelayUpdateGroup0[id - 0]; 
        *group->denDelayPtr = (*group->denDelayPtr + 1) % 29;
    }
    
}

extern "C" __global__ void updatePresynapticKernel(float t)
 {
    const unsigned int id = 64 * blockIdx.x + threadIdx.x; 
    __shared__ unsigned int shRowLength[64];
    __shared__ unsigned int shSpk[64];
    // merged0
    if(id < 57920) {
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
            const unsigned int numSpikeBlocks = (numSpikes + 64 - 1) / 64;
            for (unsigned int r = 0; r < numSpikeBlocks; r++) {
                const unsigned int numSpikesInBlock = (r == numSpikeBlocks - 1) ? ((numSpikes - 1) % 64) + 1 : 64;
                __syncthreads();
                if (threadIdx.x < numSpikesInBlock) {
                    const unsigned int spk = group->srcSpk[(r * 64) + threadIdx.x];
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
                            atomicAdd(&group->denDelay[(((*group->denDelayPtr + group->d[synAddress]) % 29) * group->numTrgNeurons) + ipost], group->g[synAddress]);
                        }
                    }
                }
            }
        }
        
    }
}
void updateSynapses(float t) {
     {
        const dim3 threads(64, 1);
        const dim3 grid(3, 1);
        synapseDendriticDelayUpdateKernel<<<grid, threads>>>();
        CHECK_CUDA_ERRORS(cudaPeekAtLastError());
    }
     {
        CHECK_CUDA_ERRORS(cudaEventRecord(presynapticUpdateStart));
        const dim3 threads(64, 1);
        const dim3 grid(905, 1);
        updatePresynapticKernel<<<grid, threads>>>(t);
        CHECK_CUDA_ERRORS(cudaPeekAtLastError());
        CHECK_CUDA_ERRORS(cudaEventRecord(presynapticUpdateStop));
    }
}
