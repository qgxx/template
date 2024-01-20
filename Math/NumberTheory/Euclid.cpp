// 扩展欧几里得求解 ax + by = c
// 也可以用来求解线性同余方程 ax === c (mod b) : ax + by = c
// 有解当且仅当：gcd(a, b) | c
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int gcd = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}


#include <numeric>
// 求 x 的最小整数解
int get_minx() {
    int a, b, c, d; 
    d = std::gcd(a, b);
    if (c % d) return -1e9; // 无解
    int x, y;
    exgcd(a, b, x, y);
    int mod = b / d;
    x = x * c / d;
    if (mod < 0) mod = -mod;
    x = (x % mod + mod) % mod; // 最小整数解
}