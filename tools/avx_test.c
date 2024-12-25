
#include <stdio.h>
#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <cpuid.h>
#endif

int has_avx_support() {
    int cpu_info[4] = {0};

    // Query CPUID function 1
    #if defined(_MSC_VER)
    __cpuid(cpu_info, 1);
    #else
    __cpuid(1, cpu_info[0], cpu_info[1], cpu_info[2], cpu_info[3]);
    #endif

    // Check OSXSAVE (bit 27) and AVX (bit 28) in ECX
    if ((cpu_info[2] & (1 << 27)) && (cpu_info[2] & (1 << 28))) {
        // Verify OS supports AVX with XGETBV
        unsigned long long xcr_feature_mask = 0;
        #if defined(_MSC_VER)
        xcr_feature_mask = _xgetbv(0); // MSVC intrinsic
        #else
        __asm__ volatile(".byte 0x0f, 0x01, 0xd0" : "=A"(xcr_feature_mask) : "c"(0));
        #endif

        // Check if XMM (bit 1) and YMM (bit 2) states are enabled
        return (xcr_feature_mask & 0x6) == 0x6;
    }

    return 0;
}

int main() {
    if (has_avx_support()) {
        printf("AVX is supported!\n");
    } else {
        printf("AVX is NOT supported.\n");
    }
    return 0;
}
