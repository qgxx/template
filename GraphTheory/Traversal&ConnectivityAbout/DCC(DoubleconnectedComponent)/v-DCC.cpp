// 点双连通分量(极大双连通子图 : 对于这个连通分量的子图极大)
// G 可能有多个 DCC，每个点可能属于多个 DCC
// 去掉所有割点之后的连通块(包括单独的一个点)集合

#include <algorithm>
#include <vector>

const int maxn = 1e5 + 10, maxm = 1e5 + 10;

struct edge {
    int v, ne;
};

edge e[maxm * 2];
int head[maxn], idx;

int dfn[maxn], low[maxn], dfn_cnt;

int stk[maxn], tp;
int dcc[maxn], dcc_cnt;
std::vector<int> v_dccSet[maxn];

void Tarjan(int u, int father) {
    dfn[u] = low[u] = ++dfn_cnt;
    stk[++tp] = u;
    int child = 0;

    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v;
        if (!dfn[v]) {
            child++;
            Tarjan(v, u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                dcc_cnt++;
                while (stk[tp + 1] != v) {
                    dcc[stk[tp]] = dcc_cnt;
                    v_dccSet[dcc_cnt].push_back(stk[tp--]);
                }
                v_dccSet[dcc_cnt].push_back(u);
                dcc[u] = dcc_cnt;
            }
        }
        else low[u] = std::min(low[u], dfn[v]);
    }
    if (father == 0 && child == 0) {
        v_dccSet[++dcc_cnt].push_back(u);
        dcc[u] = dcc_cnt;
    }
}

void getEDCC(int n) {
    for (int i = 1; i <= n; i++) 
        if (!dfn[i]) {
            tp = 0;
            Tarjan(i, 0);
        }
}