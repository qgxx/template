/**
 * @brief EK求最大流
 * O(N M^2)
 * 可用于处理1e3 ~ 1e4
 */


#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

const int maxn = 2e2 + 10, maxm = 5e3 + 10, inf = 0x3f3f3f3f;

struct edge {
    int v, ne;
    ll w;
} e[maxm * 2];

int n, m, s, t;
int head[maxn], idx = 1, isE[maxn][maxn];
int vis[maxn], pre[maxn];
ll flow[maxn];

void add(int u, int v, ll w) {
    e[++idx] = {v, head[u], w};
    head[u] = idx;
}

int bfs() {
    for (int i = 1; i <= n; i++) vis[i] = 0;
    queue<int> q;
    q.push(s);
    vis[s] = 1, flow[s] = inf;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != 0; i = e[i].ne) {
            int v = e[i].v; ll w = e[i].w;
            if (w == 0 || vis[v] == 1) continue;
            flow[v] = std::min(flow[u], w);
            pre[v] = i;
            q.push(v);
            vis[v] = 1;
            if (v == t) return 1;
        }
    }
    return 0;
}

void update(ll &ans) {
    int u = t;
    while (u != s) {
        int v = pre[u];
        e[v].w -= flow[t];
        e[v ^ 1].w += flow[t];
        u = e[v ^ 1].v;
    }
    ans += flow[t];
}

ll EdmondsKarp() {
	int u, v;
    ll w, ans = 0;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		if (isE[u][v] == 0) { 
			add(u, v, w), add(v, u, 0);
			isE[u][v] = idx;
		}
		else e[isE[u][v] - 1].w += w;  // 处理重边
	}
	while(bfs()) update(ans);

	return ans;
}