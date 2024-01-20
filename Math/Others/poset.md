# 偏序问题

## bitset
对于多维偏序问题，可以使用bitset构建K个0-1矩阵A，对于K-th$A_{ij}$表示i-th集合的k-th属性和j-th集合的k-th属性的大小关心。  
不妨在$a_{ik}>a_{jk}$时（有时是$a_{ik}\geqslant{a_{jk}}$），令对应的$A_{ij}=1$，反之为0。  
这时对K个0-1矩阵进行与运算得到一个新的矩阵S，$S=A_1\&A_2\&...\&A_k$。  
对于i-th行，只需要查看$S_{i1}-S_{in}$那个为1即可，为1则表示i的K个属性均大于这个集合K个属性，此时可以选择这个。  


``` c++
#include <vector>
#include <bitset>

using pii = pair<int, int>

const int N = 1e5 + 10, K = 6;

bitset<N> f[N];
int a[N][K];

// 这个是用来处理>=的偏序关系的
void wk(int n) {
    for (int i = 1; i <= n; ++i) {
        f[i].set();
        for (int j = 1; j < K; ++j) cin >> a[i][j];
    }
    for (int k = 1; k < K; ++k) {
        bitset<N> s; s.set();
        vector<pii> v;
        for (int i = 1; i <= n; ++i) v.emplace_back(a[i][k], i);
        sort(v.begin(), v.end());
        for (int i = n - 1; i >= 0; --i) {
            int t = i;
            while (t > 0 && v[i].first == v[t - 1].first) --t;
            for (int j = t; j <= i; ++j) f[v[j].second] &= s;
            for (int j = t; j <= i; ++j) s[v[i].second] = 0;
            i = t;
        }
    }
}
```


## K-D Tree
这是一个用于处理五维偏序的板子
``` c++
const int mod = 998244353;
const int N = 50010;
const int K = 5;
const double threshold = 0.75;

struct Point {
    int x[K];
    int v;  
};  // 5个属性和1个价值

struct Node {
    int l, r;
    int mn[K], mx[K];
    Point p;
    int v;
    int sz;
    #define ls tr[x].l
    #define rs tr[x].r
} tr[N];

int root, idx;
Point p[N];
int pool[N], top;
int now_k;
int f[N];

template<typename T> void change_min(T& x, T v) { if (v < x) x = v; }
template<typename T> void change_max(T& x, T v) { if (v > x) x = v; }
template<typename T> void add(T& x, T v) { x += v; if (x >= mod) x -= mod; }
int new_node() { return top ? pool[top--] : ++idx; }
bool cmp(Point a, Point b) { return a.x[now_k] < b.x[now_k]; }

void dfs(int x, int cnt) {
    if (!x) return;
    dfs(ls, cnt);
    pool[++top] = x;
    p[tr[ls].sz + cnt + 1] = tr[x].p;
    dfs(rs, tr[ls].sz + cnt + 1);
}

void pushup(int x) {
    auto &u = tr[x], &l = tr[ls], &r = tr[rs];
    u.sz = l.sz + r.sz + 1;
    u.v = max(u.p.v, max(l.v, r.v));
    for (int i = 0; i < K; i++) {
        u.mn[i] = u.mx[i] = u.p.x[i];
        if (ls) change_min(u.mn[i], l.mn[i]), change_max(u.mx[i], l.mx[i]);
        if (rs) change_min(u.mn[i], r.mn[i]), change_max(u.mx[i], r.mx[i]);
    }
}

int build(int l, int r, int k) {
    if (l > r) return 0;
    int mid = l + r >> 1;
    int x = new_node();
    now_k = k, nth_element(p + l, p + mid, p + r + 1, cmp);
    tr[x].p = p[mid];
    ls = build(l, mid - 1, (k + 1) % K);
    rs = build(mid + 1, r, (k + 1) % K);
    pushup(x);
    return x;
}

void rebuild(int& x, int k) {
    if (threshold * tr[x].sz <= (double) max(tr[ls].sz, tr[rs].sz)) 
        dfs(x, 0), x = build(1, top, k);
}

void insert(int& x, Point p, int k) {
    if (!x) {
        x = new_node();
        ls = rs = 0;
        tr[x].p = p;
        pushup(x);
        return;
    }
    if (p.x[k] <= tr[x].p.x[k]) insert(ls, p, (k + 1) % K);
    else insert(rs, p, (k + 1) % K);
    pushup(x), rebuild(x, k);
}

void query(int x, int a, int b, int c, int d, int e, int& f) {
    Node& u = tr[x];
    if (!x || f > u.v || a < u.mn[0] || b < u.mn[1] || c < u.mn[2] || d < u.mn[3] || e < u.mn[4]) 
        return;
    if (a >= u.mx[0] && b >= u.mx[1] && c >= u.mx[2] && d >= u.mx[3] && e >= u.mx[4]) 
        return f = max(f, u.v), void();
    if (a >= u.p.x[0] && b >= u.p.x[1] && c >= u.p.x[2] && d >= u.p.x[3] && e >= u.p.x[4]) f = max(f, u.p.v);
    query(ls, a, b, c, d, e, f), query(rs, a, b, c, d, e, f);
}

void wk() {
    root = idx = top = 0;

    int f = 0;
    int a, b, c, d, e;
    query(root, a, b, c, d, e, f);  // 查询最大的可以形成偏序的点
    insert(root, (Point){a, b, c, d, e, f}, 0);
}
```


