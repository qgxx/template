// 带修莫队 : 支持单点修改的莫队

#include <iostream>
#include <algorithm>
#include <cmath>

const int maxn = 1e6 + 10;

int a[maxn], n, m;
int sq, ans[maxn], ans_tmp, cnt[maxn];
struct query {
    int l, r, t, id;
    bool operator < (const query & x) const {
        return l / sq == x.l / sq ? (r / sq == x.r / sq ? t < x.t : r < x.r) : l < x.l; 
    }
} q[maxn];
struct modify {
    int p, col;
} mo[maxn];
int q_cnt, m_cnt, now_t;

void add(int x) {
	// do ... ans_tmp
}

void del(int x) {
	// do ... ans_tmp 
}

void Modify(int k, int ti) {
	if (mo[ti].p >= q[k].l && mo[ti].p <= q[k].r) del(a[mo[ti].p]), add(mo[ti].col);
	std::swap(a[mo[ti].p], mo[ti].col);
}

void test() {
	for (int i = 1; i <= n; i++); // do ... cin >> a[i];
	sq = std::pow(n, 0.66666);
	for (int i = 1; i <= m; i++) {
		std::string op;
		// 修改
		if (op == "M") {
			++q_cnt;
			// cin >> q[q_cnt].l >> q[q_cnt].r;
			// q[q_cnt].t = m_cnt, q[q_cnt].id = i;
		}
		// 查询
		else {
			++m_cnt;
			// cin >> mo[m_cnt].p >> mo[m_cnt].k;
		}
	}
	std::sort(q + 1, q + 1 + m);

	int l = 1, r = 0;
	for (int i = 1; i <= q_cnt; i++) {
		while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        while (now_t < q[i].t) Modify(i, ++now_t);
        while (now_t > q[i].t) Modify(i, now_t--);
        ans[q[i].id] = ans_tmp;
	}
}