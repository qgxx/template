#include <vector>
#include <queue>
#include <iostream>

const int maxn = 1e5 + 10, maxm = 1e5 + 10;

struct edge {
    int v, ne;
};

edge e[maxm];
int head[maxn], idx = -1;
int in[maxn];    // 每个节点的入度
std::vector<int> L;  // 拓扑序列

/**
 * @brief 拓扑排序
 *        只能在DAG上进行
 *        O(V + E)
 * 
 * @return true 
 * @return false 
 */
bool Kahn(int n) {
    std::queue<int> q;
    for (int i = 1; i <= n; i++) 
        if (in[i] == 0) q.push(i);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        L.push_back(u);
        for (int i = head[u]; i != -1; i = e[i].ne) {
            int v = e[i].v;
            if (--in[v] == 0) q.push(v);
        }
    }

    return (L.size() == n);
}

// 可以用 top序 判断是否无环: 所有 <u, v> ∈ G 满足 top[u] < top[v] (top[]: 点加入队列的顺序)