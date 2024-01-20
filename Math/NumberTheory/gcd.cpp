// 欧几里得求最大公约数gcd(辗转相除法)
// 默认 a > b
// O(logN)
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}


// 当整数过大时，取模时间复杂度较高可以，此时可以使用更相减损术：gcd(a, b) = gcd(a - b, b)
// 更相减损术
int _gcd(int a, int b) {
    while (a != b) if (a > b) a -= b; else b -= a;
    return a;
}


// 当 a >> b时，可以使用Stein优化：若 2 | a、2 | b，gcd(a, b) = 2gcd(a / 2, b / 2)
// 若 2 | a、b不被 2 整除, gcd(a, b) = gcd(a / 2, b)；2 | b 同理
// Stein
#include <algorithm>

int gcd_(int a, int b) {
    int a_2 = 0, b_2 = 0;  // 记录公因数 2 出现的次数
    while (a % 2 == 0) {
        a >>= 1;
        ++a_2;
    }
    while (b % 2 == 0) {
        b >>= 1;
        ++b_2;
    }
    for ( ; ;) {
        while (a % 2 == 0) a >>= 1;
        while (b % 2 == 0) b >>= 1;
        if (a == b) break;
        if (a < b) std::swap(a, b);
        a -= b;
    }
    return a << std::min(a_2, b_2);
}


// 最小公倍数lcm
// lcm(a, b) * gcd(a, b) = a * b


// if 2 | a, b | 2
// gcd(a % 4, b % 4) = gcd(a, b) % 4


// gcd(0, a) = a