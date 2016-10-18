const long long fibonacciModulo = 1000 * 1000 * 1000 + 7;
void findFibonacciNumber(long long n, long long& x, long long& y) {
    if (n == 0) {
        x = 0;
        y = 1;
        return;
    }
    if (n & 1) {
        findFibonacciNumber(n - 1, y, x);
        y = (y + x) % fibonacciModulo;
    } else {
        long long a, b;
        findFibonacciNumber(n >> 1, a, b);
        y = (a * a + b * b) % fibonacciModulo;
        x = (a * b + a * (b - a + fibonacciModulo)) % fibonacciModulo;
    }
}
