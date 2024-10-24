#include "definitionsInternal.h"
#include <iostream>
#include <random>
#include <cstdint>

struct MergedNeuronInitGroup0
 {
    float* denDelayInSyn12;
    float* inSynInSyn8;
    float* denDelayInSyn8;
    unsigned int* denDelayPtrInSyn8;
    float* inSynInSyn9;
    float* denDelayInSyn9;
    unsigned int* denDelayPtrInSyn9;
    float* inSynInSyn10;
    float* denDelayInSyn10;
    unsigned int* denDelayPtrInSyn10;
    float* inSynInSyn11;
    float* denDelayInSyn11;
    unsigned int* denDelayPtrInSyn11;
    float* inSynInSyn12;
    unsigned int* denDelayPtrInSyn7;
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
    float* inSynInSyn3;
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* V;
    scalar* RefracTime;
    float* inSynInSyn0;
    float* denDelayInSyn0;
    unsigned int* denDelayPtrInSyn0;
    float* inSynInSyn1;
    float* denDelayInSyn1;
    unsigned int* denDelayPtrInSyn1;
    float* inSynInSyn2;
    float* denDelayInSyn2;
    unsigned int* denDelayPtrInSyn2;
    float* denDelayInSyn3;
    unsigned int* denDelayPtrInSyn3;
    float* inSynInSyn4;
    float* denDelayInSyn4;
    unsigned int* denDelayPtrInSyn4;
    float* inSynInSyn5;
    float* denDelayInSyn5;
    unsigned int* denDelayPtrInSyn5;
    float* inSynInSyn6;
    float* denDelayInSyn6;
    unsigned int* denDelayPtrInSyn6;
    float* inSynInSyn7;
    float* denDelayInSyn7;
    unsigned int numNeurons;
    
}
;
struct MergedSynapseConnectivityInitGroup0
 {
    unsigned int* rowLength;
    uint32_t* ind;
    uint16_t* preCalcRowLength;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    unsigned int rowStride;
    
}
;
struct MergedSynapseSparseInitGroup0
 {
    unsigned int* rowLength;
    uint32_t* ind;
    scalar* g;
    uint8_t* d;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    unsigned int rowStride;
    unsigned int colStride;
    scalar meang;
    scalar sdg;
    scalar ming;
    scalar maxg;
    scalar meanTimestepd;
    scalar sdTimestepd;
    scalar maxTimestepd;
    
}
;
__device__ __constant__ MergedNeuronInitGroup0 d_mergedNeuronInitGroup0[17];
void pushMergedNeuronInitGroup0ToDevice(unsigned int idx, float* denDelayInSyn12, float* inSynInSyn8, float* denDelayInSyn8, unsigned int* denDelayPtrInSyn8, float* inSynInSyn9, float* denDelayInSyn9, unsigned int* denDelayPtrInSyn9, float* inSynInSyn10, float* denDelayInSyn10, unsigned int* denDelayPtrInSyn10, float* inSynInSyn11, float* denDelayInSyn11, unsigned int* denDelayPtrInSyn11, float* inSynInSyn12, unsigned int* denDelayPtrInSyn7, unsigned int* denDelayPtrInSyn12, float* inSynInSyn13, float* denDelayInSyn13, unsigned int* denDelayPtrInSyn13, float* inSynInSyn14, float* denDelayInSyn14, unsigned int* denDelayPtrInSyn14, float* inSynInSyn15, float* denDelayInSyn15, unsigned int* denDelayPtrInSyn15, float* inSynInSyn16, float* denDelayInSyn16, unsigned int* denDelayPtrInSyn16, float* inSynInSyn3, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* denDelayInSyn0, unsigned int* denDelayPtrInSyn0, float* inSynInSyn1, float* denDelayInSyn1, unsigned int* denDelayPtrInSyn1, float* inSynInSyn2, float* denDelayInSyn2, unsigned int* denDelayPtrInSyn2, float* denDelayInSyn3, unsigned int* denDelayPtrInSyn3, float* inSynInSyn4, float* denDelayInSyn4, unsigned int* denDelayPtrInSyn4, float* inSynInSyn5, float* denDelayInSyn5, unsigned int* denDelayPtrInSyn5, float* inSynInSyn6, float* denDelayInSyn6, unsigned int* denDelayPtrInSyn6, float* inSynInSyn7, float* denDelayInSyn7, unsigned int numNeurons) {
    MergedNeuronInitGroup0 group = {denDelayInSyn12, inSynInSyn8, denDelayInSyn8, denDelayPtrInSyn8, inSynInSyn9, denDelayInSyn9, denDelayPtrInSyn9, inSynInSyn10, denDelayInSyn10, denDelayPtrInSyn10, inSynInSyn11, denDelayInSyn11, denDelayPtrInSyn11, inSynInSyn12, denDelayPtrInSyn7, denDelayPtrInSyn12, inSynInSyn13, denDelayInSyn13, denDelayPtrInSyn13, inSynInSyn14, denDelayInSyn14, denDelayPtrInSyn14, inSynInSyn15, denDelayInSyn15, denDelayPtrInSyn15, inSynInSyn16, denDelayInSyn16, denDelayPtrInSyn16, inSynInSyn3, spkCnt, spk, V, RefracTime, inSynInSyn0, denDelayInSyn0, denDelayPtrInSyn0, inSynInSyn1, denDelayInSyn1, denDelayPtrInSyn1, inSynInSyn2, denDelayInSyn2, denDelayPtrInSyn2, denDelayInSyn3, denDelayPtrInSyn3, inSynInSyn4, denDelayInSyn4, denDelayPtrInSyn4, inSynInSyn5, denDelayInSyn5, denDelayPtrInSyn5, inSynInSyn6, denDelayInSyn6, denDelayPtrInSyn6, inSynInSyn7, denDelayInSyn7, numNeurons, };
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedNeuronInitGroup0, &group, sizeof(MergedNeuronInitGroup0), idx * sizeof(MergedNeuronInitGroup0)));
}
__device__ __constant__ MergedSynapseConnectivityInitGroup0 d_mergedSynapseConnectivityInitGroup0[289];
void pushMergedSynapseConnectivityInitGroup0ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, uint16_t* preCalcRowLength, unsigned int numSrcNeurons, unsigned int numTrgNeurons, unsigned int rowStride) {
    MergedSynapseConnectivityInitGroup0 group = {rowLength, ind, preCalcRowLength, numSrcNeurons, numTrgNeurons, rowStride, };
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedSynapseConnectivityInitGroup0, &group, sizeof(MergedSynapseConnectivityInitGroup0), idx * sizeof(MergedSynapseConnectivityInitGroup0)));
}
__device__ MergedSynapseSparseInitGroup0 d_mergedSynapseSparseInitGroup0[289];
void pushMergedSynapseSparseInitGroup0ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, scalar* g, uint8_t* d, unsigned int numSrcNeurons, unsigned int numTrgNeurons, unsigned int rowStride, unsigned int colStride, scalar meang, scalar sdg, scalar ming, scalar maxg, scalar meanTimestepd, scalar sdTimestepd, scalar maxTimestepd) {
    MergedSynapseSparseInitGroup0 group = {rowLength, ind, g, d, numSrcNeurons, numTrgNeurons, rowStride, colStride, meang, sdg, ming, maxg, meanTimestepd, sdTimestepd, maxTimestepd, };
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedSynapseSparseInitGroup0, &group, sizeof(MergedSynapseSparseInitGroup0), idx * sizeof(MergedSynapseSparseInitGroup0)));
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
void pushMergedSynapseConnectivityInit0preCalcRowLengthToDevice(unsigned int idx, uint16_t* value) {
    CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_mergedSynapseConnectivityInitGroup0, &value, sizeof(value), (sizeof(MergedSynapseConnectivityInitGroup0) * (idx)) + offsetof(MergedSynapseConnectivityInitGroup0, preCalcRowLength)));
}

// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
__device__ unsigned int d_mergedNeuronInitGroupStartID0[] = {0, 51776, 126720, 148352, 168640, 184192, 186816, 193856, 195648, 197312, 199232, 203328, 204928, 206656, 211200, 213184, 213568, };
__device__ unsigned int d_mergedSynapseConnectivityInitGroupStartID0[] = {213888, 265664, 317440, 369216, 420992, 472768, 524544, 576320, 628096, 679872, 731648, 783424, 835200, 886976, 938752, 990528, 1042304, 1094080, 1169024, 1243968, 1318912, 1393856, 1468800, 1543744, 1618688, 1693632, 1768576, 1843520, 1918464, 1993408, 2068352, 2143296, 2218240, 2293184, 2368128, 2389760, 2411392, 2433024, 2454656, 2476288, 2497920, 2519552, 2541184, 2562816, 2584448, 2606080, 2627712, 2649344, 2670976, 2692608, 2714240, 2735872, 2756160, 2776448, 2796736, 2817024, 2837312, 2857600, 2877888, 2898176, 2918464, 2938752, 2959040, 2979328, 2999616, 3019904, 3040192, 3060480, 3080768, 3096320, 3111872, 3127424, 3142976, 3158528, 3174080, 3189632, 3205184, 3220736, 3236288, 3251840, 3267392, 3282944, 3298496, 3314048, 3329600, 3345152, 3347776, 3350400, 3353024, 3355648, 3358272, 3360896, 3363520, 3366144, 3368768, 3371392, 3374016, 3376640, 3379264, 3381888, 3384512, 3387136, 3389760, 3396800, 3403840, 3410880, 3417920, 3424960, 3432000, 3439040, 3446080, 3453120, 3460160, 3467200, 3474240, 3481280, 3488320, 3495360, 3502400, 3509440, 3511232, 3513024, 3514816, 3516608, 3518400, 3520192, 3521984, 3523776, 3525568, 3527360, 3529152, 3530944, 3532736, 3534528, 3536320, 3538112, 3539904, 3541568, 3543232, 3544896, 3546560, 3548224, 3549888, 3551552, 3553216, 3554880, 3556544, 3558208, 3559872, 3561536, 3563200, 3564864, 3566528, 3568192, 3570112, 3572032, 3573952, 3575872, 3577792, 3579712, 3581632, 3583552, 3585472, 3587392, 3589312, 3591232, 3593152, 3595072, 3596992, 3598912, 3600832, 3604928, 3609024, 3613120, 3617216, 3621312, 3625408, 3629504, 3633600, 3637696, 3641792, 3645888, 3649984, 3654080, 3658176, 3662272, 3666368, 3670464, 3672064, 3673664, 3675264, 3676864, 3678464, 3680064, 3681664, 3683264, 3684864, 3686464, 3688064, 3689664, 3691264, 3692864, 3694464, 3696064, 3697664, 3699392, 3701120, 3702848, 3704576, 3706304, 3708032, 3709760, 3711488, 3713216, 3714944, 3716672, 3718400, 3720128, 3721856, 3723584, 3725312, 3727040, 3731584, 3736128, 3740672, 3745216, 3749760, 3754304, 3758848, 3763392, 3767936, 3772480, 3777024, 3781568, 3786112, 3790656, 3795200, 3799744, 3804288, 3806272, 3808256, 3810240, 3812224, 3814208, 3816192, 3818176, 3820160, 3822144, 3824128, 3826112, 3828096, 3830080, 3832064, 3834048, 3836032, 3838016, 3838400, 3838784, 3839168, 3839552, 3839936, 3840320, 3840704, 3841088, 3841472, 3841856, 3842240, 3842624, 3843008, 3843392, 3843776, 3844160, 3844544, 3844864, 3845184, 3845504, 3845824, 3846144, 3846464, 3846784, 3847104, 3847424, 3847744, 3848064, 3848384, 3848704, 3849024, 3849344, 3849664, };
__device__ unsigned int d_mergedSynapseSparseInitGroupStartID0[] = {0, 1152, 1408, 1728, 1728, 1728, 1984, 2112, 2176, 2176, 2304, 2432, 2496, 2496, 2624, 2688, 2688, 2688, 3328, 4736, 4992, 5120, 5120, 5184, 5504, 5568, 5568, 5632, 5888, 5952, 5952, 6080, 6272, 6336, 6336, 6656, 6848, 7424, 7680, 7808, 7872, 8000, 8064, 8128, 8192, 8320, 8384, 8448, 8576, 8640, 8704, 8768, 8768, 8768, 8960, 9216, 9216, 9216, 9216, 9280, 9408, 9408, 9408, 9472, 9600, 9600, 9600, 9664, 9728, 10496, 10944, 11136, 11328, 11840, 11904, 11904, 11904, 11904, 11968, 11968, 11968, 11968, 12096, 12096, 12096, 12096, 14976, 15552, 15808, 15808, 15936, 16192, 16320, 16384, 16384, 16448, 16512, 16512, 16512, 16704, 16768, 16768, 16768, 17792, 20288, 20480, 20480, 20480, 20544, 20864, 20928, 20928, 20992, 21056, 21120, 21120, 21184, 21248, 21312, 21312, 21312, 21312, 23296, 23488, 23488, 23616, 23744, 23936, 24000, 24000, 24064, 24128, 24192, 24192, 24256, 24320, 24384, 26176, 28672, 29504, 30272, 30272, 30272, 30272, 30336, 30464, 30464, 30464, 30528, 30656, 30656, 30656, 30720, 30784, 33792, 34368, 34496, 34496, 35136, 35584, 35712, 35712, 35712, 35776, 35840, 35840, 35840, 36416, 36480, 36480, 36480, 37504, 39552, 39680, 39680, 40064, 40128, 40704, 40768, 40768, 40832, 40896, 40896, 40896, 40960, 41152, 41216, 41216, 42880, 43712, 45120, 45312, 46016, 46016, 46144, 46528, 46592, 46656, 46720, 46784, 46848, 46848, 46912, 47040, 47104, 47104, 47104, 47424, 48192, 48192, 48192, 48192, 48256, 48320, 48320, 48320, 48384, 48448, 48448, 48448, 48512, 48576, 49280, 49856, 49856, 49856, 49856, 49920, 50048, 50048, 50048, 50304, 50368, 50368, 50368, 50432, 50496, 50496, 50496, 51520, 53568, 53568, 53568, 53568, 53632, 53696, 53760, 53760, 53824, 54080, 54144, 54144, 54208, 54272, 54336, 54336, 54336, 54848, 55424, 55616, 55616, 55616, 55744, 55808, 55872, 55872, 55936, 56192, 56256, 56256, 56320, 56384, 56448, 56448, 56448, 56768, 57536, 57536, 57536, 57536, 57600, 57664, 57664, 57664, 57728, 57792, 57792, 57792, 57856, };

