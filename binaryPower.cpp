// NOT TESTED YET

template<typename T, typename Q> T binaryPower(T a, Q n) {
    assert(n >= 0);
    T res = 1;
    while (n) {
        if (n & 1) {
            res = (res * a);
        }
        a = (a * a);
        n >>= 1;
    }
    return res;
}

template<typename T, typename Q> T binaryPower(T a, Q n, T mod) {
    assert(n >= 0 && mod > 0);
    a %= mod;
    T res = 1;
    while (n) {
        if (n & 1) {
            res = (long long)res * a % mod;
        }
        a = (long long)a * a % mod;
        n >>= 1;
    }
    return res;
}
