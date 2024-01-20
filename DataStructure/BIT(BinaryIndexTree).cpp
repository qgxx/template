// 树状数组

const int maxn = 1e5 + 10;

int n;
int tree[maxn];

int lowbit(int x) { return x & -x; }

/**
 * @brief O(NlogN)
 * 
 * @param x 
 * @param d 
 */
void update(int x, int d) {
    while (x <= n) {
        tree[x] += d;
        x += lowbit(x);
    }
}

/**
 * @brief O(NlogN)
 * 
 * @param x 
 * @return int 
 */
int query(int x) {
    int sum = 0;
    while (x != 0) {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

void action(int a[]) {
    int x, y, d;                      // 左右边界，待加值
    update(x, d);                     // 单点修改
    query(y) - query(x - 1);          // 区间查询
}