#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>
#include <malloc.h>

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

    if (RAND_bytes((unsigned char*)vectors, sizeof(vectors)) != 1)
        die("RAND_bytes()");

    clock_t start = clock();
    for (int i = 0; i < (VECTOR_COUNT * 3 / V3_SUB); i++)
    {
        vectors[i][0]  += vectors[i][16];
        vectors[i][1]  += vectors[i][17];
        vectors[i][2]  += vectors[i][18];
        vectors[i][3]  += vectors[i][19];
        vectors[i][4]  += vectors[i][20];
        vectors[i][5]  += vectors[i][21];
        vectors[i][6]  += vectors[i][22];
        vectors[i][7]  += vectors[i][23];
        vectors[i][8]  += vectors[i][24];
        vectors[i][9]  += vectors[i][25];
        vectors[i][10] += vectors[i][26];
        vectors[i][11] += vectors[i][27];
        vectors[i][12] += vectors[i][28];
        vectors[i][13] += vectors[i][29];
        vectors[i][14] += vectors[i][30];
        vectors[i][15] += vectors[i][31];
    }
    clock_t end = clock();

    printf("%ld\n", end - start);

    _mm_free(vectors);

    return 0;
}
