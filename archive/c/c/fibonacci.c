#include <stdio.h>
#include <errno.h>
#include <inttypes.h>

/*
 * This limit is chosen because fib(93) is the first number that is
 * still small enough to fit into a 64 bit integer.
 */
#define LIMIT 93

void fibonacci(int n)
{
    unsigned long long first = 0;
    unsigned long long second = 1;
    unsigned long long result = 0;

    for (int i = 1; i <= n; i++) {
        result = first + second;
        first = second;
        second = result;
        printf("%d: %llu\n", i, first);
    }
}

int main(int argc, char **argv)
{
    uintmax_t n;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [n]\n", argv[0]);
        return 1;
    }

    errno = 0;
    n = strtoumax(argv[1], NULL, 10);
    if (n == UINTMAX_MAX && errno == ERANGE) {
        fprintf(stderr, "Invalid argument for n\n");
        return 1;
    }

    if (n > LIMIT) {
        fprintf(stderr, "n cannot be larger than %d\n", LIMIT);
        return 1;
    }

    fibonacci(n);
    return 0;
}
