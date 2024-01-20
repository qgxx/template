/**
 * @brief 字符串hash
 * 
 */

# include <iostream>

using namespace std;

typedef unsigned long long ull;

const int maxn = 1e6 + 10, P = 131; // 或者13331

// s = "?" + s
ull Hash(string s) {
    int n = s.length();
    ull f = 0;
    for (int i = 1; i < n; i++)  f = f * P + ull(s[i]);
    return f;
}


ull p[maxn], f[maxn];

void hash(string s) {
    int n = s.length();
    p[0] = 1, f[0] = 0;
    for (int i = 1; i < n; i++) {
        f[i] = f[i - 1] * P + ull(s[i]);
        p[i] = p[i - 1] * P; 
    }
}
// H(S + c) = (H(S) * P + value(c)) mod M
// H(S + T) = (H(S) * P^length(T) + H(T)) mod M
// H(T) = (H(S + T) - H(S) * P^lenght(T)) mod M