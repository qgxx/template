#include <vector>

const int maxn = 1e5 + 10, maxm = 1e5 + 10;  // 无向图 m 开双倍

/**
 * @brief 链式前向星
 *        边集数组(直接存边) + 邻接表
 * 
 */
struct edge {
    int v, w, ne;
};

int idx;    // idx(edge) : 0... ; count(e) = idx
int head[maxn];
edge e[maxm];

void init(int n) {
    idx = -1;
    for (int i = 1; i <= n; i++) head[i] = -1;
}

void add(int u, int v, int w) {
    e[++idx] = {v, w, head[u]};  
    head[u] = idx;
}

void traversal(int u) {
    for (int i = head[u]; i != -1 ;i = e[i].ne) 
        int v = e[i].v, w = e[i].w;
}


/**
 * @brief 邻接表
 * 
 */
struct Edge {
    int v, w;
};

std::vector<Edge> e[maxn];