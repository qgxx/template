/**
 * @brief 线段树
 * 区间加、区间乘、查询区间和
 */


using ll = long long;

const int maxn = 1e5 + 10, mod;

ll a[maxn], n;
ll sum[maxn * 40], mul[maxn * 40], mark[maxn * 40];

void build(int p = 1, int cl = 1, int cr = n) {
    mul[p] = 1;
    if (cl == cr) return void(sum[p] = a[cl]);
    int mid = cl + cr >> 1;
    build(p << 1, cl, mid); build(p << 1 | 1, mid + 1, cr);
    sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % mod;
}

void push_down(int p, int cl, int cr) {
    int l = p << 1, r = p << 1 | 1, mid = cl + cr >> 1;
    if (mul[p] != 1) {
        mul[l] *= mul[p]; mul[l] %= mod; mul[r] *= mul[p]; mul[r] %= mod;
        mark[l] *= mul[p]; mark[l] %= mod; mark[r] *= mul[p]; mark[r] %= mod;
        sum[l] *= mul[p]; sum[l] %= mod; sum[r] *= mul[p]; sum[r] %= mod;
        mul[p] = 1;
    }
    if (mark[p] != 0) {
        sum[l] += mark[p] * (mid - cl + 1); sum[l] %= mod; 
        sum[r] += mark[p] * (cr - mid); sum[r] %= mod;
        mark[l] += mark[p]; mark[l] %= mod; mark[r] += mark[p]; mark[r] %= mod;
        mark[p] = 0;
    }
}

// 区间 + d
void update_add(int l, int r, int d, int p = 1, int cl = 1, int cr = n) {
    if (l <= cl && cr <= r) {
        sum[p] += d * (cr - cl + 1); sum[p] %= mod;
        mark[p] += d; mark[p] %= mod;
        return ;
    } 
    push_down(p, cl, cr);
    int mid = cl + cr >> 1;
    if (mid >= l) update_add(l, r, d, p << 1, cl, mid);
    if (mid < r) update_add(l, r, d, p << 1 | 1, mid + 1, cr);
    sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % mod;
}


// 区间 * d
void update_mul(int l, int r, int d, int p = 1, int cl = 1, int cr = n) {
    if (l <= cl && cr <= r) {
        mul[p] *= d; mul[p] %= mod;
        mark[p] *= d; mark[p] %= mod;
        sum[p] *= d; sum[p] %= mod;
        return ;
    }
    push_down(p, cl, cr);
    int mid = cl + cr >> 1;
    if (mid >= l) update_mul(l, r, d, p << 1, cl, mid);
    if (mid < r) update_mul(l, r, d, p << 1 | 1, mid + 1, cr);
    sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % mod;
}

// 查询区间和
ll query(int l, int r, int p = 1, int cl = 1, int cr = n) {
    if (l <= cl && cr <= r) return sum[p];
    push_down(p, cl, cr); 
    int mid = cl + cr >> 1;
    ll ans = 0;
    if (mid >= l) ans += query(l, r, p << 1, cl, mid), ans %= mod;
    if (mid < r) ans += query(l, r, p << 1 | 1, mid + 1, cr), ans %= mod;
    return ans % mod;
}