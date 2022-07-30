//
// Created by Bhagirathi Nayak on 11/07/20.
//

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000000 + 5;           // maximum number of nodes in an array
int st[MAX_N * 4];                       // the segment tree with max size of 4*MAX_N
int n;                                   // size of array
int arr[] = {2, 4, 1, 3, 9, 11, 13, 16}; // hard coding this for simplicity purpose

int getMid(int s, int e) { return s + (e - s) / 2; }

// Time complexity  : O(n) to build the entire tree
// treeIdx marked node of the segment tree holds the property from index l to index r
void build(int l, int r, int treeIdx)
{

    if (l == r)
    { // we can't move down any further as we have reached the leaf
        st[treeIdx] = arr[l];
        return;
    }

    int mid = getMid(l, r);
    build(l, mid, treeIdx * 2);         // build left subtree
    build(mid + 1, r, treeIdx * 2 + 1); // build right subtree

    st[treeIdx] = st[treeIdx * 2] + st[treeIdx * 2 + 1];
}

// Time complexity  : O(log n)
int query(int l, int r, int ql, int qr, int treeIdx)
{

    // If the current segment of this node is outside the given range
    if (r < ql || l > qr)
        return 0;

    // if the current segment is a part of the given range
    if (r <= qr && l >= ql)
        return st[treeIdx];

    // If a part of this segment overlaps with the given range
    int mid = getMid(l, r);
    return query(l, mid, ql, qr, treeIdx * 2) +
           query(mid + 1, r, ql, qr, treeIdx * 2 + 1);
}

// Time complexity : O(log n)
void update(int l, int r, int idx, int val, int treeIdx)
{

    if (l == r)
    { // we have hit a leaf node and we have to update
        st[treeIdx] = val;
    }
    else
    { // If we are on an intermediate node we check whether to go to left subtree or right subtree
        int mid = getMid(l, r);
        if (idx <= mid)
            update(l, mid, idx, val, treeIdx * 2);
        else
            update(mid + 1, r, idx, val, treeIdx * 2 + 1);
        st[treeIdx] = st[treeIdx * 2] + st[treeIdx * 2 + 1];
    }
}

int main()
{

    n = sizeof(arr) / sizeof(arr[0]);

    // Build a segment tree from the array
    build(0, n - 1, 1);

    // Build the tree and do range query
    cout << query(0, n - 1, 0, 3, 1) << endl;
    cout << query(0, n - 1, 2, 5, 1) << endl;
    cout << query(0, n - 1, 3, 6, 1) << endl;
    cout << query(0, n - 1, 6, 6, 1) << endl;

    // point update and range query
    cout << "Point update and range Query\n";
    cout << "Before update sum of 0 to 3 : ";
    cout << query(0, n - 1, 0, 3, 1) << endl;
    // update(0,n-1,2,1000,1);
    cout << "After update sum of 0 to 3 : ";
    cout << query(0, n - 1, 0, 3, 1) << endl;

    cout << "Point update and range Query\n";
    cout << "Before update sum of 2 to 6 : ";
    cout << query(0, n - 1, 2, 6, 1) << endl;
    update(0, n - 1, 5, 1000, 1);
    cout << "After update sum of 2 to 6 : ";
    cout << query(0, n - 1, 2, 6, 1) << endl;

    return 0;
}