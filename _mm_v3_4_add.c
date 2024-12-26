#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>
#include <malloc.h>

#include <windows.h>

typedef float v3[3];
typedef float v3_4[4];

int main(void)
{
#define VECTOR_COUNT 8388608
#define VECTORS_BYTES VECTOR_COUNT * sizeof(v3)
    v3_4* vectors = _mm_malloc(VECTORS_BYTES, 16);
    if (!vectors)
        die("_mm_malloc()");

    if (RAND_bytes((unsigned char*)vectors, VECTORS_BYTES) != 1)
        die("RAND_bytes()");

    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < (VECTOR_COUNT * 3 / 4); i++)
    {
        vectors[i][0] += vectors[i][2];
        vectors[i][1] += vectors[i][3];
    }

    QueryPerformanceCounter(&end);
    unsigned long long elapsed = (unsigned long long)((end.QuadPart - start.QuadPart) * 1000000.0 / frequency.QuadPart);

    printf("%llu\n", elapsed);

    _mm_free(vectors);

    return 0;
}
