/**
 * @brief ISAP求最大流
 * O(N^2 M) 最优 
 * 可以处理1e4 ~ 1e5
 */


#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

const int maxn = 1e3 + 10, maxm = 1e5 + 10, inf = 1 << 30;

struct edge {
    int v, ne;
    ll w;
} e[maxm * 2];

int n, m, s, t;
int head[maxn], idx = 1;
int dis[maxn], cur[maxn], gap[maxn];

void add(int u, int v, ll w) {
    e[++idx] = {v, head[u], w};
    head[u] = idx;
}

void bfs(){
    queue<int> q; q.push(t);
    for (int i = 0; i <= n; i++) dis[i] = -1, gap[i] = 0;
    dis[t] = 0; gap[0] = 1;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int i = head[u]; i != 0; i = e[i].ne){
            int v = e[i].v;
            if (e[i].w == 0 && dis[v] == -1){
                dis[v] = dis[u] + 1;
                ++(gap[dis[v]]);
                q.push(v);
            }
        }
    }
}

ll dfs(int u = s, ll flow = inf){
    if (u == t) return flow;
    ll used = 0, f;
    for (int i = cur[u]; i != 0; i = e[i].ne){
        cur[u] = i;
        int v = e[i].v;
        if (dis[v] + 1 == dis[u] && e[i].w > 0){
            f = dfs(v, min(e[i].w, flow));
            e[i].w -= f;
            e[i ^ 1].w += f;
            used += f;
            flow -= f;
            if (flow == 0) return used;
        }
    }
    if (--(gap[dis[u]]) == 0) dis[s] = n;
    ++(dis[u]);
    ++(gap[dis[u]]);
    return used;
}

ll ISAP() {
    int u, v; 
    ll w, ans = 0;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, 0);
    }
    bfs();
    while (dis[s] < n) {
        for (int i = 1; i <= n; i++) cur[i] = head[i];
        ans += dfs();
    }

    return ans;
}