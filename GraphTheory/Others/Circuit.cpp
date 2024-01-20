// 置换环
// 对于每个节点，让其指向下一步操作之后的位置，首尾相接形成多个环(包括自环)

const int maxn = 1e5 + 10;

int p[maxn], vis[maxn];
int cir_cnt;    // 环的数量

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    dfs(p[u]);
}

void get(int n) {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cir_cnt++;
            dfs(i);
        }
    }
}

// eg: 让所有节点到达指定位置所需的代价：n - cir_cnt