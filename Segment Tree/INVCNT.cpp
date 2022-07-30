// INVCNT - Inversion Count (SPOJ)

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
    SegmentTree(int n) { sg.resize(4 * n + 4); }

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

    sg[treeIdx] = sg[treeIdx * 2] + sg[treeIdx * 2 + 1];
}

int SegmentTree::query(int l, int r, int ql, int qr, int treeIdx)
{
    // No overlap: ql qr l r || l r ql qr
    if (qr < l or r < ql)
        return 0;

    // Complete Overlap: ql l r qr
    if (ql <= l and r <= qr)
        return sg[treeIdx];

    int mid = l + (r - l) / 2;

    int left = query(l, mid, ql, qr, treeIdx * 2);
    int right = query(mid + 1, r, ql, qr, treeIdx * 2 + 1);

    return left + right;
}

void SegmentTree::pointUpdate(int l, int r, int idx, int val, int treeIdx)
{
    if (l == r)
    {
        sg[treeIdx] += val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (idx <= mid)
        pointUpdate(l, mid, idx, val, treeIdx * 2);
    else
        pointUpdate(mid + 1, r, idx, val, treeIdx * 2 + 1);

    sg[treeIdx] = sg[treeIdx * 2] + sg[treeIdx * 2 + 1];
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

    vector<int> v(n);
    int mx = -1e18;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        mx = max(mx, v[i]);
    }
    vector<int> vFreq(mx, 0);
    for (int i = 0; i < n; i++)
    {
        vFreq[v[i]]++;
    }

    mx++;
    SegmentTree sg(mx);
    sg.build(0, mx - 1, 1, vFreq);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        vFreq[v[i]]--;
        sg.pointUpdate(0, mx - 1, v[i], -1, 1);
        ans += sg.query(0, mx - 1, 0, v[i] - 1, 1);
    }
    cout << ans << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    test_cases
    code();
}