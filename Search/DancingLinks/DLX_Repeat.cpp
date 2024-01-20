#include <vector>
#include <cstring>

using namespace std;

struct DLX_Repeat {
    static const int maxn = 60, maxm = 60;
    static const int maxnode = (maxn + 2) * (maxm + 2);
    int n, m, idx;
    int INF;
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], row[maxnode], col[maxnode];
    int first[maxn], sz[maxm];
    bool exist_one[maxm];
    int remain_all_zero;
    vector<int> tmp_ans;
    void clear()
    {
        memset(U, 0, sizeof(int) * (idx + 1));
        memset(D, 0, sizeof(int) * (idx + 1));
        memset(R, 0, sizeof(int) * (idx + 1));
        memset(L, 0, sizeof(int) * (idx + 1));
        memset(row, 0, sizeof(int) * (idx + 1));
        memset(col, 0, sizeof(int) * (idx + 1));
        memset(first, 0, sizeof(int) * (n + 1));
        memset(sz, 0, sizeof(int) * (m + 1));
        memset(exist_one, 0, sizeof(bool) * (m + 1));
    }
    void init(const int& r, const int& c, const int& search_limit)
    {
        clear();
        n = r;
        m = c;
        INF = search_limit;
        remain_all_zero = m;
        for (int i = 0; i <= m; i++)
        {
            exist_one[i] = 0;
            sz[i] = 0;
            U[i] = D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0;
        L[0] = m;
        idx = m;
    }
    void insert(const int& r, const int& c)
    {
        if (!exist_one[c])
            exist_one[c] = 1, --remain_all_zero;
        ++sz[col[++idx] = c];
        row[idx] = r;
        D[idx] = D[c], U[D[c]] = idx;
        U[idx] = c, D[c] = idx;
        if (!first[r])
            first[r] = L[idx] = R[idx] = idx;
        else
        {
            R[idx] = R[first[r]], L[R[first[r]]] = idx;
            L[idx] = first[r], R[first[r]] = idx;
        }
    }
    void remove(const int& c)
    {
        for (int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(const int& c)
    {
        for (int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    bool v[maxm];
    int f()
    { // A*搜索估价函数
        int ret = 0;
        for (int i = R[0]; i != 0; i = R[i])
            v[i] = 1;
        for (int i = R[0]; i != 0; i = R[i])
            if (v[i])
            {
                ret++;
                v[i] = 0;
                for (int j = D[i]; j != i; j = D[j])
                    for (int k = R[j]; k != j; k = R[k])
                        v[col[k]] = 0;
            }
        return ret;
    }
    int res;
    void dance()
    {
        if (tmp_ans.size() + f() >= res)
            return;
        // use R[0] > k || R[0] == 0 if we only need first k columns repeatly covered.
        if (R[0] == 0) 
        {
            res = tmp_ans.size();
            return;
        }
        int c = R[0];
        // use (i != 0 && i <= k) at for looping
        // if we only need first k columns repeatly covered.
        for (int i = R[0]; i != 0; i = R[i])
            if (sz[i] < sz[c])
                c = i;
        for (int i = D[c]; i != c; i = D[i])
        {
            for (int j = R[i]; j != i; j = R[j])
                remove(j);
            remove(i);
            tmp_ans.push_back(row[i]);
            dance();
            tmp_ans.pop_back();
            resume(i);
            for (int j = L[i]; j != i; j = L[j])
                resume(j);
        }
        return;
    }
    int solve()
    {
        tmp_ans.clear();
        res = INF; // need to be adjusted with real problem
        if (remain_all_zero)
            return res;
        dance();
        return res;
    }
} dlx;
