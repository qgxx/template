// 并查集

#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;

int p[maxn], sz[maxn], h[maxn];

int find(int x) { 
    return (p[x] == x ? x : p[x] = find(p[x]));
}

/**
 * @brief 按秩合并(启发式合并)，减慢退化
 * 
 * @param h[] : 树高上界
 * @param x 
 * @param y 
 */
void merge(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return;
    if (h[px] < h[py]) swap(px, py);
    sz[px] += sz[py];
    p[py] = px;
    if (h[px] == h[py]) h[px]++;
}

void init(int n) {
    for (int i = 1; i <= n; i++) {
        p[i] = i; h[i] = 1; sz[i] = 1;
    }
}


/**
 * @brief 分类并查集
 * 把p[] 开 n 倍：1 ~ n，n + 1 ~ 2 * n ... 分别存储不同的种类
 */
