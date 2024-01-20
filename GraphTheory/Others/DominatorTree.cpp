// 支配树
// 对除了 s 外的每一个节点 u 从 idom(u) 到 u 连边，构成一个有 n 个点，n - 1 条边的支配树
// dom(u) = v: v 支配 u; idom(u) = v: v 是除 u 自身外距 u 最近的支配点; s: 起点

#include <iostream>
#include <vector>

using namespace std;

const int maxn = 5e5 + 10;

namespace dtree // 支配树模板
{
    const int MAXN = 500020;
    vector<int> E[MAXN], RE[MAXN], rdom[MAXN];
 
    int S[MAXN], RS[MAXN], cs;
    int par[MAXN], val[MAXN], sdom[MAXN], rp[MAXN], dom[MAXN];
 
    void clear(int n)
    {
        cs = 0;
        for (int i = 0; i <= n; i++)
        {
            par[i] = val[i] = sdom[i] = rp[i] = dom[i] = S[i] = RS[i] = 0;
            E[i].clear();
            RE[i].clear();
            rdom[i].clear();
        }
    }
    void add_edge(int x, int y) { E[x].push_back(y); }
    void Union(int x, int y) { par[x] = y; }
    int Find(int x, int c = 0)
    {
        if (par[x] == x)
            return c ? -1 : x;
        int p = Find(par[x], 1);
        if (p == -1)
            return c ? par[x] : val[x];
        if (sdom[val[x]] > sdom[val[par[x]]])
            val[x] = val[par[x]];
        par[x] = p;
        return c ? p : val[x];
    }
    void dfs(int x)
    {
        RS[S[x] = ++cs] = x;
        par[cs] = sdom[cs] = val[cs] = cs;
        for (int e : E[x])
        {
            if (S[e] == 0)
                dfs(e), rp[S[e]] = S[x];
            RE[S[e]].push_back(S[x]);
        }
    }
    int solve(int s, int *up)
    {
        dfs(s);
        for (int i = cs; i; i--)
        {
            for (int e : RE[i])
                sdom[i] = min(sdom[i], sdom[Find(e)]);
            if (i > 1)
                rdom[sdom[i]].push_back(i);
            for (int e : rdom[i])
            {
                int p = Find(e);
                if (sdom[p] == i)
                    dom[e] = i;
                else
                    dom[e] = p;
            }
            if (i > 1)
                Union(i, rp[i]);
        }
        for (int i = 2; i <= cs; i++)
            if (sdom[i] != dom[i])
                dom[i] = dom[dom[i]];
        for (int i = 2; i <= cs; i++)
            up[RS[i]] = RS[dom[i]];
        return cs;
    }
}

int up[maxn];
vector<int> G[maxn];

void work() {
    int n, m; cin >> n >> m; // 点数、边数
    dtree::clear(n);
    for (int i = 1; i <= n; ++i) G[i].clear();
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        dtree::E[u].push_back(v);  // 把原图建立在 namespace dtree 中
    }
    dtree::solve(1, up);  // 直接支配点保存在 up[] 中
    for (int i = 2; i <= n; ++i) G[up[i]].push_back(i); // 建立支配树
}