#define main orig_main
#include SRC
#undef main
#include <stdlib.h>
#include <string.h>
int A[DIM], B[DIM], C[2*DIM];
volatile int sink;
int main(int argc, char **argv) {
    const char *v = argv[1]; long iters = atol(argv[2]);
    volatile int m = DIM_M, n = DIM_N;
    for (int i = 0; i < DIM; i++) { A[i] = i % 7 + 1; B[i] = i % 5 + 1; }
    for (long it = 0; it < iters; it++) {
        if (!strcmp(v, "int")) convolution_int(m, n, A, B, C);
        else if (!strcmp(v, "float")) convolution_float(m, n, A, B, C);
        else convolution_double(m, n, A, B, C);
        sink = C[1];
    }
    long s = 0; for (int i = 0; i < m + n - 1; i++) s += C[i];
    printf("%ld\n", s);
    return 0;
}
