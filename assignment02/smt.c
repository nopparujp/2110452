#include <stdio.h>
#include <time.h>
#include <math.h>
int loop(int *a)
{
#pragma omp parallel for
    for (int i = 0; i < 100000; i++)
    {
        a[i] = 2 * i + i;
    }
}
int main(void)
{
    int r = 1000;
    int a[100000];
    clock_t tik, tok;
    double t, total_t, mean;
    total_t = 1.0;

    for (int k = 0; k < 5; ++k)
    {
        tik = clock();
        for (int i = 0; i < r; ++i)
        {
            loop(a);
        }
        tok = clock();
        t = (double)(tok - tik) / CLOCKS_PER_SEC;
        total_t *= t;
    }
    mean = pow(total_t, 1.0 / 5);
    printf("geometric mean time/iteration:: %lf", mean);
    return 0;
}