// 卡特兰数
// 当有两个选择，a、b，每个选择都可以选择n次
// 但必须满足对于每次选择，包括这次选择之前的a、b的数量满足：count(a) - count(b) >= 0
// 卡特兰数H[n] = C(2n, n) - C(2n, n - 1)  {C(n, m) : 组合数[n 选 m]}
// H[n] = C(2n, n) / (n + 1),  n >= 2
// H[n] = Sum(H[i - 1] * H[n - i]){i : 1 ~ n},  n >= 2 ; H[n] = 1, n = 0, 1
// H[n] = (H[n - 1] * (4n - 2)) / (n + 1)

using ll = long long;
using ull = unsigned long long;

const int maxn = 1e6 + 10, mod = 998244353;

template<const int T>
struct ModInt {
    const static int mod = T;
    int x;
    ModInt(int x = 0) : x(x % mod) {}
    ModInt(long long x) : x(int(x % mod)) {} 
    int val() { return x; }
    ModInt operator + (const ModInt &a) const { int x0 = x + a.x; return ModInt(x0 < mod ? x0 : x0 - mod); }
    ModInt operator - (const ModInt &a) const { int x0 = x - a.x; return ModInt(x0 < 0 ? x0 + mod : x0); }
    ModInt operator * (const ModInt &a) const { return ModInt(1LL * x * a.x % mod); }
    ModInt operator / (const ModInt &a) const { return *this * a.inv(); }
    bool operator == (const ModInt &a) const { return x == a.x; };
    bool operator != (const ModInt &a) const { return x != a.x; };
    void operator += (const ModInt &a) { x += a.x; if (x >= mod) x -= mod; }
    void operator -= (const ModInt &a) { x -= a.x; if (x < 0) x += mod; }
    void operator *= (const ModInt &a) { x = 1LL * x * a.x % mod; }
    void operator /= (const ModInt &a) { *this = *this / a; }
    friend ModInt operator + (int y, const ModInt &a){ int x0 = y + a.x; return ModInt(x0 < mod ? x0 : x0 - mod); }
    friend ModInt operator - (int y, const ModInt &a){ int x0 = y - a.x; return ModInt(x0 < 0 ? x0 + mod : x0); }
    friend ModInt operator * (int y, const ModInt &a){ return ModInt(1LL * y * a.x % mod);}
    friend ModInt operator / (int y, const ModInt &a){ return ModInt(y) / a;}
    friend ostream &operator<<(ostream &os, const ModInt &a) { return os << a.x;}
    friend istream &operator>>(istream &is, ModInt &t){return is >> t.x;}

    ModInt pow(int64_t n) const {
        ModInt res(1), mul(x);
        while(n){
            if (n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }
    
    ModInt inv() const {
        int a = x, b = mod, u = 1, v = 0;
        while (b) {
            int t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        if (u < 0) u += mod;
        return u;
    }
    
};
using mint = ModInt<mod>;

mint fact[maxn], invfact[maxn];

void init() {
	fact[0] = invfact[0] = 1;
	for (int i = 1; i <= maxn; ++i) fact[i] = fact[i - 1] * i;
	invfact[maxn - 1] = fact[maxn - 1].inv();
	for (int i = maxn - 2; i; --i) invfact[i] = invfact[i + 1] * (i + 1);
}

inline mint C(int a, int b){
    if (a < 0 || b < 0 || a < b) return 0;
    return fact[a] * invfact[b] * invfact[a - b];
}

mint Catalan(int n){
    return C(n * 2, n) - C(n * 2, n - 1);
}

void test() {
    init();
}