// 稠密图
// O(N ^ 2 + M)

#include <algorithm>

const int maxn = 5e3 + 10, maxm = 2e5 + 10, inf = 0x3f3f3f3f;

struct edge {
    int v, w, ne;
};

edge e[maxm * 2];
int head[maxn], idx;

int dis[maxn], vis[maxn];

void add(int u, int v, int w) {
    e[++idx] = {v, w, head[u]};
    head[u] = idx;
}

int Prim(int n) {
    for (int i = 2; i <= n; i++) dis[i] = inf;

    for (int i = head[1]; i != -1; i = e[i].ne) 
        dis[e[i].v] = std::min(dis[e[i].v], e[i].w);
    
    int ans = 0;        // 最下权值和
    int tot = 0, u = 1;
    while (++tot < n) {
        int mind = inf, t = u;
        vis[u] = true;
        
        for (int i = 1; i <= n; i++) 
            if (!vis[i] && dis[i] < mind) {
                mind = dis[i];
                u = i;
            }
        if (u == t) return -inf;
        ans += mind;

        for (int i = head[u]; i != -1; i = e[i].ne) {
            int v = e[i].v;
            if (dis[v] > e[i].w && !vis[v]) dis[v] = e[i].w;  // 把已经相连的子树当作缩点，dis[v] = e[i].w
        }
    }

    return ans;
}