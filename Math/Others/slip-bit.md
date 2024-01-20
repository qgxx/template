# 二进制拆位算贡献


## $\sum_{i=1}^n$$\sum_{j=1}^n$($a_i$$\bigoplus$$a_j$)
暴力写法显然是O($n^2$)  
将每个数拆位，令$bit_ik$表示$a_i$的二进制在第 k 位是多少。  
$a_i$ = $2^0$$\times$$bit_i0$ + $2^1$$\times$$bit_i1$ + ... + $2^m\times$$bit_im$  
$a_j$ = $2^0$$\times$$bit_j0$ + $2^1$$\times$$bit_j1$ + ... + $2^m\times$$bit_jm$  

$\sum_{i=1}^n$$\sum_{j=1}^n$($a_i$$\bigoplus$$a_j$) = $\sum_{i=1}^n$$\sum_{j=1}^n$$\sum_{k=0}^m$($2^k\times$[${bit_ik}\not ={bit_jk}$])  

若$bit_ik$ = 0， 那只需要统计在$1\leqslant{j}\leqslant{n}$ 中有多少个数的二进制的第 k 位是1，那在这一位上$a_i$会产生$2^k\times{cnt_k1}$；  
$bit_ik$ = 0同理。  

只需要预处理出f[m][2]即可，即第 k 位为 0 的个数和为 1 的个数。  
此时可以将时间复杂度降为O(mn)，m 为最大数的二进制的位数。

``` c++
int f[30][2], a[N];
for (int i = 1; i <= n; ++i) 
    for (int k = 0; k < 30; ++k)
        f[k][a[i] >> k & 1]++;

// 计算答案
long long ans = 0;
for (int i = 1; i <= n; ++i) 
    for (int k = 0; k < 30; ++k)
        ans += (1ll << k) * f[k][a[i] >> k & 1 ^ 1];
```

## $\sum_{i=1}^n$$\sum_{j=1}^n(a_i\bigoplus{a_j})^2$
$\sum_{i=1}^n$$\sum_{j=1}^n(a_i\bigoplus{a_j})^2$ = $\sum_{i=1}^n$$\sum_{j=1}^n$$\sum_{x=0}^m$$\sum_{y=0}^m$$(2^{x+y}\times$[${bit_ix}\not ={bit_jx}$]$\times$$[bit_iy \not ={bit_jy}]$)

``` c++
int f[35][35][2][2], a[N];
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= 30; j++) {
        for (int k = 0; k <= 30; k++) {
            f[j][k][a[i] >> j & 1][a[i] >> k & 1]++;
        }
    }
}
//计算答案
long long ans = 0;
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= 30; j++) {
        for (int k = 0; k <= 30; k++) {
            ans += (1ll << (j + k)) * f[j][k][(a[i] >> j & 1) ^ 1][(a[i] >> k & 1) ^ 1];
        }
    }
}
```


## $\sum_{1\leqslant{l1}\leqslant{r1}\lt{l2}\leqslant{r2}\lt{l3}\leqslant{r3}\leqslant{n}}$
### $\sum_{i=1}^n$$\sum_{j=1}^n$XOR(l, r)
XOR(l, r) = $a_l\bigoplus{a_{l+1}}\bigoplus ... \bigoplus{a_r}$  
令$s_i$ 表示前缀异或和，显然XOR(l, r) = $s_j\bigoplus{s_{i-1}}$；  
可以改写式子$\sum_{i=0}^n$$\sum_{j=i+1}^n$$(s_j\bigoplus{s_i})$。  

令pre[]表示前缀异或和，suf[]表示后缀异或和。  
$pre_i = pre_{i-1}+$$\sum_{j=0}^{i-1}$($s_i\bigoplus{s_j}$)；  
由分配律可得
$\sum_{1\leqslant{l1}\leqslant{r1}\lt{l2}\leqslant{r2}\lt{l3}\leqslant{r3}\leqslant{n}}$ = $\sum_{i=1}^n$$\sum_{j=i}^n$XOR(i, j)$\times{pre_{i-1}}\times{suf_{j+1}}$   
= $\sum_{i=1}^n$$pre_{i-1}\times$$\sum_{j=i}^n$XOR(i, j)$\times{suf_{j+1}}$    
= $\sum_{i=1}^n{pre_{i-1}}\times$$\sum_{j=i+1}^n$($s_i\bigoplus{s_j}$)$\times{suf_j}$ 

此时的s[]是后缀异或和，因为计算贡献时是倒着的，这样才能O(n)求解。  

``` c++
using ll = long long;

const int maxn = 2e5 + 10, p = 998244353;

ll a[maxn], s[maxn], pre[maxn], suf[maxn], f[35][2];

for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    s[i] = s[i - 1] ^ a[i]; 
}
for (int k = 0; k <= 30; ++k) f[k][0] = 1;
for (int i = 1; i <= n; ++i) {
    pre[i] = pre[i - 1];
    for (int k = 0; k <= 30; ++k) {
        (pre[i] += (1 << k) * f[k][s[i] >> k & 1 ^ 1] % p) %= p;
        f[k][s[i] >> k & 1]++;
    }
}

for (int k = 0; k <= 30; ++k) f[k][0] = 1, f[k][1] = 0;
for (int i = n; i >= 1; --i) s[i] = s[i + 1] ^ a[i];
for (int i = n; i >= 1; --i) {
    suf[i] = suf[i + 1];
    for (int k = 0; k <= 30; ++k) {
        (suf[i] += (1 << k) * f[k][s[i] >> k & 1 ^ 1] % p) %= p;
        f[k][s[i] >> k & 1]++;
    }
}

for (int k = 0; k <= 30; ++k) f[k][0] = f[k][1] = 0;
ll ans = 0;
for (int i = n; i >= 1; --i) {
    for (int k = 0; k <= 30; ++k) {
        (ans += pre[i - 1] * (1 << k) % p * f[k][s[i] >> k & 1 ^ 1] % p) %= p;
        (f[k][s[i] >> k & 1] += suf[i]) %= p;
    }
}
```