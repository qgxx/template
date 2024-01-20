// 树链剖析(重链)求最近公共祖先


const int maxn = 1e6 + 10;

struct edge {
    int v, ne;
} e[maxn * 2];
int head[maxn], idx;
int fa[maxn], dep[maxn], sz[maxn], hson[maxn];
int top[maxn], dfn[maxn], rnk[maxn], dfn_cnt;

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
    top[u] = l, dfn[u] = ++dfn_cnt, rnk[dfn_cnt] = u;
    if (hson[u] == -1) return;
    dfs2(hson[u], l); 
    for (int i = head[u]; i; i = e[i].ne) {
        int v = e[i].v;
        if (v != hson[u] && v != fa[u]) dfs2(v, v);
    }
}

int lca(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]]) a = fa[top[a]];
        else b = fa[top[b]];
    }
    return dep[a] > dep[b] ? b : a;
}

void add(int u, int v) {
    e[++idx] = {v, head[u]};
    head[u] = idx;
}

void test() {
	// cin 
	int u; // 根节点的序号
	dep[u] = 1;
	dfs1(u);
	dfs2(u, u);
	// lca()
}