# 二分
* `binary_search(a.begin(), a.end(), x)`;  // 查找a中是否存在 x, return bool;
* `lower_bound(a.begin(), a.end(), x)`;    // 查找a中 >= x的第一个数的地址, return type*
* `upper_bound(a.begin(), a.end(), x)`;    // 查找a中 > x的一个数的地址 return type*

# 大数
有时可以使用`__int128_t`来替代大数模拟，不过需要重构输入和输出。
```c++
#include <iostream>
#include <iomanip>

using i64 = long long;
using i128 = __int128_t;

ostream &operator<<(ostream &os, const i128 &v) {
    if (v <= 1000000000000000000) {
        return os << i64(v);
    }
    return os << i64(v / 1000000000000000000) << setw(18) << setfill('0') << i64(v % 1000000000000000000);
}
```

# 容器
## map
`.count(key)`： 判断这个key是否存在
``` c++
mpa<int, int> st;
if (st.count(1)) // do...
```
### multimap
### unordered_map | unordered_multimap

## stack

## queue
### prioript_queue
``` c++
// 小根堆
std::priority_queue<node, std::vector<node>, std::greater<int>> q;

// 大根堆
std::priority_queue<node, std::vector<node>, std::less<int>> q;
```

### deque

## string
* 切片： `.substr(起始位置, 长度)`  
* find(ch, start = x) | find(ch): 从指定位置 | 头开始寻找ch在字符串中第一次出现的位置，不存在时返回 s.npos(s是一个string对象)
* rfind(): 从末尾开始寻找第一次出现的位置，不存在时返回 -1
* c_str(): string转char*
``` c++
// 初始化
string s;
string s(n, '0');  // 长度为n，每个字符为'0'的字符串
string s[n];       // 大小为n的string数组
```

## list

## vector
当有多个参数时可以用`emplace_back()`代替`push_back()`，数据类型需要有构造函数
``` c++
// 初始化
vector<int> b(n, 0);
vector<vector<int>> a(n, vector<int>(m)) 
vector<int> c[n];  // 大小为n的vector<int>数组
```
``` c++
for (auto [x, y] : a)
```

## array
``` c++
template <class Ty, std::size_t N>
class array;

array<int, 3> a[n];
```

## set
### multiset
保证序列有序，并允许有重复，插入和删除都是logN

### unordered_set | unordered_multiset

## bitset
bitset 就是通过固定的优化，使得一个字节的八个比特能分别储存 8 位的 0/1。（bool类型占用了一个byte）  
对于一个 4 字节的 int 变量，在只存 0/1 的意义下，bitset 占用空间只是其$\frac{1}{32}$，计算一些信息时，所需时间也是其 $\frac 1{32}$。  
所以可以通过使用 bitset 来优化程序的运行效率。一般bitset的时间复杂度：$O(\frac{n}{w}),w=32$。  

eg: 如果在一个图中寻找两个点相连边的数量，暴力的写法是$O(n^2)$的；如果使用bool数组的下标存下每个点的交点，此时只需要遍历其中一个点的相邻点然后看另一个点的bool数组对应下标是0还是1，此时是$O(n)$的；如果使用bitset来代替bool数组，此时是$O(\frac{n}{w})$的。
``` c++
bitset<maxn> adj[maxn];
for (int i = 1; i <= n; ++i) adj[i].reset();
while (m--) {
    int u, v; cin >> u >> v;
    adj[u].set(v); adj[v].set(u);
}
for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) {
    int a = (adj[i] & adj[j]).count();
}
// 此时遍历找到所有任意两个点之间相连边的数量的时间复杂度就是O(n^3/w)
```

``` c++
const int maxn = 1e3 + 10;
bitset<maxn> bt;
bt.set(1), bt.set(2);
bt.to_ulong() = ...110 = 6;
bt.test(1) = bt.test(2) = true;
bt.flip(2), bt.flip(0);
bt.to_ulang() = ...011 = 3;
bt.test(2) = false;
```

# math相关
* `__gcd(x, y)`：最大公约数
* `lcm(x, y)`：最小公倍数，在`#include <numeric>`中，最低支持C++17
* `__lg(x)`：返回是2的几次方，向下取整
* `powl()、sqrtl()`：返回`long double`，精度更高

# I/O
* 格式化输出long double：`%Lf`


# algorithm
count()：统计容器中指定数出现的数量  eg : `count(s.begin(), s.end(), s[0])`
max_element(): 容器最大元素下标 eg : `*max_element(a.begin(), a,end())`


# randow
eg: 
``` c++
mt19937_64 rnd(random_device{}());
uniform_int_distribution<ull> dist(0, ULLONG_MAX);
ull h = dist(rnd);
```


# ext


# function
`__builtin_popcount(int)`: 统计二进制数中 1 的个数

`min({a, b, c})`：求多个数中的最小数

`greater<>()`和`less<>()`：  
建堆时，`greater<>()`是小根堆，`less<>()`是大根堆； eg: pirority_queue    
排序时，`greater<>()`是降序，`less<>()`是升序。

`atoi`：char* 转 int


# 常数优化
## 循环展开
循环展开是一种程序变换，通过增加每次迭代计算元素的数量，减少循环迭代次数。  
可以把原本时间复杂度为$O(n)$的程序降低。  
``` c++
//非循环展开
for (int i = 1; i <= n; i++)
    sum += a[i];

//2*1循环展开
int i;
for(i = 1; i <= n - 1; i += 2) {
    sum += a[i];
    sum += a[i + 1];
}
for(; i <= n; i++)
	sum += a[i];

//3*1循环展开
int i;
for(i = 1; i <= n - 2; i += 3) {
    sum += a[i];
    sum += a[i + 1];
    sum += a[i + 2];
}
for(; i <= n; i++)
	sum += a[i];


//2*2循环展开
int i, sum0, sum1, sum;
for(i = 1; i <= n - 1; i += 2) {
    sum0 = sum0 + a[i];
    sum1 = sum1 + a[i + 1];
}
for(i; i <= n; i++)
    sum0 += a[i];
sum = sum0 + sum1;
```
代码相邻行的数据相关越小流水线越好流，效率也就更高，普通的2×1循环展开中，数据相关较大，sum += a[i]得到的sum值还要参与sum += a[i + 1]的运算，导致流水线的效率降低，改用两个变量，消除了数据相关，所以代码执行的效率变高了。
