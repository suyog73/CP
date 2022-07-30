// Suyog Patil

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define printv(v)          \
    for (auto vv : v)      \
        cout << vv << " "; \
    cout << "\n";
#define printpair(v)  \
    for (auto vv : v) \
        cout << vv.first << " " << vv.second << "\n";
#define bug(...) __f(#__VA_ARGS__, __VA_ARGS__)
#define test_cases \
    int TT;        \
    cin >> TT;     \
    while (TT--)
#define vsort(v) sort(v.begin(), v.end())
#define csort(v) sort(v.begin(), v.end(), myComparator)
const int MOD = 1e9 + 7;

int mod_add(int a, int b, int m)
{
    a = a % m;
    b = b % m;
    return (((a + b) % m) + m) % m;
}
int mod_mul(int a, int b, int m)
{
    a = a % m;
    b = b % m;
    return (((a * b) % m) + m) % m;
}
int mod_sub(int a, int b, int m)
{
    a = a % m;
    b = b % m;
    return (((a - b) % m) + m) % m;
}

bool myComparator(const pair<int, int> &a, const pair<int, int> &b) { return (a.first < b.first); }

template <typename Arg1>
void __f(const char *name, Arg1 &&arg1) { cerr << name << " : " << arg1 << "\n"; }
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&...args)
{
    const char *comma = strchr(names + 1, ',');
    cerr.write(names, comma - names) << " : " << arg1 << " || ";
    __f(comma + 1, args...);
}

// -------------------------------------------------------------------------------------------------//

// Segment Tree

class SegmentTree
{
private:
    vector<int> sg;

public:
    SegmentTree(int n)
    {
        sg.resize(4 * n + 4);
    }

    void build(int l, int r, int treeIdx, vector<int> &v);
    int query(int l, int r, int ql, int qr, int treeIdx);
    void pointUpdate(int l, int r, int idx, int val, int treeIdx);
    void printTree(int l, int r, int treeIdx);
};

void SegmentTree::build(int l, int r, int treeIdx, vector<int> &v)
{
    if (l == r)
    {
        sg[treeIdx] = v[l];
        return;
    }

    int mid = l + (r - l) / 2;
    build(l, mid, treeIdx * 2, v);
    build(mid + 1, r, treeIdx * 2 + 1, v);

    sg[treeIdx] = min(sg[treeIdx * 2], sg[treeIdx * 2 + 1]);
}

int SegmentTree::query(int l, int r, int ql, int qr, int treeIdx)
{
    // No overlap: ql qr l r || l r ql qr
    if (qr < l or r < ql)
        return 1e18;

    // Complete Overlap: ql l r qr
    if (ql <= l and r <= qr)
        return sg[treeIdx];

    int mid = l + (r - l) / 2;

    int left = query(l, mid, ql, qr, treeIdx * 2);
    int right = query(mid + 1, r, ql, qr, treeIdx * 2 + 1);

    return min(left, right);
}

void SegmentTree::pointUpdate(int l, int r, int idx, int val, int treeIdx)
{
    if (l == r)
    {
        sg[treeIdx] = val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (idx <= mid)
        pointUpdate(l, mid, idx, val, treeIdx * 2);
    else
        pointUpdate(mid + 1, r, idx, val, treeIdx * 2 + 1);

    sg[treeIdx] = min(sg[treeIdx * 2], sg[treeIdx * 2 + 1]);
}

void SegmentTree::printTree(int l, int r, int treeIdx)
{
    cout << "Treeidx: " << treeIdx << " value: " << sg[treeIdx] << "\n";
    if (l == r)
        return;

    int mid = l + (r - l) / 2;
    printTree(l, mid, treeIdx * 2);
    printTree(mid + 1, r, treeIdx * 2 + 1);
}

void code()
{
    int n;
    cin >> n;

    vector<int> v1(n);
    for (int i = 0; i < n; i++)
        cin >> v1[i];

    SegmentTree sg1(n);
    sg1.build(0, n - 1, 1, v1);

    // sg1.printTree(0, n - 1, 1);
    // cout << "\n";

    int m;
    cin >> m;
    vector<int> v2(m);
    for (int i = 0; i < m; i++)
        cin >> v2[i];

    SegmentTree sg2(m);
    sg2.build(0, m - 1, 1, v2);

    // sg1.printTree(0, m - 1, 1);
    // cout << "\n";

    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;

            l1--, r1--, l2--, r2--;

            int min1 = sg1.query(0, n - 1, l1, r1, 1);
            int min2 = sg2.query(0, m - 1, l2, r2, 1);

            cout << min(min1, min2) << "\n";
        }
        else
        {
            int arrayNo, idx, val;
            cin >> arrayNo >> idx >> val;

            idx--;

            if (arrayNo == 1)
                sg1.pointUpdate(0, n - 1, idx, val, 1), v1[idx] = val;
            else
                sg2.pointUpdate(0, m - 1, idx, val, 1), v2[idx] = val;
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // test_cases
    code();
}