extern "C" __global__ void initializeRNGKernel(unsigned long long deviceRNGSeed) {
    if(threadIdx.x == 0) {
        curand_init(deviceRNGSeed, 0, 0, &d_rng);
    }
}

extern "C" __global__ void initializeKernel(unsigned long long deviceRNGSeed) {
    const unsigned int id = 64 * blockIdx.x + threadIdx.x;
    // ------------------------------------------------------------------------
    // Local neuron groups
    // merged0
    if(id < 213888) {
        unsigned int lo = 0;
        unsigned int hi = 17;
        while(lo < hi)
         {
            const unsigned int mid = (lo + hi) / 2;
            if(id < d_mergedNeuronInitGroupStartID0[mid]) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        struct MergedNeuronInitGroup0 *group = &d_mergedNeuronInitGroup0[lo - 1]; 
        const unsigned int groupStartID = d_mergedNeuronInitGroupStartID0[lo - 1];
        const unsigned int lid = id - groupStartID;
        // only do this for existing neurons
        if(lid < group->numNeurons) {
            curandStatePhilox4_32_10_t localRNG = d_rng;
            skipahead_sequence((unsigned long long)id, &localRNG);
            if(lid == 0) {
                group->spkCnt[0] = 0;
            }
            group->spk[lid] = 0;
             {
                scalar initVal;
                initVal = (-1.50000000000000000e+02f) + (curand_normal(&localRNG) * (5.00000000000000000e+01f));
                group->V[lid] = initVal;
            }
             {
                scalar initVal;
                initVal = (0.00000000000000000e+00f);
                group->RefracTime[lid] = initVal;
            }
             {
                group->inSynInSyn0[lid] = 0.000000000e+00f;
                group->denDelayInSyn0[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn0 = 0;
                }
            }
             {
                group->inSynInSyn1[lid] = 0.000000000e+00f;
                group->denDelayInSyn1[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn1 = 0;
                }
            }
             {
                group->inSynInSyn2[lid] = 0.000000000e+00f;
                group->denDelayInSyn2[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn2 = 0;
                }
            }
             {
                group->inSynInSyn3[lid] = 0.000000000e+00f;
                group->denDelayInSyn3[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn3 = 0;
                }
            }
             {
                group->inSynInSyn4[lid] = 0.000000000e+00f;
                group->denDelayInSyn4[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn4 = 0;
                }
            }
             {
                group->inSynInSyn5[lid] = 0.000000000e+00f;
                group->denDelayInSyn5[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn5 = 0;
                }
            }
             {
                group->inSynInSyn6[lid] = 0.000000000e+00f;
                group->denDelayInSyn6[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn6 = 0;
                }
            }
             {
                group->inSynInSyn7[lid] = 0.000000000e+00f;
                group->denDelayInSyn7[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn7 = 0;
                }
            }
             {
                group->inSynInSyn8[lid] = 0.000000000e+00f;
                group->denDelayInSyn8[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn8 = 0;
                }
            }
             {
                group->inSynInSyn9[lid] = 0.000000000e+00f;
                group->denDelayInSyn9[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn9 = 0;
                }
            }
             {
                group->inSynInSyn10[lid] = 0.000000000e+00f;
                group->denDelayInSyn10[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn10 = 0;
                }
            }
             {
                group->inSynInSyn11[lid] = 0.000000000e+00f;
                group->denDelayInSyn11[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn11 = 0;
                }
            }
             {
                group->inSynInSyn12[lid] = 0.000000000e+00f;
                group->denDelayInSyn12[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn12 = 0;
                }
            }
             {
                group->inSynInSyn13[lid] = 0.000000000e+00f;
                group->denDelayInSyn13[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn13 = 0;
                }
            }
             {
                group->inSynInSyn14[lid] = 0.000000000e+00f;
                group->denDelayInSyn14[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn14 = 0;
                }
            }
             {
                group->inSynInSyn15[lid] = 0.000000000e+00f;
                group->denDelayInSyn15[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn15 = 0;
                }
            }
             {
                group->inSynInSyn16[lid] = 0.000000000e+00f;
                group->denDelayInSyn16[lid] = 0.000000000e+00f;
                if(lid == 0) {
                    *group->denDelayPtrInSyn16 = 0;
                }
            }
            // current source variables
        }
    }
    
    // ------------------------------------------------------------------------
    // Synapse groups
    
    // ------------------------------------------------------------------------
    // Custom update groups
    
    // ------------------------------------------------------------------------
    // Custom WU update groups
    
    // ------------------------------------------------------------------------
    // Synapse groups with sparse connectivity
    // merged0
    if(id >= 213888 && id < 3849984) {
        unsigned int lo = 0;
        unsigned int hi = 289;
        while(lo < hi)
         {
            const unsigned int mid = (lo + hi) / 2;
            if(id < d_mergedSynapseConnectivityInitGroupStartID0[mid]) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        struct MergedSynapseConnectivityInitGroup0 *group = &d_mergedSynapseConnectivityInitGroup0[lo - 1]; 
        const unsigned int groupStartID = d_mergedSynapseConnectivityInitGroupStartID0[lo - 1];
        const unsigned int lid = id - groupStartID;
        // only do this for existing presynaptic neurons
        if(lid < group->numSrcNeurons) {
            group->rowLength[lid] = 0;
            curandStatePhilox4_32_10_t localRNG = d_rng;
            skipahead_sequence((unsigned long long)id, &localRNG);
            // Build sparse connectivity
            scalar x = 0.00000000000000000e+00f;
            unsigned int c = group->preCalcRowLength[(lid * 1) + 0];
            while(true) {
                if(c == 0) {
                   break;
                }
                const scalar u = curand_uniform(&localRNG);
                x += (1.0f - x) * (1.0f - pow(u, 1.0f / (scalar)c));
                unsigned int postIdx = (unsigned int)(x * group->numTrgNeurons);
                postIdx = (postIdx < group->numTrgNeurons) ? postIdx : (group->numTrgNeurons - 1);
                do {
                    const unsigned int idx = (lid * group->rowStride) + group->rowLength[lid];
                    group->ind[idx] = postIdx+0;
                    group->rowLength[lid]++;
                }
                while(false);
                c--;
                
            }
        }
    }
    
}
extern "C" __global__ void initializeSparseKernel() {
    const unsigned int id = 64 * blockIdx.x + threadIdx.x;
    __shared__ unsigned int shRowLength[64];
    // merged0
    if(id < 57920) {
        unsigned int lo = 0;
        unsigned int hi = 289;
        while(lo < hi)
         {
            const unsigned int mid = (lo + hi) / 2;
            if(id < d_mergedSynapseSparseInitGroupStartID0[mid]) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        struct MergedSynapseSparseInitGroup0 *group = &d_mergedSynapseSparseInitGroup0[lo - 1]; 
        const unsigned int groupStartID = d_mergedSynapseSparseInitGroupStartID0[lo - 1];
        const unsigned int lid = id - groupStartID;
        curandStatePhilox4_32_10_t localRNG = d_rng;
        skipahead_sequence((unsigned long long)3849984 + id, &localRNG);
        const unsigned int numBlocks = (group->numSrcNeurons + 64 - 1) / 64;
        unsigned int idx = lid;
        for(unsigned int r = 0; r < numBlocks; r++) {
            const unsigned numRowsInBlock = (r == (numBlocks - 1)) ? ((group->numSrcNeurons - 1) % 64) + 1 : 64;
            __syncthreads();
            if (threadIdx.x < numRowsInBlock) {
                shRowLength[threadIdx.x] = group->rowLength[(r * 64) + threadIdx.x];
            }
            __syncthreads();
            for(unsigned int i = 0; i < numRowsInBlock; i++) {
                if(lid < shRowLength[i]) {
                     {
                        scalar initVal;
                        scalar normal;
                        do
                        {
                           normal = group->meang + (curand_normal(&localRNG) * group->sdg);
                        } while (normal > group->maxg || normal < group->ming);
                        initVal = normal;
                        
                        group->g[(((r * 64) + i) * group->rowStride) + lid] = initVal;
                    }
                     {
                        uint8_t initVal;
                        scalar normal;
                        do
                        {
                           normal = group->meanTimestepd + (curand_normal(&localRNG) * group->sdTimestepd);
                        } while (normal > group->maxTimestepd || normal < (1.00000000000000000e+00f));
                        initVal = rint(normal);
                        
                        group->d[(((r * 64) + i) * group->rowStride) + lid] = initVal;
                    }
                }
                idx += group->rowStride;
            }
        }
    }
}
void initialize() {
    unsigned long long deviceRNGSeed = 0;
     {
        std::random_device seedSource;
        uint32_t *deviceRNGSeedWord = reinterpret_cast<uint32_t*>(&deviceRNGSeed);
        for(int i = 0; i < 2; i++) {
            deviceRNGSeedWord[i] = seedSource();
        }
    }
    initializeRNGKernel<<<1, 1>>>(deviceRNGSeed);
    CHECK_CUDA_ERRORS(cudaPeekAtLastError());
     {
        const dim3 threads(64, 1);
        const dim3 grid(60156, 1);
        initializeKernel<<<grid, threads>>>(deviceRNGSeed);
        CHECK_CUDA_ERRORS(cudaPeekAtLastError());
    }
}

void initializeSparse() {
    copyStateToDevice(true);
    copyConnectivityToDevice(true);
    
     {
        const dim3 threads(64, 1);
        const dim3 grid(905, 1);
        initializeSparseKernel<<<grid, threads>>>();
        CHECK_CUDA_ERRORS(cudaPeekAtLastError());
    }
}
