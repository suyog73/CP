// Suyog Patil

#include <bits/stdc++.h>
using namespace std;

int main()
{

    return 0;
}

class Solution
{

    vector<int> segTree;
    int n, ans = 0;

public:
    void buildSegmentTree(int l, int r, int treeIdx, vector<int> &v)
    {
        if (l == r)
        {
            segTree[treeIdx] = v[l];
            return;
        }

        int mid = l + (r - l) / 2;
        buildSegmentTree(l, mid, 2 * treeIdx, v);
        buildSegmentTree(mid + 1, r, 2 * treeIdx + 1, v);

        segTree[treeIdx] = segTree[2 * treeIdx] + segTree[treeIdx * 2 + 1];
    }

    bool checkValid(int val, int lower, int upper)
    {
        if (val <= upper and val >= lower)
            return 1;

        return 0;
    }

    int totalQuery(int l, int r, int lower, int upper, int treeIdx)
    {
        if (l == r)
        {
            if (checkValid(segTree[treeIdx], lower, upper))
                ans++;
        }
        else
        {

            if (checkValid(segTree[treeIdx], lower, upper))
                ans++;
            int mid = l + (r - l) / 2;

            return totalQuery(l, mid, lower, upper, treeIdx * 2) +
                   totalQuery(mid + 1, r, lower, upper, treeIdx * 2 + 1);
        }
        return ans;
    }

    int countRangeSum(vector<int> &v, int lower, int upper)
    {
        int n = v.size();
        segTree.resize(4 * n + 4);
        buildSegmentTree(0, n - 1, 1, v);     

        return ans;
    }
};