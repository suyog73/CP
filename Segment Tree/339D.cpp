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

    void build(int l, int r, int treeIdx, vector<int> &v, bool isOR);
    int query();
    void pointUpdate(int l, int r, int idx, int val, int treeIdx, bool isOR);
    void printTree(int l, int r, int treeIdx);
};

void SegmentTree::build(int l, int r, int treeIdx, vector<int> &v, bool isOR)
{
    if (l == r)
    {
        sg[treeIdx] = v[l];
        return;
    }

    int mid = l + (r - l) / 2;
    build(l, mid, treeIdx * 2, v, !isOR);
    build(mid + 1, r, treeIdx * 2 + 1, v, !isOR);

    if (isOR)
        sg[treeIdx] = (sg[treeIdx * 2] | sg[treeIdx * 2 + 1]);
    else
        sg[treeIdx] = (sg[treeIdx * 2] ^ sg[treeIdx * 2 + 1]);
}

int SegmentTree::query() { return sg[1]; }

void SegmentTree::pointUpdate(int l, int r, int idx, int val, int treeIdx, bool isOR)
{
    if (l == r)
    {
        sg[treeIdx] = val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (idx <= mid)
        pointUpdate(l, mid, idx, val, treeIdx * 2, !isOR);
    else
        pointUpdate(mid + 1, r, idx, val, treeIdx * 2 + 1, !isOR);

    if (isOR)
        sg[treeIdx] = (sg[treeIdx * 2] | sg[treeIdx * 2 + 1]);
    else
        sg[treeIdx] = (sg[treeIdx * 2] ^ sg[treeIdx * 2 + 1]);
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

    int n, m;
    cin >> n >> m;

    bool isOR = 0;
    if (n % 2)
        isOR = 1;

    int x = (1 << n);
    bug(x);
    vector<int> v(x);
    for (int i = 0; i < x; i++)
        cin >> v[i];

    SegmentTree sg(x);
    sg.build(0, x - 1, 1, v, isOR);

    while (m--)
    {
        int idx, val;
        cin >> idx >> val;

        idx--;
        sg.pointUpdate(0, x - 1, idx, val, 1, isOR);
        // sg.printTree(0, x - 1, 1);
        // cout << "\n";
        cout << sg.query() << "\n";
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