// 稀疏图
// O(MlogM)

#include <iostream>
#include <algorithm>

const int maxn = 5e3 + 10, maxm = 2e5 + 10, inf = 0x3f3f3f3f;

struct edge {
    int u, v, w;
    bool operator < (const edge & a) const { return w < a.w; } 
};

edge e[maxm];

int p[maxn];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

/**
 * @brief 最小生成树
 * 
 * @param n count(vertex)
 * @param m count(edge)
 * @return int 
 */
int Kruskal(int n, int m) {
    std::sort(e, e + m);

    int ans = 0, cnt = 0;       // ans : 最小权值和
    for (int i = 0; i < m; i++) {
        int pu = find(e[i].u), pv = find(e[i].v);
        if (pu == pv) continue;

        ans += e[i].w;
        p[pv] = pu;
        cnt++;

        if (cnt == n - 1) break;
    }

    if (cnt < n - 1) return -inf;
    return ans;
}

void init(int n, int m) {
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 0; i < m; i++) std::cin >> e[i].u >> e[i].v >> e[i].w;
}