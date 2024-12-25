#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include <immintrin.h>

typedef float v3[3];
#define V3_SUB 32
typedef float v3_32[V3_SUB];

int main(void)
{
#define VECTOR_COUNT 8388608
#define VECTORS_BYTES VECTOR_COUNT * sizeof(v3)
    v3_32* vectors = _mm_malloc(VECTORS_BYTES, sizeof(float) * V3_SUB);
    if (!vectors)
        die("_mm_malloc()");

    if (RAND_bytes((unsigned char*)vectors, VECTORS_BYTES) != 1)
        die("RAND_bytes()");

    clock_t start = clock();
    for (int i = 0; i < (VECTOR_COUNT * 3 / V3_SUB); i++)
    {
        __m256 v_1 = _mm256_load_ps(&vectors[i][0]);
        __m256 v_2 = _mm256_load_ps(&vectors[i][8]);
        __m256 v_3 = _mm256_load_ps(&vectors[i][16]);
        __m256 v_4 = _mm256_load_ps(&vectors[i][24]);

        __m256 v_res_1 = _mm256_add_ps(v_1, v_3);
        __m256 v_res_2 = _mm256_add_ps(v_2, v_4);

        _mm256_store_ps(&vectors[i][0], v_res_1);
        _mm256_store_ps(&vectors[i][8], v_res_2);
    }
    clock_t end = clock();

    printf("%ld\n", end - start);

    _mm_free(vectors);

    return 0;
}
