// 树的最小权支配集
// 对于所有节点，本身选中或者父节点选中，子节点选中的最小权值和

// f[u][0]: u 被父节点支配，u 的子树的最小权支配集；
// f[u][1]: 选中 u，u 的子树的最小权支配集；
// f[u][2]: u 被子节点支配，u 的子树的最小权支配集

// f[u][0] = sum{min(f[v][1], f[v][2]), v ∈ son(u)}
// f[u][1] = w[u] + sum{min{f[v][0], f[v][1], f[v][2]},v ∈ son(u)}
// f[u][2] = sum{min(f[v][1], f[v][2]), v ∈ son(u)} + min{f[v][1] - min(f[v][1], f[v][2]), v ∈ son(u)}


#include <algorithm>

using namespace std;
using ll = long long;

const int maxn = 1e5 + 10;
const ll inf = 1e18;

struct edge {
    int v, ne;
} e[maxn << 1];
int n, head[maxn], idx;
ll w[maxn], f[maxn][3];

void dfs(int u, int fa) {
    f[u][1] = w[u];
    f[u][0] = 0;
    ll mindiff = inf;
    for (int i = head[u]; i != -1; i = e[i].ne) {
        int v = e[i].v;
        if (v == fa) continue;
        dfs(v, u);
        f[u][1] += min({f[v][0], f[v][1], f[v][2]});
        f[u][0] += min(f[v][1], f[v][2]);
        mindiff = min(mindiff, f[v][1] - min(f[v][1], f[v][2]));
    }
    f[u][2] = f[u][0] + mindiff;
}

void wk() {
    dfs(1, 0);
    int ans = min(f[1][1], f[1][2]);
}

// 最小支配集把权值改为 1 即可