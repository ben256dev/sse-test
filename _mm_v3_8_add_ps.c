#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include <emmintrin.h>

typedef float v3[3];
#define V3_SUB 8
typedef float v3_8[V3_SUB];

int main(void)
{
#define VECTOR_COUNT 8388608
#define VECTORS_BYTES VECTOR_COUNT * sizeof(v3)
    v3_8* vectors = _mm_malloc(VECTORS_BYTES, sizeof(float) * V3_SUB);
    if (!vectors)
        die("_mm_malloc()");

    if (RAND_bytes((unsigned char*)vectors, sizeof(vectors)) != 1)
        die("RAND_bytes()");

    clock_t start = clock();
    for (int i = 0; i < (VECTOR_COUNT * 3 / V3_SUB); i++)
    {
        __m128 v_1 = _mm_load_ps(&vectors[i][0]);
        __m128 v_2 = _mm_load_ps(&vectors[i][4]);

        __m128 v_res = _mm_add_ps(v_1, v_2);

        _mm_store_ps(&vectors[i][0], v_res);
    }
    clock_t end = clock();

    printf("%ld\n", end - start);

    _mm_free(vectors);

    return 0;
}
