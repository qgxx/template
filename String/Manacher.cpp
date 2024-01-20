/**
 * @brief Manacher处理回文子串
 * O(N)
 */

// d[]: 表示以 i 为中心的回文字符串的半径
// 长度为奇数的字符串中心就是字符的下标，为偶数的是字符下标左边的空隙（从0开始）

#include <iostream>
#include <vector>

using namespace std;

// 这个时间比较稳定
void Manacher(const string &s) {
    int n = s.length();
    vector<int> d1(n);   // 处理长度为奇数的回文子串，半径 = (字串长度 + 1) / 2
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    vector<int> d2(n);   // 处理长度为偶数的回文子串
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}


void Manacher(string s) {
    string t = "?";
    for (char c : s) t += c, t += "?";
    s = t;
    int n = s.length();
    vector<int> d1(n << 1);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
}