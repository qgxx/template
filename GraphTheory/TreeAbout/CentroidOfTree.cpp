/**
 * @brief 树的重心
 * 数上所有点的到重心的距离之和是最短的，如果有过的重心则距离相等
 * 如果把两棵树通过一条边相连得到一颗新的数，新的数的重心在原来两棵树的重心的路径上
 * 在一棵树上添加或删除一个叶子，它的重心最多只移动一条边的距离
 */

#include <algorithm>

const int maxn = 1e5 + 10;

struct edge {
    int v, ne;
} e[maxn * 2];

int head[maxn], idx;
int weight[maxn], sz[maxn], n, c1, c2;
// weight[] : 节点的重量 ; sz[] : 子树节点数 + 该节点的节点数量
// c1、c2 : 重心

void init(int n) {
    for (int i = 1; i <= n; i++) head[i] = 0;
    idx = c1 = c2 = 0;
    weight[0] = 0x3f3f3f3f;
}

void add(int u, int v) {
    e[++idx] = {v, head[u]};
    head[u] = idx;
}
// add(u, v), add(v, u)  建立双向边

void dfs(int u, int father) {
    weight[u] = 0, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].ne) {
        int v = e[i].v;
        if (v != father) {
            dfs(v, u);
            sz[u] += sz[v];
            weight[u] = std::max(weight[u], sz[v]);
        }
    }
    weight[u] = std::max(weight[u], n - sz[u]);
    if (weight[u] == weight[c1]) c2 = u;
    if (weight[u] < weight[c1]) c1 = u, c2 = 0;
}