// 吉司机线段树
// 维护区间修改min(a[i], t)，区间修改max(a[i], p)，区间加并求区间和、区间极值


#include <algorithm>

using namespace std;
using ll = long long;

const int maxn = 5e5 + 5, inf = 0x7fffffff;

int n, a[maxn];
struct Node {
	int mx, mx2, mn, mn2, mx_cnt, mn_cnt, mx_tag, mn_tag, add_tag;
	ll sum;
} t[maxn << 2];

void pushup(int u) {
	const int lu = u << 1, ru = u << 1 | 1;
	t[u].sum = t[lu].sum + t[ru].sum;
	if (t[lu].mx == t[ru].mx) {
		t[u].mx = t[lu].mx, t[u].mx_cnt = t[lu].mx_cnt + t[ru].mx_cnt;
		t[u].mx2 = max(t[lu].mx2, t[ru].mx2);
	} else if (t[lu].mx > t[ru].mx) {
		t[u].mx = t[lu].mx, t[u].mx_cnt = t[lu].mx_cnt;
		t[u].mx2 = max(t[lu].mx2, t[ru].mx);
	} else {
		t[u].mx = t[ru].mx, t[u].mx_cnt = t[ru].mx_cnt;
		t[u].mx2 = max(t[lu].mx, t[ru].mx2);
	}
	if (t[lu].mn == t[ru].mn) {
		t[u].mn = t[lu].mn, t[u].mn_cnt = t[lu].mn_cnt + t[ru].mn_cnt;
		t[u].mn2 = min(t[lu].mn2, t[ru].mn2);
	} else if (t[lu].mn < t[ru].mn) {
		t[u].mn = t[lu].mn, t[u].mn_cnt = t[lu].mn_cnt;
		t[u].mn2 = min(t[lu].mn2, t[ru].mn);
	} else {
		t[u].mn = t[ru].mn, t[u].mn_cnt = t[ru].mn_cnt;
		t[u].mn2 = min(t[lu].mn, t[ru].mn2);
	}
}

void push_add(int u, int l, int r, int v) {
	t[u].sum += (r - l + 1ll) * v;
	t[u].mx += v, t[u].mn += v;
	if (t[u].mx2 != -inf) t[u].mx2 += v;
	if (t[u].mn2 != inf) t[u].mn2 += v;
	if (t[u].mx_tag != -inf) t[u].mx_tag += v;
	if (t[u].mn_tag != inf) t[u].mn_tag += v;
	t[u].add_tag += v;
}

void push_min(int u, int tg) {
	if (t[u].mx <= tg) return;
	t[u].sum += (tg * 1ll - t[u].mx) * t[u].mx_cnt;
	if (t[u].mn2 == t[u].mx) t[u].mn2 = tg; 
	if (t[u].mn == t[u].mx) t[u].mn = tg;    
	if (t[u].mx_tag > tg) t[u].mx_tag = tg;        
	t[u].mx = tg, t[u].mn_tag = tg;
}

void push_max(int u, int tg) {
	if (t[u].mn > tg) return;
	t[u].sum += (tg * 1ll - t[u].mn) * t[u].mn_cnt;
	if (t[u].mx2 == t[u].mn) t[u].mx2 = tg;
	if (t[u].mx == t[u].mn) t[u].mx = tg;
	if (t[u].mn_tag < tg) t[u].mn_tag = tg;
	t[u].mn = tg, t[u].mx_tag = tg;
}

void pushdown(int u, int l, int r) {
	const int lu = u << 1, ru = u << 1 | 1, mid = (l + r) >> 1;
	if (t[u].add_tag)
		push_add(lu, l, mid, t[u].add_tag), push_add(ru, mid + 1, r, t[u].add_tag);
	if (t[u].mx_tag != -inf) push_max(lu, t[u].mx_tag), push_max(ru, t[u].mx_tag);
	if (t[u].mn_tag != inf) push_min(lu, t[u].mn_tag), push_min(ru, t[u].mn_tag);
	t[u].add_tag = 0, t[u].mx_tag = -inf, t[u].mn_tag = inf;
}

void build(int u = 1, int l = 1, int r = n) {
	t[u].mn_tag = inf, t[u].mx_tag = -inf;  
	if (l == r) {
		t[u].sum = t[u].mx = t[u].mn = a[l];
		t[u].mx2 = -inf, t[u].mn2 = inf;
		t[u].mx_cnt = t[u].mn_cnt = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void update_add(int l, int r, int v, int u = 1, int cl = 1, int cr = n) {
	if (r < cl || cr < l) return;
	if (l <= cl && cr <= r) return push_add(u, cl, cr, v); 
	int mid = (cl + cr) >> 1;
	pushdown(u, cl, cr);
	update_add(l, r, v, u << 1, cl, mid), update_add(l, r, v, u << 1 | 1, mid + 1, cr);
	pushup(u);
}

void update_min(int l, int r, int v, int u = 1, int cl = 1, int cr = n) {
	if (r < cl || cr < l || t[u].mx <= v) return;
	if (l <= cl && cr <= r && t[u].mx2 < v) return push_min(u, v); 
	int mid = (cl + cr) >> 1;
	pushdown(u, cl, cr);
	update_min(l, r, v, u << 1, cl, mid), update_min(l, r, v, u << 1 | 1, mid + 1, cr);
	pushup(u);
}

void update_max(int l, int r, int v, int u = 1, int cl = 1, int cr = n) {
	if (r < cl || cr < l || t[u].mn >= v) return;
	if (l <= cl && cr <= r && t[u].mn2 > v) return push_max(u, v);
	int mid = (cl + cr) >> 1;
	pushdown(u, cl, cr);
	update_max(l, r, v, u << 1, cl, mid), update_max(l, r, v, u << 1 | 1, mid + 1, cr);
	pushup(u);
}

ll query_sum(int l, int r, int u = 1, int cl = 1, int cr = n) {
	if (r < cl || cr < l) return 0;
	if (l <= cl && cr <= r) return t[u].sum;
	int mid = (cl + cr) >> 1;
	pushdown(u, cl, cr);
	return query_sum(l, r, u << 1, cl, mid) + query_sum(l, r, u << 1 | 1, mid + 1, cr);
}

ll query_max(int l, int r, int u = 1, int cl = 1, int cr = n) {
	if (r < cl || cr < l) return -inf;
	if (l <= cl && cr <= r) return t[u].mx;
	int mid = (cl + cr) >> 1;
	pushdown(u, cl, cr);
	return max(query_max(l, r, u << 1, cl, mid), query_max(l, r, u << 1 | 1, mid + 1, cr));
}

ll query_min(int l, int r, int u = 1, int cl = 1, int cr = n) {
	if (r < cl || cr < l) return inf;
	if (l <= cl && cr <= r) return t[u].mn;
	int mid = (cl + cr) >> 1;
	pushdown(u, cl, cr);
	return min(query_min(l, r, u << 1, cl, mid), query_min(l, r, u << 1 | 1, mid + 1, cr));
}