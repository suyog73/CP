// Suyog Patil

#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> segTree(45511123);

int getMid(int s, int e) { return (s + (e - s) / 2); }

void printSegmentTree()
{
    for (int i = 0; i < 16; i++)
    {
        cout << segTree[i] << " ";
    }
    cout << "\n";
}

// Building a segment tree
void buildSegmentTree(int l, int r, int treeIdx, vector<int> &v)
{
    if (l == r)
    {
        segTree[treeIdx] = v[l];
        return;
    }

    int mid = getMid(l, r);
    buildSegmentTree(l, mid, 2 * treeIdx, v);
    buildSegmentTree(mid + 1, r, 2 * treeIdx + 1, v);

    segTree[treeIdx] = segTree[2 * treeIdx] + segTree[2 * treeIdx + 1];
}

// Range Query to segment tree
int rangeQuery(int l, int r, int ql, int qr, int treeNode)
{
    if (qr < l or r < ql)
        return 0;

    if (l >= ql and r <= qr)
        return segTree[treeNode];

    int mid = getMid(l, r);
    return rangeQuery(l, mid, ql, qr, 2 * treeNode) +
           rangeQuery(mid + 1, r, ql, qr, 2 * treeNode + 1);
}

// Point Update in segment tree
void pointUpdate(int l, int r, int idx, int value, int treeIdx)
{
    if (l == r)
        segTree[treeIdx] = value;
    else
    {
        int mid = getMid(l, r);
        if (idx <= mid)
            pointUpdate(l, mid, idx, value, 2 * treeIdx);
        else
            pointUpdate(mid + 1, r, idx, value, 2 * treeIdx + 1);

        segTree[treeIdx] = segTree[2 * treeIdx] + segTree[2 * treeIdx + 1];
    }
}

int32_t main()
{
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    // segTree.resize(4 * n + 4);

    buildSegmentTree(0, n - 1, 1, v);

    printSegmentTree();
    cout << rangeQuery(0, n - 1, 3, 5, 1) << "\n";
    pointUpdate(0, n - 1, 2, 100000, 1);
    printSegmentTree();
    cout << rangeQuery(0, n - 1, 2, 5, 1) << "\n";

    return 0;
}
