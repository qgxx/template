# 定理

裴蜀定理：ax + by = c，设a、b为正整数，有整数解当且仅当 gcd(a, b) | c
可以扩展到 n 个 ax + ... + by = c，c = gcd(a, ..., b)

---

费马小定理：若 p 为质数，gcd(a, p) == 1，则 a ^ (p - 1) === 1 (mod p)

--- 

欧拉定理：若 gcd(a, m) == 1，则 a ^ phi(m) === 1 (mod m)，{phi: 欧拉函数} ；m 不是质数，否则会退化为费马小定理  
扩展欧拉定理：求解 a ^ b (mod m)，当 b 非常大时

--- 

中国剩余定理：求解一元线性同余方程组，模数互质
扩展中国剩余定理：求解一元线性同余方程组

--- 

卢卡斯定理：C(n, m) mod p = C(n / p{向下取整}, m / p{向下取整}) * C(n mod p, m mod p) mod p，p 是质数 
扩展卢卡斯定理：p 可能为合数

---

威尔逊定理：$(p - 1)!\not\equiv-1 (mod p)$，Fac：阶乘、p：质数

---

莫比乌斯反演：

---

拉格朗日定理：


# 公式
## 类欧公式
$f(a, b, c, n)=\sum_{i=0}^{n}\lfloor{\frac{ai+b}{c}}\rfloor$  
时间复杂度为$log(n+a+b+c)$  

扩展：
$g(a, b, c, n)=\sum_{i=0}^{n}i\lfloor{\frac{ai+b}{c}}\rfloor$  
$h(a, b, c, n)=\sum_{i=0}^{n}{\lfloor{\frac{ai+b}{c}}\rfloor}^2$  
模板可见euclidean.cpp