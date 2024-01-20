typedef long long ll;

const int maxn = 1e5 + 10, mod = 1e9 + 7;

int tree[maxn], p[maxn], fact[maxn];
// p[] : 输入的排列
// ai : p[i + 1 ~ n]小于 pi 的数的数量
// fact[] : 每个点的权重

int lowbit(int x) { return x & -x; }

void update(int x, ll d) {
    for (int i = x; i < maxn; i += lowbit(i)) tree[i] += d;
}

ll query(int x) {
    ll sum = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) sum += tree[i];
    return sum;
}

/**
 * @brief 康托展开：求一个排列在所有的 1 ~ n 排列间的字典序排名
 * 
 * @param n 
 * @return ll 
 */
int a[maxn];
ll Cantor(int n) {
    ll ans = 1;
    // fact[0] = 1; for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;  // 权重为阶乘时
    for (int i = n; i >= 1; i--) {
        a[i] = query(p[i]);
        update(p[i], 1);
    }
    for (int i = 1; i < n; i++) 
        ans = (ans + a[i] * fact[n - i]) % mod;
}


/**
 * @brief 逆康托展开：求指定排名的排列
 * 
 * @param x 
 */
int _a[maxn];  // 每个点分配的权值
void decantor(int x, int n) {
    x--;
    // 反向写法：
    for (int i = n; i >= 1; i--) {
        if (x < fact[i]) {
            _a[i] = x;
            break;
        }
        else {
            _a[i] = x % fact[i];
            x /= fact[i];
        }
    }

    // 正向写法：
    for (int i = 1; i <= n; i++) {
        _a[i] = x / fact[i];
        x %= fact[i];
    }


    // 处理剩下的...
}