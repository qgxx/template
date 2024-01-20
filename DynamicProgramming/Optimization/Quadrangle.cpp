// 四边形不等式优化
// 最优决策点数组: m[][]
// m[l][r - 1] <= m[l][r] <= m[l + 1][r]

// 单调性：
// l1 <= l2 <= r2 <= r1: w(l1, r1) >= w(l2, r2)
// 四边形不等式：
// l1 <= l2 <= r2 <= r1: w(l1, r2) + w(l2, r1) <= w(l1, r1) + w(l2. r2)


// 转移方程为：dp[l][r] = min(dp[l][k], dp[k + 1][r]) + w(l, r)   
// 定理：
// 当二元方程 w(l, r)满足单调性并且符合四边形不等式，dp转移方程也符合四边形不等式
// dp转移方程符合四边形不等式时，转移方程的最优决策点 k 符合单调性
// 根据 k 的单调性可以缩小决策范围

// 转移方程不是求解最小时，可能不符合上述定理，此时可以单表判断 k 是否单调、dp是否符合四边形不等式，只要符合就可以使用
// 可以直接打表判断是否满足上述条件来决定使用四边形不等式优化


const int maxn = 1e3;

int m[maxn][maxn], f[maxn][maxn], s[maxn];

void test(int n) {
	for (int i = 1; i <= n; i++) m[i][i] = i;  // 初始化

	for (int l = (n << 1); l >= 1; --l)  // 阶段
        for (int r = l + 1; r <= (n << 1); ++r) {  // 状态
            for (int k = m[l][r - 1]; k <= m[l + 1][r]; k++) {  // 决策（优化部分）
                int t = f[l][k] + f[k + 1][r] + s[r] - s[l - 1];
                if (t < f[l][r]) f[l][r] = t, m[l][r] = k;
            } 
        }
}
