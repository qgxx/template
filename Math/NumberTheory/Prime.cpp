/**
 * @brief 埃氏筛
 * O(N loglogN)
 */


const int maxn = 1e5 + 10;

int vis[maxn], prime[maxn], cnt;

void Eratosthenes(int n) {
    for (int i = 2; i <= n; i++) {
        if (vis[i]) continue;
        prime[++cnt] = i;
        for (int j = i; j <= n / i; j++) vis[i * j] = 1;
    }
}


/**
 * @brief 欧拉筛
 * O(N)
 */
int vis[maxn], prime[maxn], cnt;

void Euler(int n) {
    for (int i = 2; i <= n; i++) {
        if (vis[i] == 0) {
            vis[i] = i;
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt; j++) {
            if (prime[j] > vis[i] || prime[j] > n / i) break;
            vis[prime[j] * i] = prime[j];
        } 
    }
}


/**
 * @brief MillerRabin素性测试
 * O(k (logn) ^ 2 loglogn logloglogn)
 */
#include <algorithm>

using ll = long long;

ll qpow(ll a, ll n, ll p) {
    ll ans = 1;  
    while (n) {
        if (n & 1) ans = ans * a % p;
        n >>= 1;
        a = a * a % p;
    }
    return ans;
}


// 素性检验
// p是素数返回true
bool MillerRabin(ll p) {
    if (p < 2) return 0;
    if (p == 2) return 1;
    if (p == 3) return 1;
    ll d = p - 1, r = 0;
    while (!(d & 1)) ++r, d >>= 1;
    for (ll k = 0; k < 10; ++k) {
        ll a = std::rand() % (p - 2) + 2;
        ll x = qpow(a, d, p);
        if (x == 1 || x == p - 1) continue;
        for (int i = 0; i < r - 1; ++i) {
            x = x * x % p;
            if (x == p - 1) break;
        }
        if (x != p - 1) return 0;
    }
    return 1;
}


// 所有大于3的素数都可以表示成 6n +- 1 的形式