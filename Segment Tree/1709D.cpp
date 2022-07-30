// Suyog Patil
// Build Segment tree and Range query Question

#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> segTree;

int getMid(int s, int e) { return ((s + e) / 2); }

void build(int l, int r, int treeIdx, vector<int> &v)
{
    if (l > r)
        return;

    if (l == r)
    {
        segTree[treeIdx] = v[l];
        return;
    }

    int mid = getMid(l, r);

    build(l, mid, treeIdx * 2, v);
    build(mid + 1, r, 2 * treeIdx + 1, v);

    segTree[treeIdx] = max(segTree[treeIdx * 2], segTree[2 * treeIdx + 1]);
}

int query(int l, int r, int ql, int qr, int treeIdx)
{
    if (ql > r or qr < l)
        return 0;

    if (l >= ql and r <= qr)
        return segTree[treeIdx];

    int mid = getMid(l, r);
    return max(query(l, mid, ql, qr, treeIdx * 2),
               query(mid + 1, r, ql, qr, 2 * treeIdx + 1));
}

int32_t main()
{
    int n, m;
    cin >> n >> m;

    vector<int> v(m);
    for (int i = 0; i < m; i++)
    {
        cin >> v[i];
    }
    build(0, m - 1, 1, v);

    int q;
    cin >> q;

    while (q--)
    {
        bool ans = true;

        int stRow, stCol, enRow, enCol, k;
        cin >> stRow >> stCol >> enRow >> enCol >> k;

        if (stCol > enCol)
            swap(stRow, enRow), swap(stCol, enCol);

        if (stCol == enCol and stRow > enRow)
            swap(stRow, enRow);

        if (abs(enRow - stRow) % k or abs(enCol - stCol) % k)
            ans = false;
        else
        {
            int mx = query(0, m - 1, stCol - 1, enCol - 1, 1);
            // cout << "Mx " << mx << "\n";
            if (mx >= stRow)
            {
                int tp1 = ((mx - stRow) / k) + 1;
                int tp2 = tp1 * k + stRow;
                // cout << "Tp " << tp2 << "\n";

                if (n < tp2)
                    ans = false;
            }
        }

        if (ans)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
