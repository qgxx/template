/**
 * @brief Trie字典树
 * 
 */


#include <iostream>

using namespace std;

const int maxn = 1e6 + 10, maxc = 65;

int trie[maxn][maxc], idx;
int cnt[maxn], s_end[maxn];   // 用于统计前缀和以 p 为结尾的 s 是否存在

void init() {
    for (int i = 0; i <= idx; i++) {
        cnt[i] = s_end[i] = 0;
        for (int j = 0; j <= maxc; j++) trie[i][j] = 0;
    }
    idx = 1;
}

int to_c(char c) {
    int x;
    if (c >= 'A' && c <= 'Z') x = (c - 'A');
    else if (c >= 'a' && c <= 'z') x = (c - 'a' + 26);
    else x = (c - '0' + 52);
    return x;
}

void insert(const string &s) {
    int p = 1;
    for (char c : s) {
        int x = to_c(c);
        if (trie[p][x] == 0) trie[p][x] = ++idx;
        p = trie[p][x];
        // ++cnt[p];
    }
    s_end[p] = 1;
}

int search(const string &s) {
    int p = 1;
    for (char c : s) {
        int x = to_c(c);
        p = trie[p][x];
        if (p == 0) return 0;
    }
    return cnt[p]; 
    // return s_end[p];
}