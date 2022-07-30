// Suyog Patil
// Build Segment tree and Range query

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAX_N = 1e6 + 5;
vector<int> segTree(4 * MAX_N, 0);
int n;
vector<int> v(MAX_N);

int getMid(int st, int end) { return (st + (end - st) / 2); }

void buildSegTree(int l, int r, int treeIdx)
{
    if (l == r)
    {
        segTree[treeIdx] = v[l];
        return;
    }

    int mid = getMid(l, r);
    buildSegTree(l, mid, treeIdx * 2);
    buildSegTree(mid + 1, r, treeIdx * 2 + 1);

    segTree[treeIdx] = max(segTree[treeIdx * 2], segTree[treeIdx * 2 + 1]);
}

int query(int l, int r, int ql, int qr, int treeIdx)
{
    // If the current segment of this node is outside the given range (No overlapping)
    if (qr < l or r < ql)
        return 0;

    // if the current segment is a part of the given range (Complete Overlapping)
    if (ql <= l and r <= qr)
        return segTree[treeIdx];

    // If a part of this segment overlaps with the given range (Partial Overlaps)
    int mid = getMid(l, r);
    return max(query(l, mid, ql, qr, treeIdx * 2),
               query(mid + 1, r, ql, qr, treeIdx * 2 + 1));
}

int32_t main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    buildSegTree(0, n - 1, 1);

    for (int i = 0; i < 30; i++)
    {
        cout << segTree[i] << " ";
    }
    cout << "\nQuery\n";
    int q;
    cin >> q;
    while (q--)
    {
        int ql, qr;
        cin >> ql >> qr;

        cout << query(0, n - 1, ql, qr, 1) << "\n";
    }

    return 0;
}
