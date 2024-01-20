// 倍增法求最近公共祖先
// 单次查询: O(logn)


#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;

struct edge {
    int v, ne;
};

edge e[maxn * 2];
int head[maxn], idx;
int fa[maxn][__lg(maxn) + 1], vis[maxn], depth[maxn];

void add(int u, int v) {
    e[++idx] = {v, head[u]};
    head[u] = idx;
}

void dfs(int u, int father = 0) {
    if (vis[u]) return;
    vis[u] = true;
    depth[u] = depth[father] + 1;
    fa[u][0] = father;
    for (int k = 1; k <= __lg(depth[u]); k++) fa[u][k] = fa[fa[u][k - 1]][k - 1];
    for (int i = head[u]; i != -1; i = e[i].ne) dfs(e[i].v, u);
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    while (depth[a] != depth[b]) b = fa[b][__lg(depth[b] - depth[a])];
    if (a == b) return a;
    for (int k = __lg(depth[a]); k >= 0; k--)
        if (fa[a][k] != fa[b][k]) a = fa[a][k], b = fa[b][k];
    return fa[a][0];  // 2^k - sum(2^(k-1) ... 1) = 1
}

void test() {
    // init ... 
    // add ...
    int u;  // 数根结点的序号
    dfs(u, 0);
    // lca(int u, int v)
}


// 可以借助LCA求两点之间的距离
// p = lca(u, v)
// dist(u, v) = depth(u) + depth(v) - depth(p) * 2