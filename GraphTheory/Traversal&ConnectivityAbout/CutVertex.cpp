// 割
// 删除 v 及相连边之后，G 分裂成两个及以上互不相连的子图
// dfn[u] <= low[v]

#include <algorithm>

const int maxn = 1e5 + 10, maxm = 2e5 + 10; 

struct edge {
    int v, ne;
};

edge e[maxm];
int head[maxn], idx;

int dfn[maxn], low[maxn], dfn_cnt;
bool cut[maxn];

/**
 * @brief Version_1
 * 
 * @param u 
 * @param father root
 */
void Tarjan(int u, int father) {
    dfn[u] = low[u] = ++dfn_cnt;
    int child = 0;
    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v;
        if (!dfn[v]) {
            Tarjan(v, father);
            low[u]= std::min(low[u], low[v]);

            if (dfn[u] <= low[v] && u != father) cut[u] = true;
            if (u == father) child++;
        }
        low[u] = std::min(low[u], dfn[v]);
    }
    if (child >= 2 && u == father) cut[u] = true;
}


/**
 * @brief Version_2😶‍🌫 推荐用这个
 * 
 * @param u 
 * @param father root
 */
void Tarjan_2(int u, int father) {
    dfn[u] = low[u] = ++dfn_cnt;
    int child = 0;
    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v;
        if (!dfn[v]) {
            Tarjan_2(v, father);
            low[u]= std::min(low[u], low[v]);

            if (dfn[u] <= low[v]) {
                child++;
                if (u != father || child > 1) cut[u] = true;
            }
        }
        else low[u] = std::min(low[u], dfn[v]);
    }
}

/**
 * @brief Version_3
 * 
 * @param u 
 * @param father root
 */
void Tarjan_3(int u, int father) {
    dfn[u] = low[u] = ++dfn_cnt;
    int child = 0;
    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v;
        if (!dfn[v]) {
            child++;
            Tarjan_3(v, u);
            low[u] = std::min(low[u], low[v]);
            if (dfn[u] <= low[v]) cut[u] = true; 
        }
        else if (v != father) low[u] = std::min(low[u], dfn[v]);
    }

    if (father == u && child < 2) cut[u] = false;
}

void getcut(int n) {
    for (int i = 1; i <= n; i++) 
        if (!dfn[i]) {
            Tarjan(i, i);  
            // Tarjan_2(i, i);
            // Tarjan_3(i, i);  // Version_2, father用虚拟节点(比如 0)也可以, 相对应的father == ? 也要改成对应的(0)
        }
    
    for (int i = 1; i <= n; i++) 
        if (cut[i]) {
            // do...
        }
}