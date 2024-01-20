// 中国剩余定理
// 求解一元线性同余方程组
// x === a1 (mod b1)
// x === a2 (mod b2)
// ...
// x === ak (mod b3)


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

// a[] : 余数数组 ； b[] : 取模数组
// b[] 两两互质
ll crt(ll a[], ll b[], ll n) {
    ll M = 1, ans = 0;
    for (int i = 1; i <= n; ++i) M = M * b[i];
    for (int i = 1; i <= n; ++i) {
        ll m = M / b[i];
        ans += (m * inv1(m, b[i]) * a[i]) % M; 
    } 
    return (ans % M + M) % M;
}


// excrt 扩展中国剩余定理
// b[] 存在两两不互质

ll mul(ll a, ll n, ll p) {
    ll ans = 0;   
    while (n) {
        if (n & 1) ans = (ans + a) % p;
        n >>= 1;
        a = (a + a) % p;
    }
    return ans;
}

ll excrt(ll a[], ll b[], ll n) {
    ll x, y;
    ll M = b[1], ans = a[1];
    for (int i = 2; i <= n; ++i) {
        ll aa = M, bb = b[i], cc = (a[i] - ans % bb + bb) % bb;
        ll gcd = exgcd(aa, bb, x, y);
        if (cc % gcd != 0) return -1;

        ll lcm = bb / gcd;
        x = mul(x, cc / gcd, lcm);
        ans += x * M;
        M = M * lcm;
        ans = (ans % M + M) % M; 
    }
    return (ans % M + M) % M;
}