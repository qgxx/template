// 背包DP : 线性DP的一种

#include <iostream>
# include <algorithm>

const int maxn = 1e5 + 10;


/**
 * @brief 0-1背包
 * O(nW)
 * 每个物品只能选1次，sum(w) <= W下的最大Value
 */
int w[maxn], v[maxn], f[maxn];    // weight, value
int n, W;                         // 物品数, 容量
void backpack1() {
    for (int i = 1; i <= n; i++) std::cin >> w[i] >> v[i];
    f[0] = 0;
    for (int i = 1; i <= n; i++) 
        for (int j = W; j >= w[i]; j--) 
            f[j] = std::max(f[j], f[j - w[i]] + v[i]);
    // ans : f[W];
}


/**
 * @brief 完全背包
 * O(nW)
 * 每个物品可以选择无数次
 */
// 使用滑动窗口优化
int w[maxn], v[maxn], f[maxn];
int n, W;
void backpack2() {
    for (int i = 1; i <= n; i++) std::cin >> w[i] >> v[i];
    f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = w[i]; j <= W; j++)
            f[j] = std::max(f[j], f[j - w[i]] + v[i]);
    // ans : f[W]
}


/**
 * @brief 多重背包
 * 每个物品可以选择c次
 * 二进制优化 : 倍增思想，将其拆分成2的次方倍来表示中间值
 */
int w[maxn], v[maxn], f[maxn], cnt;
int n, W;
void backpack3() {
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        for (int j = 1; j <= c; j <<= 1) {
            w[++cnt] = a * j, v[cnt] = b * j;
            c -= j;
        }
        if (c) w[++cnt] = a * c, v[cnt] = b * c;
    }
    f[0] = 0;
    for (int i = 1; i <= cnt; i++) 
        for (int j = W; j >= w[i]; j--) 
            f[j] = std::max(f[j], f[j - w[i]] + v[i]);
    // ans : f[W]
}

// 当0-1背包、完全背包、多重背包混合出现时，可以为完全背包设置一个非常大的可选c数
// 然后套用多重背包即可（本质是当作0-1背包）

// 二维费用时f增加一个维度


/**
 * @brief 分组背包
 * 对组别做0-1背包，对组内做决策
 */
const int maxg = 110;
int w[maxn], v[maxn], f[maxn], g[maxg][maxn], b[maxn], g_cnt = 1;
void backpack4() {
    int x;  // 组别
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i] >> v[i] >> x;
        b[x]++;
        g[x][b[x]] = i;
        g_cnt = std::max(g_cnt, x);
    }
    for (int i = 1; i <= g_cnt; i++) // 阶段
        for (int j = W; j >= 0; j--) // 状态
            for (int k = 1; k <= b[i]; k++) // 决策
                if (j >= w[g[i][k]]) f[j] = std::max(f[j], f[j - w[g[i][k]]] + v[g[i][k]]);
    // ans : f[W]
}