#include <cmath>

using Vec = struct Point {
    long double x, y;
};
const double EPS = 1e-9;
Vec operator + (Vec u, Vec v) { return { u.x + v.x, u.y + v.y }; }   // 向量加向量
Vec operator - (Vec u, Vec v) { return { u.x - v.x, u.y - v.y }; }   // 向量减向量
Vec operator * (double k, Vec v) { return { k * v.x, k * v.y }; }    // 数乘
long double operator * (Vec u, Vec v) { return u.x * v.x + u.y * v.y; } // 点乘
long double operator ^ (Vec u, Vec v) { return u.x * v.y - u.y * v.x; } // 叉乘
bool eq(long double a, long double b) { return std::abs(a - b) < EPS; } // ==
bool gt(long double a, long double b) { return a - b > EPS; }      // >
bool lt(long double a, long double b) { return a - b < -EPS; }     // <
bool ge(long double a, long double b) { return a - b > -EPS; }     // >=
bool le(long double a, long double b) { return a - b < EPS; }      // <=