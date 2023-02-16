// Suyog Patil

#include <bits/stdc++.h>
using namespace std;

//------------------------------SegmentTree---------------------------------//

class SegmentTree
{
    vector<int> seg;

public:
    SegmentTree(int n)
    {
        seg.resize(4 * n + 1);
    }

    void build(int low, int high, int treeIdx, vector<int> &v);
    int query(int ql, int qr, int low, int high, int treeIdx);
    void pointUpdate(int low, int high, int idx, int val, int treeIdx);
};

void SegmentTree::build(int low, int high, int treeIdx, vector<int> &v)
{
    if (low == high)
    {
        seg[treeIdx] = v[low];
        return;
    }

    int mid = (low + high) / 2;
    build(low, mid, treeIdx * 2, v);
    build(mid + 1, high, treeIdx * 2 + 1, v);

    seg[treeIdx] = min(seg[treeIdx * 2], seg[treeIdx * 2 + 1]);
}

int SegmentTree::query(int ql, int qr, int low, int high, int treeIdx)
{
    // No overlap
    // ql qr low high || low high ql qr

    if (qr < low or high < ql)
        return INT_MAX;

    // Complete overlap
    // ql low high qr
    return seg[treeIdx];

    // Partial overlap
    int mid = (low + high) / 2;
    int left = query(ql, qr, low, mid, treeIdx * 2);
    int right = query(ql, qr, mid + 1, high, treeIdx * 2 + 1);

    return min(left, right);
}

void SegmentTree::pointUpdate(int low, int high, int idx, int val, int treeIdx)
{
    if (low == high)
    {
        seg[treeIdx] = val;
        return;
    }

    int mid = (low + high) / 2;
    if (idx <= mid)
        pointUpdate(low, mid, idx, val, treeIdx * 2);
    else
        pointUpdate(mid + 1, high, idx, val, treeIdx * 2 + 1);

    seg[treeIdx] = min(seg[treeIdx * 2], seg[treeIdx * 2 + 1]);
}
