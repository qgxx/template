#include <algorithm>
#include <vector>

const int maxn = 1e5 + 10, maxm = 1e6 + 10;

struct edge {
    int v, w, ne;
};

int idx;    // idx(edge) : 0...
int head[maxn];
edge e[maxm];


/**
 * @brief Tarjan求强连通分量并缩点
 *        O(N + M)
 * @param dfn[] 时间戳
 * @param low[] 追溯值
 * @param dfn_cnt timestamp时间戳
 * @param scc[] 每个节点所在的SCC
 * @param scc_int 缩点索引
 * @param sz[] 每个SCC缩点的Vertex数量
 * @param stack u 的祖先节点
 */
int dfn[maxn], low[maxn], dfn_cnt;
int stk[maxn], tp, in_stack[maxn];
int scc[maxn], scc_cnt;  
int sz[maxn];          
std::vector<int> sccSet[maxn];  // 每个缩点的集合

void Tarjan(int u) {
    low[u] = dfn[u] = ++dfn_cnt;
    stk[++tp] = u, in_stack[u] = 1;
    for (int i = head[u]; i != -1; i = e[i].ne) {
        const int & v = e[i].v;
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if (in_stack[v]) low[u] = std::min(low[u], low[v]);
    }

    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int v;
        do {
            v = stk[tp--];
            in_stack[v] = 0;
            scc[v] = scc_cnt;
            sz[scc_cnt]++;
            sccSet[scc_cnt].push_back(v);
        } while (u != v);
    }
}

void getSCC(int n) {
    for (int u = 1; u <= n; u++)
        if (!dfn[u]) Tarjan(u);
}
