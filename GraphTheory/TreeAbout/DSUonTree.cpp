// 树上启发式合并： 解决树上离线问题
// 常用来解决对于每个点，询问关于其子树的某些信息这样的问题
// 经常和树剖相关联，优先查询轻点的信息，保留重点的信息
// O(NlogN)

const int maxn = 1e5 + 10;

int n;
struct edge {
	int v, ne;
} e[maxn * 2];
int head[maxn], idx = 1;
int sz[maxn], hson[maxn], L[maxn], R[maxn], node[maxn], dfn_cnt;
// 子树大小、重点、子树左右端点dfn序、dfn序对应原点

void add_e(int u, int v) {
	e[++idx] = {v, head[u]};
	head[u] = idx;
}


// 树剖标记轻、重点
void dfs1(int u, int fa) {
	sz[u] = 1, hson[u] = -1, L[u] = ++dfn_cnt, node[dfn_cnt] = u;
	for (int i = head[u]; i; i = e[i].ne) {
		int v = e[i].v;
		if (v != fa) {
			dfs1(v, u);
			sz[u] += sz[v];
			if (hson[u] == -1 || sz[hson[u]] < sz[v]) hson[u] = v;
		}
	}
	R[u] = dfn_cnt;
}

// 预处理查询信息
void dfs2(int u, int fa, bool is_keep = 0) {
	for (int i = head[u]; i; i = e[i].ne) {
		int v = e[i].v;
		if (v != fa && v != hson[u]) dfs2(v, u);
	}
	if (hson[u] != -1) dfs2(hson[u], u, 1);  // 最后查询重点，保留其信息

	// add(u)
	for (int i = head[u]; i; i = e[i].ne) {
		int v = e[i].v;
		if (v != fa && v != hson[u]) 
			for (int j = L[v]; j <= R[v]; j++); // add(node[j])
	}
	// ans[u] = ...

	if (!is_keep) {
		for (int i = L[u]; i <= R[u]; i++); // del(node[i])
	} // 删除轻点信息
}