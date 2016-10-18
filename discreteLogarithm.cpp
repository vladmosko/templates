// baby-step-giant-step for solving (a^x) = b (mod m)
// complexity is O(sqrt(m) * logm)
template<typename T> T solve(T a, T b, T m) {
    T n = (T)sqrt(m + .0) + 1;
    T pw = 1;
    for (int i = 0; i < n; i++) {
        pw = (T)a * pw % m;
    }
    if (m <= 1000000) { // when should we create an array, and when a map? Don't forget about hash-table if speed sucks
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
    }
}
