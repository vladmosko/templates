
/*
 * All functions related to algebra are gathered here
 */
namespace Algebra {
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

    // baby-step-giant-step for solving (a^x) = b (mod m)
    // complexity is O(sqrt(m) * logm)
    template<typename T> T solve(T a, T b, T m) {
        T n = (T)sqrt(m + .0) + 1;
        T pw = 1;
        for (int i = 0; i < n; i++) {
            pw = (T)a * pw % m;
        }
        if (m <= 1000000) { // when should we create an array, and when a map?
            vector<T> values(m, -1);
            for (T i = 1, cur = pw; i <= n; i++) {
                if (values[cur] == -1) {
                    values[cur] = i;
                }
                cur = (T)cur * pw % m;
            }
            for (T i = 0, cur = b; i <= n; i++) {
                if (values[cur] != -1) {
                    T candidate = values[cur] * n - i;
                    if (candidate < m) {
                        return candidate;
                    }
                }
                cur = (T)cur * a % m;
            }
            return -1;
        } else {
            map<T, T> values;
            for (T i = 1, cur = pw; i <= n; i++) {
                if (!values.count(cur)) {
                    values[cur] = i;
                }
                cur = (T)cur * pw % m;
            }
            for (T i = 0, cur = b; i <= n; i++) {
                if (values.count(cur)) {
                    T candidate = values[cur] * n - i;
                    if (candidate < m) {
                        return candidate;
                    }
                }
                cur = (T)cur * a % m;
            }
            return -1;
        }
    }

    template<typename T> T phi(T n) {
        T res = n;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                while (n % i == 0) {
                    n /= i;
                }
                res -= res / i;
            }
        }
        if (n > 1) {
            res -= res / n;
        }
        return res;
    }

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

    template<typename T> T grayCode(T n) {
        return n ^ (n >> 1);
    }

    template<typename T> T reverseGrayCode(T grayCode) {
        T n = 0;
        for (; grayCode; grayCode >>= 1) {
            n ^= grayCode;
        }
        return n;
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

    vector<char> sieve(int n) {
        vector<char> prime(n + 1, true);
        prime[0] = prime[1] = false;
        for (int i = 2; i <= n; i++) {
            if (!prime[i]) {
                continue;
            }
            if (i * i > n) {
                break;
            }
            for (int j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
        return prime;
    }

    vector<int> primeList(int n) {
        vector<char> prime = sieve(n);
        vector<int> res;
        for (int i = 2; i <= n; i++) {
            if (prime[i]) {
                res.emplace_back(i);
            }
        }
        return res;
    }
};
