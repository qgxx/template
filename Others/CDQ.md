# CDQ

## 解决和点对有关的问题
常用来解决此类问题：给定一个长度为n的序列，统计一些具有特性的点对(i, j)`{注意这里说的是点对，不是坐标}`的数量或者是
要找到一对点(i, j)使一些函数的值最大。  

**流程：**  
1. 找到这个序列的中点 *mid*
2. 将所有的点对分为三类：  
    a. $1\leqslant{i}\leqslant{mid}, 1\leqslant{j}\leqslant{mid}$的$(i, j)$点对；  
    b. ${mid+1}\leqslant{i}\leqslant{n}, {mid+1}\leqslant{j}\leqslant{n}$的$(i, j)$；  
    c. $1\leqslant{i}\leqslant{mid}, {mid+1}\leqslant{j}\leqslant{n}$的$(i, j)$。
3. 将(1, n)序列拆成两个序列$(1, mid)$和$(mid + 1, n)$。显然a、b两类分别在两个队列中，所以可以直接递归；问题在于c类，因为涉及两个子序列所以需要设计合适的算法。  

可以参考template\Math\Others\poset.md的偏序解决方法。