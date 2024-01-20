// 圆方树
// 处理简单无向图，把v-DCC缩点当成方点，原点当成
// 把每个v-DCC的原点与它的缩点相连成为一棵子树，然后通过割点连接成一棵树

#include <algorithm>
#include <vector>

struct edge {
    int v, w, ne;
};

const int maxn = 1e5 + 10, maxm = 1e5 + 10;

edge e[maxm * 2];
int head[maxn], idx;

int dfn[maxn], low[maxn], dnf_cnt;

int stk[maxn], tp;

std::vector<int> T[maxn * 2];
int t_cnt;

void Tarjan(int u) {
    dfn[u] = low[u] = ++dnf_cnt;
    stk[++tp] = u;
    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v;
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = std::min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                ++t_cnt;
                while (stk[tp + 1] != v) {
                    int x = stk[tp--];
                    T[t_cnt].push_back(x), T[x].push_back(t_cnt);
                }
                T[t_cnt].push_back(u), T[u].push_back(t_cnt);
            }
        }
        else low[u] = std::min(low[u], dfn[v]);
    }
}

void toTree(int n) {
    t_cnt = n;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tp = 0;
            Tarjan(i);
        }
    }
}