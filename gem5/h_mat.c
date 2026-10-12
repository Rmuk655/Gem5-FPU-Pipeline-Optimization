#define main orig_main
#include SRC
#undef main
#include <stdlib.h>
#include <string.h>
int M1[DIM][DIM], M2[DIM][DIM], P[DIM][DIM];
int main(int argc, char **argv) {
    const char *v = argv[1]; long iters = atol(argv[2]);
    volatile int d = DIM;
    for (int i = 0; i < DIM; i++) for (int j = 0; j < DIM; j++) { M1[i][j] = (i + j) % 7 + 1; M2[i][j] = (i * j) % 5 + 1; }
    for (long it = 0; it < iters; it++) {
        if (!strcmp(v, "int")) multiply_int(d, d, d, M1, M2, P);
        else multiply_float(d, d, d, M1, M2, P);
        __asm__ volatile("" ::: "memory");
    }
    long s = 0; for (int i = 0; i < DIM; i++) for (int j = 0; j < DIM; j++) s += P[i][j];
    printf("%ld\n", s);
    return 0;
}
