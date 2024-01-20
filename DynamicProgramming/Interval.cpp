// 区间DP
// 从小段开始合并


#include <algorithm>

const int maxn = 110, inf = 1 << 30;

int a[maxn];
int f[maxn][maxn], s[maxn];

void dp1(int n) {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) f[i][j] = inf, f[i][i] = 0;
    // 进行其他的预处理

    for (int len = 2; len <= n; ++len) 
        for (int l = 1, r = len; r <= n; l++, r++) 
            for (int k = l; k < r; k++) 
                f[l][r] = std::min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
}


// 在处理max时，只需要判断两端（代价函数单调），不满足四边形不等式
void dp2(int n) {
	for (int len = 2; len <= n; ++len)
        for (int l = 1, r = len; r <= n; ++l, ++r) 
        	f[l][r] = std::max(f[l][r - 1], f[l + 1][r]) + s[r] - s[l - 1];
}