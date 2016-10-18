template<typename T> T extendedGcd(T a, T b, T& x, T& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    T u, v;
    T d = extendedGcd(b % a, a, u, v);
    x = v - (b / a) * u;
    y = u;
    return d;
}

template<typename T> T moduloInverse(T a, T m) {
    T x, y;
    T g = extendedGcd<T>(a, m, x, y);
    if (g != 1) {
        assert(false); 
    } else {
        x = (x % m + m) % m;
        return x;
    }
}

// m is prime
vector<long long> allModuloInverses(long long m) {
    vector<long long> results(m, 0);
    results[1] = 1;
    for (int i = 2; i < m; i++) {
        results[i] = (m - (m / i) * results[m % i] % m) % m;
    }
    return results;
}
