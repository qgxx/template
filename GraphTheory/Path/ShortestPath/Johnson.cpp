#include <vector>
#include <queue>
#include <cstring>

const int maxn = 1e5 + 10, maxm = 1e5 + 10;
const long long INF = 1e9;

struct edge {
    int v, w, ne;
};

struct node {
    int dis, u;
    bool operator > (const node & a) const { return dis > a.dis; }
};

edge e[maxm];       
int head[maxn], idx;
int h[maxn], dis[maxn], vis[maxn], cnt[maxn];
std::vector<int> res[maxn];

bool SPFA(int n, int s) {
    std::queue<int> q;
    memset(h, 63, sizeof h);
    for (int i = 0; i <= n; i++) q.push(i), vis[i] = 1;
    h[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        vis[u] = 0;
          for (int i = head[u]; i != -1; i = e[i].ne) {
            int v = e[i].v, w = e[i].w;
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] > n) return false;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }

    return true;
}

void Dijkstra(int n, int s) {
    std::priority_queue<node, std::vector<node>, std::greater<node> >q;
    for (int i = 1; i <= n; i++) dis[i] = INF;
    memset(vis, 0, sizeof vis);
    dis[s] = 0;
    q.push({0, s});

    while (!q.empty()) {
        int u = q.top().u;
        q.pop();
        if (vis[u]) continue;

        vis[u] = 1;
        for (int i = head[u]; i != -1; i = e[i].ne) {
            int v = e[i].v, w = e[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) q.push({dis[v], v});
            }
        }
    }
}

void add(int u, int v, int w) {
    e[++idx] = {v, w, head[u]};  
    head[u] = idx;
}

/**
 * @brief 求出无负环图(稀疏图)上任意两点间最短路径
 *        O(NMlogM)
 * 
 * @param n 
 */
void Johnson(int n) {
    for (int i = 1; i <= n; i++) add(0, i, 0);

    if (!SPFA(n, 0)) return ;

    for (int u = 1; u <= n; u++) 
        for (int i = head[u]; i != -1; i = e[i].ne) e[i].w += (h[u] - h[e[i].v]);
    for (int i = 1; i <= n; i++) {
        Dijkstra(n, i);
        for (int j = 1; j <= n; j++) 
            res[i].push_back(dis[j] + h[j] - h[i]);
    }
}