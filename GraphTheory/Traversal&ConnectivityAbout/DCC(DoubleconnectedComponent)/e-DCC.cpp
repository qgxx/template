// 边双连通分量(极大双连通子图 : 对于这个连通分量的子图极大)
// G 可能有多个 DCC，每个点可能属于多个 DCC
// 去掉所有桥之后的连通块(包括单独的一个点)集合

#include <vector>

struct edge {
    int v, ne;
};

const int maxn = 1e5 + 10, maxm = 1e5 + 10;

edge e[maxm * 2];
int head[maxn], idx;

int dfn[maxn], low[maxn], dfn_cnt;
bool bridge[maxm * 2];

std::vector<int> e_dccSet[maxm];
int dcc[maxn], dcc_cnt;  // 缩点

void add(int u, int v) {
    e[++idx] = {v, head[u]};
    head[u] = idx;
}

void Tarjan(int u, int father) {
    dfn[u] = low[u] = ++dfn_cnt;
    for (int i = head[u]; i != - 1; i = e[i].ne) {
        int v = e[i].v;
        if (!dfn[v]) {
            Tarjan(v, i);
            low[u] = std::min(low[u], low[v]);

            if (low[v] > dfn[u]) bridge[i] = bridge[i ^ 1] = true;
        }
        else if (i != (father ^ 1)) low[u] = std::min(low[u], dfn[v]);
    }
}

void dfs(int u) {
    dcc[u] = dcc_cnt;
    e_dccSet[dcc_cnt].push_back(u);
    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v;
        if (dcc[v] || bridge[i]) continue;
        dfs(v);
    }
}

void getEDCC(int n) {
    for (int i = 1; i <= n; i++) 
        if (!dfn[i]) Tarjan(i, 0);
    for (int i = 1; i <= n; i++) 
        if (!dcc[i]) {
            ++dcc_cnt;  
            dfs(i);
        }  
}