## CDQ
可以用CDQ来解决一些偏序问题，高维偏序需要CDQ套CDQ，此时可以使用K-D Tree算法解决。  

eg：给定一个序列，每个点有三个属性$(a_i, b_i, c_i)$，询问对于点j有多少个点i满足$a_i\leqslant{a_j}且b_i\leqslant{b_j}且c_i\leqslant{c_j}且j\not ={i}$。  

首先将序列按照$a_i$进行排序，此时需要考虑$1\leqslant{i}\leqslant{mid}, {mid+1}\leqslant{j}\leqslant{n}$的$(i, j)$的情况如何解决。  
因为是按照$a_i$进行排序的，所以$a_i<a_j$是显然的，此时不需要考虑这个维度上的属性。  
现在还剩下两个属性$b_i和c_i$，此时可以分别把$1\leqslant{i}\leqslant{mid}, {mid+1}\leqslant{j}\leqslant{n}$两个子序列中序列按照$b_i$进行排序。然后对于每一个j，把$b_i<b_j$的序列进入到树状数组中，然后只需要从树状数组中找到$c_i<c_j$的序列就可以满足了。  

``` c++
const int N = 1e5 + 10, K = 2e5 + 10;

int n, k, m, t;
int res[N];
struct Element {
    int a, b, c;
    int cnt;  // 三个属性都相等的元素数量
    int res;  // 满足偏序的元素数量

    bool operator!=(Element o) {
        if (this->a != o.a || this->b != o.b || this->c != o.c) return true;
        return false;
    }
    Element() = default;
};
Element e[N], ue[N];

struct BinaryIndexTree {
    int node[K];

    int lowbit(int x) { return (x & -x); }
    void update(int x, int d) {
        while (x <= k) {
            node[x] += d;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int res = 0;
        while (x != 0) {
            res += node[x];
            x -= lowbit(x);
        }
        return res;
    }
} BIT;

void CDQ(int l, int r) {
    if (l == r) return ;
    int mid = (l + r) >> 1;
    CDQ(l, mid); CDQ(mid + 1, r);
    sort(ue + l, ue + mid + 1, [](Element x, Element y){
        return (x.b != y.b ? x.b < y.b : x.c < y.c);
    });
    sort(ue + mid + 1, ue + r + 1, [](Element x, Element y){
        return (x.b != y.b ? x.b < y.b : x.c < y.c);
    });
    int i = l, j = mid + 1;
    while (j <= r) {
        while (i <= mid && ue[i].b <= ue[j].b) {
            BIT.update(ue[i].c, ue[i].cnt);
            ++i;
        }
        ue[j].res += BIT.query(ue[j].c);
        ++j;
    }
    for (int k = l; k < i; ++k) BIT.update(ue[k].c, -ue[k].cnt);  // 消除此前加入的元素影响
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
 
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> e[i].a >> e[i].b >> e[i].c;
    sort(e + 1, e + n + 1, [](Element x, Element y){
        if (x.a != y.a) return x.a < y.a;
        if (x.b != y.b) return x.b < y.b;
        return x.c < y.c;
    });
    for (int i = 1; i <= n; ++i) {  // 离散化
        ++t;
        if (e[i] != e[i + 1]) {
            ++m;
            ue[m].a = e[i].a;
            ue[m].b = e[i].b;
            ue[m].c = e[i].c;
            ue[m].cnt = t;
            t = 0;
        }
    }
    CDQ(1, m);

    return 0;
}
```