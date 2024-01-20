// 重链部分

#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;

struct edge {
    int v, ne;
} e[maxn * 2];
int head[maxn], idx;
int fa[maxn], dep[maxn], sz[maxn], hson[maxn];  // 父节点、深度、子树大小、重儿子
int top[maxn], dfn[maxn], dfn_cnt;   // 所属链头、时间戳（dfs序）、

void dfs1(int u) {
    hson[u] = -1, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].ne) {
        int v = e[i].v;
        if (!dep[v]) {
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v);
            sz[u] += sz[v];
            if (hson[u] == -1 || sz[v] > sz[hson[u]]) hson[u] = v;
        }
    }
}

void dfs2(int u, int l) {
    top[u] = l, dfn[u] = ++dfn_cnt, w_dfn[dfn_cnt] = w[u];
    if (hson[u] == -1) return;
    dfs2(hson[u], l);
    for (int i = head[u]; i; i = e[i].ne) {
        int v = e[i].v;
        if (v != hson[u] && v != fa[u]) dfs2(v, v);
    }
}

void test() {
    int s;    // 根节点
    dep[s] = 1;
    dfs1(s);
    dfs2(s, s);

    build();  // 线段树
}


/**
 * @brief 组合线段树实现路径查询和修改、子树查询和修改
 * 使用 dfn 来建树
 * 以区间和为例
 */
using ll = long long;
ll w[maxn], w_dfn[maxn];
int n, mod;
int tree[maxn << 2];

void build(int p = 1, int cl = 1, int cr = n) {
    if (cl == cr) return void(tree[p] = w_dfn[cl]);
    int mid = (cl + cr) >> 1;
    build(p << 1, cl, mid);
    build(p << 1 | 1, mid + 1, cr);
    tree[p] = (tree[p << 1] + tree[p << 1 | 1]) % mod;
}

void push_down(int p, int len) {}

void update(int l, int r, int d, int p = 1, int cl = 1, int cr = n) {}

ll query(int l, int r, int p = 1, int cl = 1, int cr = n) {}

void update_path(int l, int r, int d) {
    while (top[l] != top[r]) {
        if (dep[top[l]] < dep[top[r]]) swap(l, r);
        update(dfn[top[l]], dfn[l], d);
        l = fa[top[l]];
    }
    if (dep[l] > dep[r]) swap(l, r);
    update(dfn[l], dfn[r], d);
}

ll query_path(int l, int r) {
    int ans = 0;
    while (top[l] != top[r]) {
        if (dep[top[l]] < dep[top[r]]) swap(l, r);
        ans += query(dfn[top[l]], dfn[l]), ans %= mod;
        l = fa[top[l]];
    }
    if (dep[l] > dep[r]) swap(l, r);
    ans += query(dfn[l], dfn[r]);
    return (ans % mod);
}

// 子树维护
void update_subtree(int x, int d) {
    update(dfn[x], dfn[x] + sz[x] - 1, d);
}

ll query_subtree(int x) {
    return query(dfn[x], dfn[x] + sz[x] - 1);
}