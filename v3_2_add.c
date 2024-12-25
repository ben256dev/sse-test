#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>

typedef float v3[3];
typedef float v3_2[2];

int main(void)
{
#define VECTOR_COUNT 8388608
#define VECTORS_BYTES VECTOR_COUNT * sizeof(v3)
    v3_2* vectors = xmalloc(VECTORS_BYTES);

    if (RAND_bytes((unsigned char*)vectors, VECTORS_BYTES) != 1)
        die("RAND_bytes()");

    clock_t start = clock();
    for (int i = 0; i < (VECTOR_COUNT * 3 / 2); i++)
    {
        vectors[i][0] += vectors[i][1];
    }
    clock_t end = clock();

    printf("%ld\n", end - start);

    free(vectors);

    return 0;
}
