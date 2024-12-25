#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>

typedef float v3[4];

int main(void)
{
#define VECTOR_COUNT 8388608
#define VECTORS_BYTES VECTOR_COUNT * sizeof(v3)
    v3* vectors = xmalloc(VECTORS_BYTES);

    if (RAND_bytes((unsigned char*)vectors, sizeof(vectors)) != 1)
        die("RAND_bytes()");

    clock_t start = clock();
    for (int i = 0; i < VECTOR_COUNT/2; i++)
    {
        vectors[i][0] += vectors[i + VECTOR_COUNT/2][0];
        vectors[i][1] += vectors[i + VECTOR_COUNT/2][1];
        vectors[i][2] += vectors[i + VECTOR_COUNT/2][2];
    }
    clock_t end = clock();

    printf("%ld\n", end - start);

    free(vectors);

    return 0;
}
