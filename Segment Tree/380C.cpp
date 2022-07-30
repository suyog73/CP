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
const int MAX_N = 1e6;
int ans[4 * MAX_N] = {0};
int leftP[4 * MAX_N] = {0};  // Left Parenthethisis
int rightP[4 * MAX_N] = {0}; // Right Parenthethisis

typedef pair<int, pair<int, int>> node;

string s;

void buildSegTree(int l, int r, int treeIdx)
{
    if (l == r)
    {
        if (s[l] == '(')
            leftP[treeIdx] = 1;
        else
            rightP[treeIdx] = 1;

        ans[treeIdx] = 0;
        return;
    }

    int mid = l + (r - l) / 2;
    buildSegTree(l, mid, treeIdx * 2);
    buildSegTree(mid + 1, r, treeIdx * 2 + 1);

    int temp = min(leftP[treeIdx * 2], rightP[treeIdx * 2 + 1]);
    ans[treeIdx] = ans[treeIdx * 2] + ans[treeIdx * 2 + 1] + temp;
    leftP[treeIdx] = leftP[treeIdx * 2] + leftP[treeIdx * 2 + 1] - temp;
    rightP[treeIdx] = rightP[treeIdx * 2] + rightP[treeIdx * 2 + 1] - temp;
}

void printSegmentTree(int l, int r, int treeIdx)
{
    cout << "idx= " << treeIdx << ", leftParen= " << leftP[treeIdx] << ", rightParen= " << rightP[treeIdx] << ", ans: " << ans[treeIdx] << "\n";
    if (l == r)
        return;

    int mid = l + (r - l) / 2;
    printSegmentTree(l, mid, treeIdx * 2);
    printSegmentTree(mid + 1, r, treeIdx * 2 + 1);
}

node querySegmentTree(int l, int r, int ql, int qr, int treeIdx)
{
    if (r < ql or l > qr)
        return {0, {0, 0}};

    if (ql <= l && r <= qr)
        return {ans[treeIdx], {leftP[treeIdx], rightP[treeIdx]}};

    int mid = l + (r - l) / 2;
    node nodeLeft = querySegmentTree(l, mid, ql, qr, treeIdx * 2);
    node nodeRight = querySegmentTree(mid + 1, r, ql, qr, treeIdx * 2 + 1);

    int temp = min(nodeLeft.second.first, nodeRight.second.second);
    int ans1 = nodeLeft.first + nodeRight.first + temp;
    int tempLeft = nodeLeft.second.first + nodeRight.second.first - temp;
    int tempRight = nodeLeft.second.second + nodeRight.second.second - temp;

    return {ans1, {tempLeft, tempRight}};
}

void code()
{
    cin >> s;
    int n = s.size();

    buildSegTree(0, n - 1, 1);
    // printSegmentTree(0, n - 1, 1);
    int m;
    cin >> m;

    while (m--)
    {
        int l, r;
        cin >> l >> r;

        l--, r--;

        node ans = querySegmentTree(0, n - 1, l, r, 1);
        cout << ans.first * 2 << "\n";
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