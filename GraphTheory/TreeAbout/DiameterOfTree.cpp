// 树的直径

// 若树上所有边边权均为正，则树的所有直径中点重合

#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;

struct edge {
    int v, ne, w;
};

edge e[maxn];
int head[maxn * 2], idx;
int d[maxn], vis[maxn], ans;

/**
 * @brief 树形dp
 * 
 * 可以处理负边权，但不能获得更多的信息
 * @param u 
 */
void dp(int u) {
    vis[u] = 1;
    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v, w = e[i].w;
        dp(v);
        ans = max(ans, d[u] + d[v] + w);
        d[u] = max(d[u], d[v] + w);
    }
}


int c;
void dfs(int u, int fa) {
    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v, w = e[i].w;
        if (v == fa) continue;
        d[v] = d[u] + w;
        if (d[v] > d[c]) c = v;
        dfs(v, u);
    }
}
void get() {
    dfs(1, 0);  // 任意选择一个节点作为根
    d[c] = 0, dfs(c, 0);
    // Diameter : d[c]
}