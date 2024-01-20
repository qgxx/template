/**
 * @brief KMP
 * t: 文本串 ; s: 模式串
 * 找到模式串 s 在文本串 t 中的所有出现
 * 
 * next_p[] : T 中以 i 结尾的非前缀子串与 T 的前缀的最大匹配长度
 * f[] : S 中以 i 结尾的子串与 T 的前缀匹配的最大长度
 */


#include <iostream>

using namespace std;

const int maxn = 1e6 + 10;

int next_p[maxn], f[maxn];

// s: 模式串
// s = "?" + s
void cul_next(string s) {
    int n = s.length();
    next_p[1] = 0;
    for (int i = 2, j = 0; i < n; i++) {
        while (j && (s[i] != s[j + 1])) j = next_p[j];
        if (s[i] == s[j + 1]) j++;
        next_p[i] = j;
    }
}

// t: 文本串 ; s: 模式串
// s = "?" + s ; t = "?" + t
bool cul_f(string t, string s) {
    int n = t.length(), m = s.length() - 1;
    for (int i = 1, j = 0; i < n; i++) {
        while (j && (j == m || t[i] != s[j + 1])) j = next_p[j];
        if (t[i] == s[j + 1]) j++;
        f[i] = j;
        if (f[i] == m) return true;
    }
    return false;
}