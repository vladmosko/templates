template<typename T> T factorialByModulo(T n, T mod) {
    T res = 1;
    while (n > 1) {
        res = (res * ((n / mod) % 2 ? mod - 1 : 1)) % mod;
        for (T i = 2; i <= n % mod; i++) {
            res = (res * i) % mod;
        }
        n /= mod;
    }
    return res % mod;
}
