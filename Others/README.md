# 倍数遍历
在中间值被外层循环的倍数包含在内即包含所有情况时，可以使用倍数遍历来把时间复杂度把O(N^2)降低到O(NlogN)
```c++
for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i) 
                // do...
```


# 倍增法binary-lifting
通过预处理2^k的值来表示中间值
1、2、4、8、16...
``` c++
bz[maxn][20];
bz[i][j] = f(bz[i][j - 1], bz[i + (1 << (j - 1))][j - 1])
```


# 二分
## 可以手动设置迭代次数
eg: L = 0, R = 1e6
``` c++
long long l = 0, r = 1e6;
        for (int i = 1; i <= 30; i++) {
            long long mid = (l + r) / 2;
```


# 差分
A[] : 原数组 ; B[] : 差分序列 

Ai = $\sum_1^i$Bi  
因为差分序列的前缀和序列是原序列，把原序列`A[l, r]`区间加上`d`，
其差分序列化为：`Bl` + `d`, `Br+1` - `d`，其它位置不变，把区间操作转化为差分序列上的单点操作。
eg:
``` c++
int n;
int l, r, d;
cin >> l >> r >> d;
a[l] += k, a[r + 1] -= k;

for (int i = 1; i <= n; i++) a[i] += a[i - 1];
```
## 差分数组应用：
* 用来把数组划分为几个段落，通过给这个段落加上一个随机hash，然后前缀和得到连续段相同的分组数组。然后将其保存在map中即可。  
eg：
``` c++
mt19937_64 rnd(random_device{}());
uniform_int_distribution<ull> dist(0, ULLONG_MAX);
for (int i = 0; i < m; ++i) {
        ull h = dist(rnd);
        int l, r;
        std::cin >> l >> r;
        d[l] += h;
        if (r + 1 <= n) d[r + 1] -= h;
}
map<ull, int> mp;
for (int i = 1; i <= n; ++i) {
        d[i] += d[i - 1];
        ++mp[d[i]];
}
```

# 最小后缀和
min_suf(k) = min($\sum_{i=j}^{k}$a[i]), (1<=j<=k)  
e.g: 如果要想任意长度 >= 2 的区间和 >= 0，只需要在枚举最后一位i-th数 x 时满足`min_suf(i-1) >= -x` (假设前i-1位已经合法)
 

# 滚动数组
在进行DP的转移时，如果每次转移的取值范围都不超过 M，那只需要一个大小为M的容器即可，因为每次转移时都只需要上一个长度为M的区间的信息。