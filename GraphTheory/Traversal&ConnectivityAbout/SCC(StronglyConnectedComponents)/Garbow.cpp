#include <vector>

const int maxn = 1e5 + 10;

struct edge {
    int v, w;
};
std::vector<edge> e[maxn];


/**
 * @brief 维护节点栈的Tarjan实现
 * 
 */
int low[maxn], dfs_colck;
int stk1[maxn], stk2[maxn], tp1, tp2;
int scc[maxn], scc_cnt;

void Garbow(int u) {
    stk1[++tp1] = stk2[++tp2] = u;
    low[u] = ++dfs_colck;
    for (auto ed : e[u]) {
        int v = ed.v;
        if (!low[v]) Garbow(v);
        else if (!scc[v]) 
            while (low[stk2[tp2]] > low[v]) tp2--;
    }
    if (stk2[tp2] == u) {
        tp2--;
        scc_cnt++;
        do {
            scc[stk1[tp1]] = scc_cnt;
        } while (stk1[tp1] != u);
    }
}

void init(int n) {
    dfs_colck = scc_cnt = 0;
    tp1 = tp2 = 0;
    for (int i = 1; i <= n; i++) scc[i] = low[i] = 0;
}

void getSCC(int n) {
    init(n);

    for (int u = 1; u <= n; u++)
        if (!low[u]) Garbow(u);
}