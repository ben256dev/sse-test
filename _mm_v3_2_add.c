#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>
#include <malloc.h>

typedef float v3[3];
typedef float v3_2[2];

int main(void)
{
#define VECTOR_COUNT 8388608
#define VECTORS_BYTES VECTOR_COUNT * sizeof(v3)
    v3_2* vectors = _mm_malloc(VECTORS_BYTES, 8);
    if (!vectors)
        die("_mm_malloc()");

    if (RAND_bytes((unsigned char*)vectors, VECTORS_BYTES) != 1)
        die("RAND_bytes()");

    clock_t start = clock();
    for (int i = 0; i < (VECTOR_COUNT * 3 / 2); i++)
    {
        vectors[i][0] += vectors[i][1];
    }
    clock_t end = clock();

    printf("%ld\n", end - start);

    _mm_free(vectors);

    return 0;
}
