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
