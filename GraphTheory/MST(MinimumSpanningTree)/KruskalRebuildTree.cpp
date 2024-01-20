#include <vector>
#include <array>
#include <functional>

using namespace std;

// 使用这个方法建立的是森林，所以lca初始化是从底部开始建立倍增表，然后分别求树的深度。
// 程序是吸氧的，可以开O2
std::pair<std::vector<int>, std::vector<int>>
kruskalRebuildTree(int n, std::vector<std::array<int, 3>> edges, 
std::function<bool(std::array<int, 3>, std::array<int, 3>)> comp) {
    /**
     * @brief 实现 Kruskal 重构树, 两结点的 lca 的点权表示原图中两结点路径中最小边权的最大值。
     *
     * @param n     : 点的个数
     * @param edges : 表示无向图的边。每条边中, 第 0 维度表示边权, 第 1 维度和第 2 维度表示端点
     * @param comp  : 边权的排序方法, std::greater<>() 表示从大到小, std::less<>() 表示从小到大
     *
     * @return 返回一个 pair, 其中 first 代表重构树中每一个结点的点权, second 表示父结点信息
     * 父结点为 0 说明没有父结点。
     *
     * 时间复杂度是 O(m log m), 其中 m 是边的数量, 即 edges.size()
     *
     * 1-index
     */

    std::vector<int> p(2 * n);
    for(int i = 1; i < 2 * n; i++) p[i] = i;
    std::function<int(int)> find = [&](int x){if(x != p[x]) p[x] = find(p[x]); return p[x];};
    // 并查集

    int cnt = n;
    std::sort(edges.begin(), edges.end(), comp);

    std::vector<int> value(n + 1, 0);
    std::vector<int> parent(2 * n, 0);
    for(auto [weight, from, to] : edges) {
        from = find(from);
        to = find(to);

        if(from == to) continue;

        p[from] = ++cnt;
        p[to] = cnt;

        value.push_back(weight);

        parent[from] = cnt;
        parent[to] = cnt;
    }

    parent.resize(value.size());
    return {value, parent};
}

struct LCA{
    LCA(int n, std::vector<int>& parent) : parent(parent), pa(n + 1), depth(n + 1) {
        for(int i = 1; i <= n; i++) {
            if(this->parent[i] <= 0)
                this->parent[i] = i;
            pa[i][0] = this->parent[i];
        }

        for(int i = 1; i < 20; i++) {
            for(int j = 1; j <= n; j++) {
                pa[j][i] = pa[pa[j][i-1]][i-1];
            }
        }

        std::function<int(int)> get_depth = [&](int now) {
            if(now <= 0 || now > n) return 0;
            if(depth[now])
                return depth[now];
            if(parent[now] <= 0 || parent[now] == now)
                return depth[now] = 1;
            return depth[now] = get_depth(parent[now]) + 1;
        };

        for(int i = 1; i <= n; i++)
            depth[i] = get_depth(i);
    }

    int lca(int u, int v) {

        /**
         * @brief 返回 u 和 v 的最近公共祖先, 如果 u 和 v 不连通(森林的情况)则返回 -1
         *
         * 使用倍增法, 时间复杂度是 O(n log n)
         */

        if(pa[u][19] != pa[v][19])
            return -1;

        if(depth[u] < depth[v]) {
            std::swap(u, v);
        }

        for(int i = 19; depth[u] > depth[v]; i--) {
            if(depth[pa[u][i]] >= depth[v]) {
                u = pa[u][i];
            }
        }

        if(u == v) return u;

        for(int i = 19; i >= 0; i--) {
            if(pa[u][i] != pa[v][i]) {
                u = pa[u][i];
                v = pa[v][i];
            }
        }

        return pa[u][0];
    }
private:
    std::vector<int> parent, depth;
    std::vector<std::array<int, 20>> pa;
};

void wk() {
    int n;
    std::vector<std::array<int, 3>> edges; // w, u, v
    auto [value, parent] = kruskalRebuildTree(n, edges, less<>()); // 降序用greater<>()
    LCA t((int)value.size() - 1, parent);
    // t.lca(u, v);
}