/**
 * @brief Dinic求最大流
 * O(n^2 M) 常用
 * 当前弧优化，DFS时跳过残差容量为0的边
 * 可用于处理1e4 ~ 1e5
 */


#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

const int maxn = 1e3 + 10, maxm = 5e3 + 10, inf = 0x3f3f3f3f;

struct edge {
    int v, ne;
    ll w;
} e[maxm * 2];

int n, m, s, t;
int head[maxn], idx = 1;       // idx 必须初始化为 1 
int dis[maxn], cur[maxn];      // cur[] : 当前弧优化标记增广节点

void add(int u, int v, ll w) {
    e[++idx] = {v, head[u], w};
    head[u] = idx;
}

int bfs() {
    for (int i = 1; i <= n; i++) dis[i] = -1;  // ! 记得改
    queue<int> q;
    q.push(s);
    dis[s] = 0, cur[s] = head[s];
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i != 0; i = e[i].ne) {
            int v = e[i].v;
            if (e[i].w > 0 && dis[v] == -1) {
                q.push(v);
                cur[v] = head[v];
                dis[v] = dis[u] + 1;
                if (v == t) return 1;
            }
        }
    }
    return 0;
}

ll Dinic(int u = s, ll flow = inf) {
    if (u == t) return flow;
    ll f, res = 0;
    for (int i = cur[u]; i && flow; i = e[i].ne) {
        cur[u] = i;
        int v = e[i].v;
        if (e[i].w > 0 && dis[v] == dis[u] + 1) {
            f = Dinic(v, min(flow, e[i].w));
            if (f == 0) dis[v] = -1;
            e[i].w -= f;
            e[i ^ 1].w += f;
            res += f;
            flow -= f;
        }
    }
    return res;
} 

ll work() {
    ll ans = 0;
    while (bfs()) ans += Dinic();
    return ans;
}