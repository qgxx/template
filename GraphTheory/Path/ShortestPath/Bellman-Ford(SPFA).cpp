#include <queue>
#include <cstring>

struct edge {
    int v, w, ne;
};

const int maxn = 1e5 + 10, maxm = 1e5 + 10;

edge e[maxm];
int head[maxn], idx;
int dis[maxn], cnt[maxn], vis[maxn];
std::queue<int> q;

/**
 * @brief 队列优化Bellman-Ford
 *        求出有负权的图的最短路，并可以对最短路不存在的情况进行判断
 *        在判断是否是负环时，初始应该加入所有的点
 *        O(NM)
 * 
 * @param n       count(Vertex)
 * @param s       start Vertex
 * @return true   
 * @return false  最短路经过负环
 */
bool SPFA(int n, int s) {
    memset(dis, 0x3f, sizeof dis);

    // 求最短路
    dis[s] = 0, vis[s] = 1;
    q.push(s);

    /** @brief 判断负环
    for (int i = 1; i <= n; i++) vis[i] = 1, q.push(i);
    dis[s] = 0;
    */

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = e[i].ne) {
            int v = e[i].v, w = e[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] > n) return false;   
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }

    return true;
}
