/**
 * @brief 二叉堆
 * 小根堆：父节点的权值 <= 子节点的权值
 * 大根堆：父节点的权值 >= 子节点的权值
 * heap[1]是序列最值
 */ 

#include <algorithm>

const int maxn = 1e5 + 10;

int heap[maxn], heap_size;

void push(int x) {
    heap[++heap_size] = x;
    for (int i = heap_size; i > 1 && heap[i] < heap[i >> 1]; i >>= 1) std::swap(heap[i], heap[i >> 1]);
}

int get_son(int i) {
    return ((i << 1) + ((i << 1 | 1) <= heap_size && heap[i << 1 | 1] < heap[i << 1]));
}

void pop() {
    std::swap(heap[1], heap[heap_size--]);
    for (int i = 1, t = get_son(i); t <= heap_size && heap[t] < heap[i]; i = t, t = get_son(i)) std::swap(heap[i], heap[t]); 
}

int get() { return heap[1]; }