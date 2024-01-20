/**
 * @brief 单调队列：维护长度为 n 的序列中，长度为 m 的区间的最值
 * 
 */

#include <iostream>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

int a[N];

struct MonotonicQueue {
    int q[N], hh, tt, type;   
    // q: 维护元素下标；hh: 队顶；tt: 队尾
    // type = 0: 维护min \ type = 1: 维护max
    // min: 维护单调递增；max: 维护单调递减
    void init() {
        hh = 0; tt = -1;
    }
    void push(int i) {
        if (type == 0) {
            while (hh <= tt && a[q[tt]] >= a[i]) --tt;
        } else {
            while (hh <= tt && a[q[tt]] <= a[i]) --tt;
        } 
        q[++tt] = i;
    }
    void pop(int i) {  
        while (hh <= tt && q[hh] <= i) ++hh;
    }
    int val() {
        return a[q[hh]];
    }
} qmin, qmax;