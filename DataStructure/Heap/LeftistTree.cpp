/**
 * @brief 左偏树
 * 是一种可并堆
 */

#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;

struct node {
    int val, idx, lc, rc, dist;  // val : 权值 ; idx : 排名
    bool operator < (const node & a) const {
        return val == a.val ? idx < a.idx : val < a.val;
    }
} v[maxn];

int p[maxn];

int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (v[y] < v[x]) swap(x, y);
    v[x].rc = merge(v[x].rc, y);
    if (v[v[x].lc].dist < v[v[x].rc].dist) swap(v[x].lc, v[x].rc);
    // if (rand() & 1) swap(v[x].lc, v[x].rc);  // 随机化合并
    v[x].dist = v[v[x].rc].dist + 1;
    return x;
}


// 删除根
void pop(int x) {
    x = find(x);
    p[v[x].lc] = p[v[x].rc] = p[x] = merge(v[x].lc, v[x].rc);
    v[x].lc = v[x].rc = v[x].dist = 0;
}

void test(int n) {
    for (int i = 1; i <= n; i++) {
        cin >> v[i].val;
        v[i].lc = v[i].rc = v[i].dist = 0;
    }
    int x, y;
    x = find(x), y = find(y);
    p[x] = p[y] = merge(x, y);  // 合并
}