// Andrew求二维凸包
// O(NlogN)

#include <algorithm>
#include <cmath>
#include <vector>

const int maxn = 1e5 + 10;

struct Point {
    long double x, y;
};
using Vec = Point;
Vec operator+ (Vec u, Vec v) { return { u.x + v.x, u.y + v.y }; }   // 向量加向量
Vec operator- (Vec u, Vec v) { return { u.x - v.x, u.y - v.y }; }   // 向量减向量
Vec operator* (double k, Vec v) { return { k * v.x, k * v.y }; }    // 数乘
long double operator* (Vec u, Vec v) { return u.x * v.x + u.y * v.y; } // 点乘
long double operator^ (Vec u, Vec v) { return u.x * v.y - u.y * v.x; } // 叉乘

int stk[maxn], tp = 0, used[maxn];

void Andrew() {
    int n;
    std::vector<Vec> p(n + 1);  // 点坐标
    std::sort(p.begin() + 1, p.end(), [](Vec a, Vec b){
        return (a.x == b.x ? a.y < b.y : a.x < b.x);
    }); 
    
    // 上凸壳
    stk[++tp] = 1;
    for (int i = 2; i <= n; ++i) {
        while (tp >= 2 && ((p[stk[tp]] - p[stk[tp - 1]]) ^ (p[i] - p[stk[tp]])) <= 0) used[stk[tp--]] = 0;
        stk[++tp] = i;
        used[i] = 1;
    }

    // 下凸壳
    int tmp = tp;
    for (int i = n - 1; i > 0; --i) {
        if (!used[i]) {
            while (tp > tmp && ((p[stk[tp]] - p[stk[tp - 1]]) ^ (p[i] - p[stk[tp]])) <= 0) used[stk[tp--]] = 0;
            stk[++tp] = i;
            used[i] = 1;
        }
    }

    std::vector<Vec> h(tp + 1);  
    for (int i = 1; i <= tp; ++i) h[i] = p[stk[i]];  // 保存凸包点顺序
    int num = tp - 1;  // 凸包元素数量 h[tp]和h[1]是同一个
    long double len = 0.0;
    auto d = [](Vec a, Vec b)->long double {
        return sqrtl(powl(a.x - b.x, 2) + powl(a.y - b.y, 2));
    };
    for (int i = 1; i <= num; ++i) len += d(h[i], h[i + 1]);
    len += d(h[num + 1], h[1]);
}


// 平面上随机N个点，这N个点的凸包上的点的个数的期望为logN