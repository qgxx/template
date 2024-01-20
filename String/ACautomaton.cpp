/**
 * @brief AC自动机
 * 在Trie图上进行类似于KMP的操作
 * 找到多个模式串 si 在文本串 t 中的所有出现
 */


#include <iostream>
#include <queue>

using namespace std;

const int maxn = 1e6 + 10, maxc = 65;

int trie[maxn][maxc], tot = 0;
int fail[maxn];
int cnt[maxn];

int to_c(char c);

// 构建trie-tree
void insert(const string &s) {
    int u = 0;
    for (char c : s) {
        int x = to_c(c);
        if (trie[u][x] == 0) trie[u][x] = ++tot;
        u = trie[u][x];
    }
    ++cnt[u];
}

// 构建trie图
void build() {
    queue<int> q;
    for (int i = 0; i < maxc; ++i) if (trie[0][i]) q.push(trie[0][i]);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < maxc; ++i) {
            if (trie[u][i]) {
                fail[trie[u][i]] = trie[fail[u]][i];
                q.push(trie[u][i]);
            }
            else trie[u][i] = trie[fail[u]][i];
        }
    }
}

// 以多个不同的模式串出现在文本串中为例
int query(const string &t) {
    int u = 0, ans = 0;
    for (char c : t) {
        int x = to_c(c);
        u = trie[u][x];
        for (int j = u; j; j = fail[j]) ans += cnt[j], cnt[j] = 0;
    }
    return ans;
}