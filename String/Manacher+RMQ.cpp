// 下面的下标表示字符串中每个字符左边的位置，从0开始（回文字符串长度默认为偶数） eg：(0)s[0](1)s[1]...
// 结合Manacher和ST-table，快速找到距离 i 最近的点 j，使（i，j）之间的字符串使回文字符串

#include <iostream>

using namespace std;

const int maxn = 1e5 + 10;

int d[maxn], st[maxn][20];

void Manacher(const string &s) {
    int n = s.length();
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}

void work() {
    string s; int n = s.length();
    Manacher(s);   // 首先使用Manacher算法求得所有的偶回文字符串

    // st-table其实是用来表示每次可以移动多少 (1 << k) 步
    for (int i = 0; i < n; ++i) st[i][0] = i - d[i];
    for (int k = 1; k < 20; ++k) for (int i = 0; i + (1 << k) <= n; ++i) 
        st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]); 

    // find
    for (int i = 0; i < n; ++i) {
        int j = i + 1;
        for (int k = 19; k >= 0; --k) 
            if (j + (1 << k) <= n && st[j][k] > i) j += (1 << k);  // 寻找的 j 其实是回文中心轴
        if (j * 2 - i <= n) ; // 根据偶数回文的性质得到 j + d(d = j - i) 右边界
    }
}

// st-table：
// 如果st[i][k - 1] < st[i + (1 << (k - 1))][k - 1]，说明右边一定存在一个中心轴的最大回文包含它,
// 此时st[i][k] < i, i 就不能移动 (1 << k);
// 否则说明这段区间没有可以和 i 组成回文的子字符串，可以直接移动 (1 << k) 