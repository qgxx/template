// 可持久化线段树
// 保存多个版本的线段树，但只能修改最近的版本
// 支持区间修改（加）


using ll = long long;

const int maxn = 1e5 + 10;

struct node {
    ll val, mark;
    int ls, rs;
} tree[maxn * 40];
int a[maxn], roots[maxn], n, cnt = 0;

int build(int cl = 1, int cr = n) {
    int p = ++cnt;
    tree[p].mark = 0;
    if (cl == cr) {
        tree[p].val = a[cl];
        return p;
    }
    int mid = cl + cr >> 1;
    tree[p].ls = build(cl, mid); tree[p].rs = build(mid + 1, cr);
    tree[p].val = tree[tree[p].ls].val + tree[tree[p].rs].val;
    return p;
}

int update(int q, int l, int r, ll d, int cl = 1, int cr = n) {
    int p = ++cnt;
    tree[p] = tree[q];
    if (l <= cl && cr <= r) {
        tree[p].val += (cr - cl + 1) * d;
        tree[p].mark += d;
        return p;
    }
    int mid = cl + cr >> 1;
    if (l <= mid) tree[p].ls = update(tree[q].ls, l, r, d, cl, mid);
    if (r >= mid + 1) tree[p].rs = update(tree[q].rs, l, r, d, mid + 1, cr);
    tree[p].val = tree[tree[p].ls].val + tree[tree[p].rs].val + tree[p].mark * (cr - cl + 1);
    return p;
}

ll query(int p, int l, int r, ll mk = 0, int cl = 1, int cr = n) {
    if (l <= cl && cr <= r) return tree[p].val + mk * (cr - cl + 1);
    ll ans = 0;
    mk += tree[p].mark;
    int mid = cl + cr >> 1;
    if (l <= mid) ans += query(tree[p].ls, l, r, mk, cl, mid);
    if (r >= mid + 1) ans += query(tree[p].rs, l, r, mk, mid + 1, cr);
    return ans;
}

// roots[0] = build();