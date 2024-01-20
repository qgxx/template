// 类欧几里得算法
// 类欧公式 f(a, b, c, n) = Sum{floor((a * i + b) / c), 0<=i<n}
// a, b, c, n是常数，时间复杂度O(log(a+b+c+n))


#include <algorithm>
using namespace std;
using ll = long long;
using i128 = __int128_t;
i128 floor_sum(i128 n, i128 c, i128 a, i128 b) {
    i128 ans = 0;
    if (a < 0) {
        i128 a2 = (a % c + c) % c;
        ans -= n * (n - 1) / 2 * ((a2 - a) / c);
        a = a2;
    }
    if (b < 0) {
        i128 b2 = (b % c + c) % c;
        ans -= n * ((b2 - b) / c);
        b = b2;
    }
    while (1) {
        if (a >= c) {
            ans += n * (n - 1) / 2 * (a / c);
            a %= c;
        }
        if (b >= c) {
            ans += n * (b / c);
            b %= c;
        }
        i128 y_max = a * n + b;
        if (y_max < c) {
            break;
        }
        n = y_max / c;
        b = y_max % c;
        swap(c, a);
    }
    return ans;
}



// f(a, b, c, n) = Sum{floor((a * i + b) / c), 0<=i<=n}
// g(a, b, c, n) = Sum{i * floor((ai + b) / c), 0<=i<=n}
// h(a, b, c, n) = Sum{(floor((ai + b) / c))^2, 0<=i<=n}
const ll P = 998244353;
ll i2 = 499122177, i6 = 166374059;

struct data {
  data() { f = g = h = 0; }

  ll f, g, h;
};  // 三个函数打包

data calc(ll n, ll a, ll b, ll c) {
    ll ac = a / c, bc = b / c, m = (a * n + b) / c, n1 = n + 1, n21 = n * 2 + 1;
    data d;
    if (a == 0) {  // 迭代到最底层
        d.f = bc * n1 % P;
        d.g = bc * n % P * n1 % P * i2 % P;
        d.h = bc * bc % P * n1 % P;
        return d;
    }
    if (a >= c || b >= c) {  // 取模
        d.f = n * n1 % P * i2 % P * ac % P + bc * n1 % P;
        d.g = ac * n % P * n1 % P * n21 % P * i6 % P + bc * n % P * n1 % P * i2 % P;
        d.h = ac * ac % P * n % P * n1 % P * n21 % P * i6 % P +
                bc * bc % P * n1 % P + ac * bc % P * n % P * n1 % P;
        d.f %= P, d.g %= P, d.h %= P;

        data e = calc(n, a % c, b % c, c);  // 迭代

        d.h += e.h + 2 * bc % P * e.f % P + 2 * ac % P * e.g % P;
        d.g += e.g, d.f += e.f;
        d.f %= P, d.g %= P, d.h %= P;
        return d;
    }
    data e = calc(m - 1, c, c - b - 1, a);
    d.f = n * m % P - e.f, d.f = (d.f % P + P) % P;
    d.g = m * n % P * n1 % P - e.h - e.f, d.g = (d.g * i2 % P + P) % P;
    d.h = n * m % P * (m + 1) % P - 2 * e.g - 2 * e.f - d.f;
    d.h = (d.h % P + P) % P;
    return d;
}