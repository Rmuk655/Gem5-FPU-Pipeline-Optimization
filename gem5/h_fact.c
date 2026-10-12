#define main orig_main
#include SRC
#undef main
#include <stdlib.h>
#include <string.h>
volatile unsigned long long sink;
int main(int argc, char **argv) {
    const char *v = argv[1]; long iters = atol(argv[2]);
    volatile int n = 20;
    for (long i = 0; i < iters; i++) {
        if (!strcmp(v, "int")) sink = fact_int(n);
        else if (!strcmp(v, "float")) sink = fact_float(n);
        else sink = fact_double(n);
    }
    printf("%llu\n", sink);
    return 0;
}
