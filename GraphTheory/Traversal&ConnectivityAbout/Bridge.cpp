// 桥
// 删除边 e 之后，G 分类成两个互不相连的子图
// dfn[u] < low[v] bridge : u->v

#include <algorithm>

const int maxn = 1e5 + 10, maxm = 1e5 + 10;

struct edge {
    int v, ne;
};

edge e[maxm * 2];
int head[maxn], idx = -1;

int dfn[maxn], low[maxn], dfn_cnt;
bool bridge[maxm * 2];

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

void getBridge(int n) {
    for (int i = 1; i <= n; i++) 
        if (!dfn[i]) Tarjan(i, 0);
}