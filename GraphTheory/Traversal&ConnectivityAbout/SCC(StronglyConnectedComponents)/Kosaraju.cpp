#include <vector>

struct edge {
    int v, w;
};

const int maxn = 1e5 + 10;

std::vector<edge> e[maxn], _e[maxn];  // 原图、反图
int vis[maxn];
int scc[maxn], scc_cnt;
std::vector<int> s;                   // 回溯之前给顶点重新编号(后序遍历)

void dfs1(int u) {
    vis[u] = true;
    for (auto ed : e[u]) {
        int v = ed.v;
        if (!vis[v]) dfs1(v);
    }
    s.push_back(u);
}

void dfs2(int u) {
    scc[u] = scc_cnt;
    for (auto ed : _e[u]) {
        int v = ed.v;
        if (!scc[v]) dfs2(v);
    }
}

/**
 * @brief O(N + M)
 */
void Kosaraju(int n) {
    scc_cnt = 0;
    for (int u = 1; u <= n; u++) 
        if (!vis[u]) dfs1(u);
    
    for (int u = n; u >= 1; u--) {
        if (!scc[s[u]]) {
            ++scc_cnt;
            dfs2(s[u]);
        }
    }
}