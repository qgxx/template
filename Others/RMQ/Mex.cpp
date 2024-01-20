// 莫队求区间 mex
// 没有出现过的最小自然数

#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 2e5 + 10, maxsq = 1e5 + 10;

int a[maxn], n, m;
int cnt[maxn], ans[maxn], sz[maxsq], sq;
struct query {
    int l, r, id;
    bool operator < (const query & t) const {
        return l / sq == t.l / sq ? ((l / sq) & 1 ? r < t.r : r > t.r) : l < t.l;
    }
} q[maxn];

void add(int x) {
    if (cnt[x]++ == 0) sz[x / sq]++;
}  

void del(int x) {
    if (--cnt[x] == 0) sz[x / sq]--;
}

int get_mex() {
    for (int i = 1; i <= sq; i++) 
        if (sz[i - 1] != sq) 
            for (int j = sq * (i - 1); j < sq * i; j++)
                if (cnt[j] == 0) return j;
    return n;  // 最右端不被包含
}

void test() {
    for (int i = 1; i <= n; i++); // cin >> a[i];
    sq = n / std::sqrt(n);
    for (int i = 0; i < m; i++); // cin >> q[i].l >> q[i].r, q[i].id = i;
    sort(q, q + m);
    int l = 1, r = 0;
    for (int i = 0; i < m; i++) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        ans[q[i].id] = get_mex();
    }
    for (int i = 0; i < m; i++); // cout << ans[i] << '\n';
}