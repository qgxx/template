#include <vector>
#include <queue>
#include <cstring>

struct edge {
    int v, w, ne;                   // u -(w)-> v 
};

struct node {
    int dis, u;                  // dist(s -> u)
    bool operator > (const node & a) const { return dis > a.dis; }
};

const int maxn = 1e5 + 10, maxm = 1e5 + 10;       // N : count(Vertex);

edge e[maxm];      
int head[maxn], idx;
int dis[maxn], vis[maxn];        // dist(s -> i);  isConfirm(dist(s -> i)shortest-path)
std::priority_queue<node, std::vector<node>, std::greater<node> > q;

/**
 * @brief 优先队列优化Dijkstra
 *        求解 非负权图 上单源最短路径
 *        O(MlogM), M : count(Edge)
 * 
 * @param n count(Vertex)
 * @param s start Vertex
 */
void Dijkstra(int n, int s) {
    memset(dis, 0x3f, sizeof dis);
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
                q.push({dis[v], v});
            }
        }
    }
}