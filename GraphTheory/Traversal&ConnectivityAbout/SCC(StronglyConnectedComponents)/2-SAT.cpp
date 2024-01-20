// Tarjan求缩点
// O(N + M)
// ai可以取两种情况，但不能同时出现
// 0: ai = 0 ; 1: ai = 1

#include <algorithm>

const int maxn = 1e3 + 10, maxk = 1e5 + 10;

struct edge {
    int v, ne;
};

edge e[maxn * 100];
int head[maxn * 2], idx; 

int dfn[maxn * 2], low[maxn * 2], dfn_cnt;
int stk[maxn * 2], tp, in_stack[maxn * 2];
int scc[maxn * 2], scc_cnt;

bool vis[maxk];
int ans[maxk];

void add(int u, int v) {
    e[++idx] = {v, head[u]};
    head[u] = idx;
}

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfn_cnt;
    stk[++tp] = u;
    in_stack[u] = 1;

    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v;
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if (in_stack[v]) low[u] = std::min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stk[tp--];
            in_stack[v] = 0;
            scc[v] = scc_cnt;
        } while (u != v);
    }
}

bool getAns(int n, int k) {
    // init();
    // add(i * 2, i * 2 + 1);
    for (int i = 1; i <= k * 2; i++) 
        if (dfn[i]) Tarjan(i);

    for (int i = 1; i <= k * 2; i += 2) 
        if (scc[i] == scc[i + 1]) return false;
    
    /**
     * @brief 得到一组输出方案
     * 1. 可以通过变量在图中的拓扑排序，如果 x 在 !x 之后(x > !x)，取 x 为真；
     * 2. Tarjan缩点(用到了stack，相当于反拓扑)，如果 x 在 !x 之前(x < !x)，取 x 为真；
     * 
     */
    // 从 1 开始 
    // >> : 1 3 5 
    for (int i = 1; i <= k * 2; i += 2) {
        int t1 = scc[i], t2 = scc[i + 1];
        if (vis[t1]) {
            ans[(i + 1) >> 1] = 0;
            continue;
        }
        if (vis[t2]) {
            ans[(i + 1) >> 1] = 1;
            continue;
        }
        if (t1 < t2) {
            vis[t1] = true;
            ans[(i + 1) >> 1] = 0;
        }
        else {
            vis[t2] = true;
            ans[(i + 1) >> 1] = 1;
        }
    }
    ans[k + 1] = 0;
    // cout << (ans + 1);
    return true;
}