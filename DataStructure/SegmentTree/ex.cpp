// 动态开点

const int maxn = 1e6 + 10;

struct node {
    int val, ls, rs;
} tr[maxn * 40];
int cnt = 1;
// eg: tree[p].ls = ++cnt;



// 标记永久化
// 不再另外下传 mark，在询问时把 mark 的影响加到答案上

using ll = long long;

const int maxn = 1e5 + 10;

struct node {
    ll val, mark;
    int ls, rs;
} tree[maxn * 40];
int n, cnt = 1; ll a[maxn];

void build(int p = 1, int cl = 1, int cr = n) {
    if (cl == cr) return void(tree[p].val = a[cl]);
    int mid = cl + cr >> 1;
    tree[p].ls = ++cnt; tree[p].rs = ++cnt;
    build(tree[p].ls, cl, mid); build(tree[p].rs, mid + 1, cr);
    tree[p].val = tree[tree[p].ls].val + tree[tree[p].rs].val;
}

void update(int l, int r, ll d, int p = 1, int cl = 1, int cr = n) {
    if (l <= cl && cr <= r) {
        tree[p].val += (cr - cl + 1) * d;
        tree[p].mark += d;
        return ;
    }
    int mid = cl + cr >> 1;
    if (l <= mid) update(l, r, d, tree[p].ls, cl, mid);
    if (r >= mid + 1) update(l, r, d, tree[p].rs, mid + 1, cr);
    tree[p].val = tree[tree[p].ls].val + tree[tree[p].rs].val + tree[p].mark * (cr - cl + 1);
}

ll query(int l, int r, int p = 1, ll mk = 0, int cl = 1, int cr = n) {
    if (l <= cl && cr <= r) return tree[p].val + mk * (cr - cl + 1);
    ll ans = 0;
    mk += tree[p].mark;
    int mid = cl + cr >> 1;
    if (l <= mid) ans += query(l, r, tree[p].ls, mk, cl, mid);
    if (r >= mid + 1) ans += query(l, r, tree[p].rs, mk, mid + 1, cr);
    return ans;
}