// 树形DP
// DFS在子树进行递归时更新局部最优


// 树形背包DP
// 以树形DP + 组合背包为例
// 以 u 为根的子树，把 u 的子节点为顶点的子树当作不同的组别
// 阶段：不同的子树（组别）；  状态：u 当前的容量；  决策：对每棵子树的决策

#include <algorithm>

const int maxn = 1e3 + 10;

struct edge {
	int v, ne;
} e[maxn];
int head[maxn], idx, w[maxn];
int f[maxn][maxn], sz[maxn], n, m;

void dfs(int u) {
    f[u][1] = w[u], sz[u] = 1;
    for (int i = head[u]; i; i = e[i].ne) {
        int v = e[i].v;
        dfs(v);
        sz[u] += sz[v];
        for (int j = std::min(sz[u], m); j >= 0; --j) 
            for (int k = std::min(sz[v], j - 1); k >= 0; --k) 
                f[u][j] = std::max(f[u][j], f[u][j - k] + f[v][k]);
    }
}



// 换根DP
// 求解每个节点作为根时，可以任选一个节点进行预处理
// 然后进行换根操作转移状态

void dfs1(int u, int fa) {
    sz[u] = 1;
    for (int i = head[u]; i; i = e[i].ne) {
        int v = e[i].v;
        if (v == fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        // ... 预处理各种信息
    }
} 

// 求出f[1]状态 （假设预处理以1为根）,也可能需要在预处理中求出

void dfs2(int u, int fa) {
    for (int i = head[u]; i; i = e[i].ne) {
        int v = e[i].v;
        if (v == fa) continue;
        // f[v]... 进行状态转移
        dfs2(v, u);
    }
}