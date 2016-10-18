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
