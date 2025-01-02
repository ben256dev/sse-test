#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include <windows.h>

typedef float v3[3];

u64 spec_summation_time(const char* spec_file)
{
    v3* vectors = xmfopen(spec_file);

    const char* count_str = spec_file;
    for (int i = 0; i < 128 && spec_file[i] != '\0'; i++)
        if (spec_file[i] == '.')
            count_str = &spec_file[i + 1];

    int vector_count = strtol(count_str, 0, 10);

    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < vector_count/2; i++)
    {
        vectors[i][0] += vectors[i + vector_count/2][0];
        vectors[i][1] += vectors[i + vector_count/2][1];
        vectors[i][2] += vectors[i + vector_count/2][2];
    }

    QueryPerformanceCounter(&end);
    u64 elapsed = (u64)((end.QuadPart - start.QuadPart) * 1000000.0 / frequency.QuadPart);

    printf("%llu\n", elapsed);

    free(vectors);
}

int main(int argc, char* argv[])
{
    argc--;
    argv++;

    if (argc < 0)
        lie("no filenames specified");

    for (int i = 0; i < argc; i++)
        puts("%llu", spec_summation_time(argv));

    return 0;
}
