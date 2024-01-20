// 快速幂
// 数据类型支持乘法且满足结合律


template <typename T>
auto qpow(T a, int n)->T {
    T ans = 1;   // 初始化为乘法单位元
    while (n) {
        if (n & 1) ans = ans * a;
        n >>= 1;
        a = a * a;
    }
    return ans;
}

#include <stdint.h>

using ll = long long;

ll qpow(ll a, ll n, ll p) {
    ll ans = 1;   
    while (n) {
        if (n & 1) ans = (__int128_t)ans * a % p;
        n >>= 1;
        a = (__int128_t)a * a % p;
    }
    return ans;
}