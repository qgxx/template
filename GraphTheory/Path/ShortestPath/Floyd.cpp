#include <algorithm>

const int maxn = 1e2 + 10;

int f[maxn][maxn]; // f[][][]: f[k]表示只运行经过节点1~k（子图1、2...k中的路径，u、v不一定在子图中）

/**
 * @brief 求任意两个结点之间的最短路
 *        适用于任何图，不管有向无向，边权正负，但是最短路必须存在。（不能有个负环）
 *        O(N^3)
 * 
 * @param n count(Vertex)
 */
void Floyd(int n) {
    for (int k = 1; k <= n; k++)
        for (int u = 1; u <= n; u++) 
            for (int v = 1; v <= n; v++)
                f[u][v] = std::min(f[u][v], f[u][k] + f[k][v]);
}


/**
 * @brief 使用floyd求解最小权值和的环及其数量
 * 
 * 在节点1~k的子图时，f[k-1][u][v]和(u,k)、(k, v)共同构成了环
*/

#include <cstring>
using ll = long long;
const int N = 510, mod = 998244353;
const ll inf = 0x3f3f3f3f3f3f3f3f;
ll dis[maxn][maxn], cnt[maxn][maxn], g[maxn][maxn];
// g保存初始路径

void circuit(int n) {
    memcpy(dis, g, sizeof g);
    ll res = inf, c = 0;   // 最小权值回路、构成最小权值回路的方案数量
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i) {
            for (int j = 1; j < k; ++j) {
                if (dis[i][j] + g[j][k] < res - g[k][i]) {
                    res = 1ll * dis[i][j] + g[j][k] + g[k][i];
                    c = cnt[i][j];
                } else if (dis[i][j] + g[j][k] == res - + g[k][i]) {
                    c += cnt[i][j];
                    if (c >= mod) c -= mod;
                }
            }
    }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j || j == k || i == k) continue;
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    cnt[i][j] = 1ll * cnt[i][k] * cnt[k][j] % mod;
                } else if (dis[i][j] == dis[i][k] + dis[k][j]) {
                    cnt[i][j] += 1ll * cnt[i][k] * cnt[k][j];
                    if (cnt[i][j] >= mod) cnt[i][j] -= mod;
                }
            }
        }
    }
}