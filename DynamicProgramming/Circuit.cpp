// 当区间为环时


#include <algorithm>

const int maxn = 1e3 + 10, inf = 0x3f3f3f3f;

int a[maxn], f[maxn][maxn], s[maxn];

// 任选一个节点将环断开为链，并在其后接一条相同的链
void dp1(int n) {
    for (int i = 1; i <= n; i++) a[i + n] = a[i];
    // 其他预处理

    n <<= 1;
    for (int len = 2; len <= n; ++len)
        for (int l = 1, r = len; r <= n; ++l, ++r) 
            for (int k = l; k < r; k++) 
                f[l][r] = std::min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
    n >>= 1;
    int ans = inf;
    for (int i = 1; i <= n; ++i) ans = std::min(ans, f[i][i + n - 1]);
} 


// 任选一个节点断开形成链，在链上此进行dp
// 强行连接断开的两个点，再进行一次dp
// 两个dp的最优解就是答案
// 初始化不同，dp转移方程是一样的