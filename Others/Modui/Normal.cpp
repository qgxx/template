// 只有询问没有修改
// 将询问离线
// O(Nsqrt(M) + MlogM)

#include <algorithm>
#include <cmath>

const int maxn = 1e5 + 10;

int sq, n, m, a[maxn], ans[maxn];
struct query {
	int l, r, id;
	bool operator < (const query t) const { 
		return l / sq == t.l / sq ? ((l / sq) & 1 ? r < t.r : r > t.r) : l < t.l;
	}
} q[maxn];

void add(int x) {}

void del(int x) {}

void test() {
	for (int i = 1; i <= n; i++); // do ...
	sq = n / std::sqrt(n);
	for (int i = 0; i < m; i++);  // do ... cin >> q[i].l >> q[i].r, q[i].id = i;
	std::sort(q, q + m);
	
	int l = 1, r = 0;
	for (int i = 0; i < m; i++) {
		while (l > q[i].l) add(a[--l]);
		while (r < q[i].r) add(a[++r]);
		while (l < q[i].l) del(a[l++]);
		while (r > q[i].r) del(a[r--]);
		// do ... 
		// ans[q[i].id] = 
	}
	// do ... 输出答案
}