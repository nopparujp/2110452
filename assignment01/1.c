#include <stdio.h>
#include <immintrin.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void add_avx(int size, int *a, int *b)
{
    int i = 0;
    for (; i < size; i += 8)
    {
        __m256i av = _mm256_loadu_si256((__m256i *)&a[i]);
        __m256i bv = _mm256_loadu_si256((__m256i *)&b[i]);
        av = _mm256_add_epi32(av, bv);
        _mm256_storeu_si256((__m256i *)&a[i], av);
    }
    for (; i < size; i++)
    {
        a[i] += b[i];
    }
}

void add(int size, int *a, int *b)
{
    for (int i = 0; i < size; i++)
    {
        a[i] += b[i];
    }
}

double calculate_geometric_mean(double *values, int size)
{
    double product = 1.0;
    for (int i = 0; i < size; i++)
    {
        product *= values[i];
    }
    return pow(product, 1.0 / size);
}

int compare_doubles(const void *a, const void *b)
{
    return (*(double *)a > *(double *)b) - (*(double *)a < *(double *)b);
}

double remove_outliers(double *values, int size)
{
    qsort(values, size, sizeof(double), compare_doubles);
    double *trimmed_values = values + 1;
    trimmed_values[size - 2] = '\0';
    return calculate_geometric_mean(trimmed_values, size - 2);
}

int main()
{
    clock_t tik, tok;
    int N = 1000000;
    int a[N];
    int b[N];
    int rep = 5;

    double times_normal[rep];
    double times_avx[rep];

    for (int k = 0; k < rep; k++)
    {
        for (int i = 0; i < N; i++)
        {
            a[i] = i;
            b[i] = i;
        }
        tik = clock();
        add(N, a, b);
        tok = clock();
        times_normal[k] = (double)(tok - tik) / CLOCKS_PER_SEC;

        for (int i = 0; i < N; i++)
        {
            a[i] = i;
            b[i] = i;
        }
        tik = clock();
        add_avx(N, a, b);
        tok = clock();
        times_avx[k] = (double)(tok - tik) / CLOCKS_PER_SEC;
    }

    double geometric_mean_normal = remove_outliers(times_normal, rep);
    double geometric_mean_avx = remove_outliers(times_avx, rep);

    printf("Geometric Mean without Outlier (Normal): %f seconds\n", geometric_mean_normal);
    printf("Geometric Mean without Outlier (AVX): %f seconds\n", geometric_mean_avx);
    printf("Speed Up: %f times\n", geometric_mean_normal / geometric_mean_avx);

    return 0;
}
