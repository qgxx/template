// 珂朵莉树
// 把 value 相同的连续段合并为 set 中的一个点
// 基于数据随机
// O(NlogNlogN)

#include <algorithm>
#include <set>

using namespace std;

using ll = long long;

struct node {
    ll l, r;
    mutable ll v;
    node(ll l, ll r, ll v) : l{l}, r{r}, v{v} {}
    constexpr bool operator < (const node & x) const {
        return l < x.l;
    }
};
set<node> tree;

// 分裂节点
auto split(ll pos) {
    auto it = tree.lower_bound(node(pos, 0, 0));
    if (it != tree.end() && it->l == pos)
        return it;
    it--;
    ll l = it->l, r = it->r, v = it->v;
    tree.erase(it);
    tree.insert(node(l, pos - 1, v));
    return tree.insert(node(pos, r, v)).first;
}

// 区间修改(把区间内的全部节点删掉重新赋值)
void assign(ll l, ll r, ll v) {
    auto end = split(r + 1), begin = split(l);
    tree.erase(begin, end);
    tree.insert(node(l, r, v));
}