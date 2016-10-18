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

// solve ax + by = c
// finds any solution
// others can be represented as (u + k * (b / g); v - k * (a / g))
template<typename T> bool findAnySolution(T a, T b, T c, T& u, T& v, T& g) {
    g = extendedGcd<T>(abs(a), abs(b), u, v);
    if (c % g != 0) {
        return false;
    }
    u *= c / g;
    v *= c / g;
    if (a < 0) {
        u = -u;
    }
    if (b < 0) {
        v = -v;
    }
    return true;
}
