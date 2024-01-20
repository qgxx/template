/**
 * @brief 对顶堆 : 可以用来维护序列第 k 大的数
 * 
 */

#include <queue>
#include <vector>

void TopHeap() {
    std::priority_queue<int, std::vector<int>, std::less<int>> maxq;     // 大根堆: 维护比 k 大数小的其他值
    std::priority_queue<int, std::vector<int>, std::greater<int>> minq;  // 小根堆: 维护前 k 大的值(包括第 k 大的值)

    // eg: 维护中位数
    int x;
    if (maxq.empty() || x <= maxq.top()) maxq.push(x);
    else minq.push(x);

    if (maxq.size() > (maxq.size() + minq.size() + 1) / 2) {
        minq.push(maxq.top());
        maxq.pop();
    }
    else if (maxq.size() < (maxq.size() + minq.size() + 1) / 2) {
        maxq.push(minq.top());
        minq.pop();
    }

    // ans : maxq.top()
}