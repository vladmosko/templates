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
