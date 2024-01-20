/**
 * @brief 增广路算法（匈牙利算法）求二分图最大图匹配
 * O(N M)
 */


#include <iostream>

const int maxn = 1e5 + 10, maxe = 1e5 + 10;

struct edge {
    int v, ne;
} e[maxe];       // 建立左 -> 右的单向边即可

int head[maxn], idx = 1;
int match[maxn], vis[maxn];
int n, m, e;     // 左端点数量、右端点数量、边的数量


int dfs(int u) {
    for (int i = head[u]; i; i = e[i].ne) {
        int v = e[i].v;
        if (!vis[v]) {
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int Hungarian() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) vis[j] = 0;
        ans += dfs(i);
    }
    return ans;
}