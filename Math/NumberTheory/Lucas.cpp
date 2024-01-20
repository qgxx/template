// 卢卡斯定理
// 求解大组合数取模问题
// C(n, m) mod p = C(n / p{向下取整}, m / p{向下取整}) * C(n mod p, m mod p) mod p {n为底}

const int maxn = 1e6 + 10;

using ll = long long;

ll Fac[maxn];   // 阶乘，可以提前预处理，因为不会快速阶乘

ll inv(ll a, ll p) {};

ll C(ll n, ll m, ll p) {
    return n < m ? 0 : Fac[n] * inv(Fac[m], p) % p * inv(Fac[n - m], p) % p;
}

// p 是质数
ll lucas(ll n, ll m, ll p) {
    return m == 0 ? 1 % p : lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}


// 扩展卢卡斯定理
// p 不是质数
#include <cmath>

ll p;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll gcd = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}

ll inv(ll a, ll b) {
    ll x, y;
    if (exgcd(a, b, x, y) != 1) {
        return -1;  
    }
    return (x % b + b) % b;
}

ll CRT(ll a, ll b) {
    return a * inv(p / b, b) % p * (p / b) % p;
}

ll qpow(ll a, ll n, ll p) {
    ll ans = 1;   
    while (n) {
        if (n & 1) ans = ans * a % p;
        n >>= 1;
        a = a * a % p;
    }
    return ans;
}

ll fac(ll n, ll pi, ll pk) {
    if (!n) return 1;
    ll res = 1;
    for (ll i = 2; i <= pk; ++i) if (i % pi) (res *= i) %= pk;
    res = qpow(res, n / pk, pk);
    for (ll i = 2; i <= n % pk; ++i) if (i % pi) (res *= i) %= pk;
    return res * fac(n / pi, pi, pk) % pk;
}

ll C(ll n, ll m, ll pi, ll pk) {
    ll up = fac(n, pi, pk), d1 = fac(m, pi, pk), d2 = fac(n - m, pi, pk);
    ll k = 0;
    for (ll i = n; i; i /= pi) k += i / pi;
    for (ll i = m; i; i /= pi) k -= i / pi;
    for (ll i = n - m; i; i /= pi) k -= i / pi;
    return up * inv(d1, pk) % pk * inv(d2, pk) % pk * qpow(pi, k, pk) % pk;
}

ll exlucas(ll n, ll m) {
    ll ans = 0, tmp = p, pk;
    int lim = std::sqrt(p) + 5;
    for (int i = 2; i <= lim; ++i) 
        if (tmp % i == 0) {
            pk = 1;
            while (tmp % i == 0) pk *= i, tmp /= i;
            (ans += CRT(C(n, m, i, pk), pk)) %= p;
        }
    if (tmp > 1) (ans += CRT(C(n, m, tmp, tmp), tmp)) %= p;
    return ans;
}