// 欧拉函数 phi(x): <= x 且与 x 互质的正整数的数量

// 若 p 是质数：phi(p ^ n) == p ^ (n - 1) * (p - 1)
// 积性函数：若 gcd(a, b) == 1，则 phi(a * b) = phi(a) * phi(b); 当 n 为奇数时：phi(2n) = 2phi(n)
// 设 n = Mul(pi ^ ki) [1 <= i <= s] {pi是质数}，则 phi(n) = n * Mul((pi - 1) / pi) [1 <= i <= s]

// O(sqrt(N))
int euler_phi(int n) {
    int ans = n;
    for (int i = 2; i <= n; ++i) {
        if (n % i == 0) ans = ans / i * (i - 1);
        while (n % i == 0) n /= i;
    }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}


// 筛法求欧拉函数
// O(N)
#include <vector>

const int maxn = 1e6 + 10;

int phi[maxn], isnp[maxn];
std::vector<int> primes;

void euler(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!isnp[i]) primes.push_back(i), phi[i] = i - 1;
        for (int p : primes) {
            if (p * i > n) break;
            isnp[p * i] = 1;
            if (i % p == 0) {
                phi[p * i] = phi[i] * p;
                break;
            } 
            else phi[p * i] = phi[p] * phi[i];
        }
    }
}

// 欧拉定理：若 gcd(a, m) == 1，则 a ^ phi(m) === 1 (mod m)
// 扩展欧拉定理 
// 求解 a ^ p (mod m)
#include <iostream>

using ll = long long;

ll qpow(ll a, ll n, ll p) {
    ll ans = 1;   // 初始化为乘法单位元
    while (n) {
        if (n & 1) ans = ans * a % p;
        n >>= 1;
        a = a * a % p;
    }
    return ans;
}

ll exphi(ll a, ll m, std::string s) {
    ll phi = euler_phi(m), b = 0;
    bool op = false;
    s.reserve();
    for (char c : s) {
        b = b * 10 + (c - '0');
        if (b >= phi) {
            b %= phi;
            op = true;
        }
    }
    ll ans = qpow(a, b + (op ? phi : 0ll), m);
    return ans;
}