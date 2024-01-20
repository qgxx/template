/**
 * @brief ST表
 * O(NlogN)预处理RMQ，O(1)查询
 */

#include <iostream>
#include <algorithm>
#include <numeric>

const int maxn = 1e5 + 10, maxm = 21;

int st[maxn][maxm];

void init(int n) {
    for (int i = 1; i <= n; i++) std::cin >> st[i][0];
	for (int j = 1; j <= maxm; j++) 
		for (int i = 1; i + (1 << j) - 1 <= n; i++) 
			st[i][j] = std::max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int query(int l, int r) {
	int k = std::__lg(r - l + 1);
	return std::max(st[l][k], st[r - (1 << k) + 1][k]);
}