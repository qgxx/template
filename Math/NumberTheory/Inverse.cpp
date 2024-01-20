// 逆元：如果一个线性同余方程 ax === 1 (mod b)，则 x 称为 a mod b 的逆元

// (a / b) mod p = (a * inv(b)) mod p


using ll = long long;

// 扩展欧几里得
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

ll inv1(ll a, ll b) {
    ll x, y;
    if (exgcd(a, b, x, y) != 1) {
        return -1;  // 无解
    }
    return (x % b + b) % b;
}


// 费马小定理 + 快速幂
// 费马小定理: 若 p 是质数，且 gcd(a, p) = 1，则 a ^ (p - 1) === 1 (mod p)
// 因为 ax === 1 (mod p), 由小费马定理得: ax === a ^ (p - 1) (mod p)
// 所以 x === a ^ (p - 2) (mod p)

// 推论: ay === x (mod p) -> a / x === y ^ (p - 2) (mod p) - > a = x * y ^ (p - 2) (mod p)
ll qpow(ll a, ll n, ll p){
    ll ans = 1;   // 初始化为乘法单位元
    while (n) {
        if (n & 1) ans = ans % p * a % p;
        n >>= 1;
        a = a % p * a % p;
    }
    return ans;
}

ll inv2(ll a, ll p) {  // p 必须是质数
    return qpow(a, p - 2, p);
}


// 线性递推
// p 必须是质数
const int maxn = 1e6 + 10;

ll Inv[maxn] {1, 1};

ll inv3(ll a, ll p) {
    if (Inv[a]) return Inv[a];
    Inv[a] = ((-p / a * inv3(p % a, p)) % p + p) % p;
    return Inv[a];
}

// 线性求 1 ~ n 的逆元
ll inv4(ll p) {
    Inv[1] = 1;
    for (int i = 2; i < maxn; ++i) Inv[i] = (p - p / i) * Inv[p % i] % p;
}

// 线性求任意 n 个数的逆元
// O(n + logp)
int a[maxn], s[maxn], inv_s[maxn], inv_a[maxn];
// s[]: 前i个a的乘积
// inv_s[]: s[]的逆元
// 因此在搞阶乘时，可以直接用inv_s[i]作为Fac(i)的逆元
ll inv5(int n, int p) {
    s[0] = 1; for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % p;
    inv_s[n] = inv2(s[n], p); for (int i = n - 1; i >= 1; --i) inv_s[i] = inv_s[i + 1] * a[i + 1] % p; 
    // inv_a[i + 1] 被 a[i + 1] 抵消
    for (int i = 1; i <= n; ++i) inv_a[i] = inv_s[i] * s[i - 1] % p; 
    // inv_s[i - 1] 被 s[i - 1] 抵消
}
// inv(a) * a === 1 (mod p), inv(b) * b === 1 (mod p), b / a = k, k | b, b > a
// inv(a) = inv(b) * k % p