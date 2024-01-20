// 块状数组 

#include <algorithm>
#include <cmath>

const int maxn = 1e5 + 10, maxsq = 1005; 
// maxsq = std::sqrt(maxn) 可以适当开大

int a[maxn], n;
struct block {
	int st, ed, sz; // 起点、终点、大小
} b[maxsq];
int for_b[maxn], mark[maxsq]; // 属于那个块、对整个块的标记

void split_block() {
	int sq = std::sqrt(n);
	for (int i = 1; i <= sq; i++) b[i].st = n / sq * (i - 1) + 1, b[i].ed = n / sq * i;
	b[sq].ed = n;
	for (int i = 1; i <= sq; i++) {
		for (int j = b[i].st; j <= b[i].ed; j++) for_b[j] = i;
		b[sq].sz = b[sq].ed - b[sq].st + 1;
	}
}

// 以为区间每个数增加 c 为例
void modify(int l, int r, int c) {
	if (for_b[l] == for_b[r]) {
		for (int i = l; i <= r; i++) a[i] += c;
		return;
	}
	for (int i = l; i <= b[for_b[l]].ed; i++) a[i] += c;
	for (int i = b[for_b[r]].st; i <= r; i++) a[i] += c;
	for (int i = for_b[l] + 1; i < for_b[r]; i++) mark[i] += c;
}

// 记得使用 mark
int query(int l, int r, int c) {
	int ans = 0;
	if (for_b[l] == for_b[r]) {
		for (int i = l; i <= r; i++) // do ...
		return ans;
	}
	for (int i = l; i <= b[for_b[l]].ed; i++) // do ... 
	for (int i = b[for_b[r]].st; i <= r; i++) // do ...
	for (int i = for_b[l] + 1; i < for_b[r]; i++) // do ...
	return ans;
}