// 主席树: 区间 [l, r] 内的第 k 小值


#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;

struct node {
    int sum, ls, rs;
} tree[maxn * 40];
int roots[maxn], cnt = 0;
int a[maxn], ind[maxn], len;

int get_id(const int &val) { return lower_bound(ind + 1, ind + len + 1, val) - ind; }

int build(int l, int r) {
    int p = ++cnt;
    if (l == r) return p;
    int mid = l + r >> 1;
    tree[p].ls = build(l, mid); tree[p].rs = build(mid + 1, r);
    return p;
}

int update(int k, int l, int r, int q) {
    int p = ++cnt;
    tree[p] = tree[q]; tree[p].sum = tree[q].sum + 1;
    if (l == r) return p;
    int mid = l + r >> 1;
    if (k <= mid) tree[p].ls = update(k, l, mid, tree[p].ls);
    else tree[p].rs = update(k, mid + 1, r, tree[p].rs);
    return p;
}

int query(int p, int q, int l, int r, int k) {
    int mid = l + r >> 1, x = tree[tree[q].ls].sum - tree[tree[p].ls].sum;
    if (l == r) return l;
    if (k <= x) return query(tree[p].ls, tree[q].ls, l, mid, k);
    else return query(tree[p].rs, tree[q].rs, mid + 1, r, k);
}

/*
for (int i = 1; i <= n; ++i) cin >> a[i], ind[i] = a[i];
sort(ind + 1, ind + n + 1);
len = unique(ind + 1, ind + n + 1) - ind - 1;
roots[0] = build(1, len);
for (int i = 1; i <= n; ++i) roots[i] = update(get_id(a[i]), 1, len, roots[i - 1]);

ind[query(roots[l - 1], roots[r], 1, len, k)]
*/