// 求正整数一个非平凡因子（并不特指素因子，非1，非自身）

#include <algorithm>
#include <stdint.h>
#include <numeric>
#include <ctime>

using ll = long long;

ll PollardRho(ll x) {
    using namespace std;
    ll s = 0, t = 0;
    ll c = (ll)rand() % (x - 1) + 1;
    int step = 0, goal = 1;
    ll val = 1;
    for (goal = 1; ; goal <<= 1, s = t, val = 1) {
        for (step = 1; step <= goal; ++step) {
            t = ((__int128_t)t * t + c) % x;
            val = (__int128_t)val * abs(t - s) % x;
            if (step % 127 == 0) {
                ll d = gcd(val, x); 
                if (d > 1) return d;
            }
        }
        ll d = gcd(val, x);
        if (d > 1) return d;
    }
}

ll max_factor ;

void factor(ll x) {
    if (x <= max_factor || x < 2) return ;
    ll p = x;
    while (p >= x) p = PollardRho(x);
    while ((x % p) == 0) x /= p;
    factor(x); factor(p);
}

void wk() {
    ll x;
    max_factor = 0;
    srand((unsigned)time(NULL));
    factor(x);
}
// 在分解一个数之前记得：srand((unsigned)time(NULL));
// 可以用这个种子对这个数一直分解