// 数论分块，快速计算一些含有除法向下取整的和式
// 对于常数 n，使得 (n / i){向下取整} == (n / j){向下取整} 成立的最大的满足 i <= j <= n
// 的 j = (n / (n / i){向下取整}){向下取整}
#include <algorithm>

// 以 Sum(num / i)  [st <= i <= ed] {向下取整} 为例 
int block(int st, int ed, int num) {
    int r = 0;
    int ans = 0;
    ed = std::min(ed, num);
    for (int l = st; l <= ed; l = r + 1) {
        r = std::min(ed, num / (num / l));
        ans += (r - l + 1) * (num / l);   // 视情况而定
    }
    return ans;
}

// a / bc = a / b / c {向下取整}


// 常见整数公式与整数分块

// a mod b = a - (a / b){向下取整} * b
// a / b {向上取整} = (a - 1) / b {向下取整} + 1