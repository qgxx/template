// 线性基
// 可以用来求解整个序列的子序列异或和极值问题
#include <cstring>
#include <algorithm>

using ll = long long;

struct LinearBasis {
    ll b[60], p[60];  // b[]: 线形基; p[]: 查询第 k 小时改造的线形基
    int num, cnt;     // num: 线形基中元素个数; t: 改造线形基
    LinearBasis() {
        memset(b, 0, sizeof b); memset(p, 0, sizeof p);
        cnt = num = 0;
    }
    void insert(ll x) {
        for (int i = 59; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (b[i]) x ^= b[i];
                else { b[i] = x; ++num; break; }
            }
        }
    }
    ll query_max() {
        ll ans = 0;
        for (int i = 59; i >= 0; --i) if ((ans ^ b[i]) > ans) ans ^= b[i];
        return ans;
    }
    ll query_min() {
        for (int i = 0; i < 60; ++i) if (b[i]) return b[i];
        return 0;
    }
    void rebuild() {
        for (int i = 59; i >= 0; --i) 
            for (int j = i - 1; j >= 0; --j) 
                if ((b[i] >> j) & 1) b[i] ^= b[j];
        for (int i = 0; i < 60; ++i) if (b[i]) p[cnt++] = b[i];
    }
    ll query_kth(int k) {
        ll ans = 0;
        if (k >= (1ll << cnt)) return -1;
        for (int i = 59; i >= 0; --i) if ((k >> i) & 1) ans ^= p[i];
        return ans;
    } 
    void operator+=(const LinearBasis &t) {
        for (int i = 59; i >= 0; --i) if (t.b[i]) insert(t.b[i]);
    } 
};
LinearBasis Union(const LinearBasis &l1, const LinearBasis &l2) {
    LinearBasis ans = l1;
    for (int i = 59; i >= 0; --i) if (l2.b[i]) ans.insert(l2.b[i]);
    return ans;
}


// 前缀线性基: 可以用来维护整个序列一段区间的异或和极值问题
const int maxn = 5e5 + 10;

struct PrefixLinearBasis {
    int b[maxn][32], pos[maxn][32], num;  
    // b[][]: 前缀线形基; pos[][]: 修改 i 的最后一个数; num: 线形基中元素个数
    PrefixLinearBasis() {
        memset(b, 0, sizeof b); memset(pos, 0, sizeof pos); num = 0;
    }
    void clear() {
        memset(b, 0, sizeof b); memset(pos, 0, sizeof pos); num = 0;
    }
    void insert(int x) {
        ++num;
        for (int i = 0; i < 32; ++i) b[num][i] = b[num - 1][i], pos[num][i] = pos[num - 1][i];

        int p = num;
        for (int i = 31; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (b[num][i]) {
                    if (pos[num][i] < p) { std::swap(b[num][i], x); std::swap(pos[num][i], p); }
                    x ^= b[num][i];
                }
                else { b[num][i] = x; pos[num][i] = p; break; }
            }
        }
    }
    int query_max(int l, int r) {
        int ans = 0;
        for (int i = 31; i >= 0; --i) {
            if (pos[r][i] < l) continue;
            if ((ans ^ b[r][i]) > ans) ans ^= b[r][i];
        }
        return ans;
    }
    int query_min(int l, int r) {
        for (int i = 0; i < 32; ++i) {
            if (pos[r][i] < l) continue;
            if (b[r][i]) return b[r][i];
        }
        return 0;
    }
};