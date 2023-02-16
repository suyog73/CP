// Suyog Patil

#include <bits/stdc++.h>
using namespace std;

// ---------------------Disjoint Set---------------------------//

class DisjointSet
{
    vector<int> parent, rank, size;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        parent.resize(n + 1);

        for (int i = 0; i < n + 1; i++)
            parent[i] = i;
    }

    int findParent(int u)
    {
        if (u == parent[u])
            return u;

        return parent[u] = findParent(parent[u]); // Path compression
    }

    void unionByRank(int u, int v)
    {
        int upU = findParent(u); // ultimate parent of U
        int upV = findParent(v); // ultimate parent of V

        // belonging to same component
        if (upU == upV)
            return;

        if (rank[upU] < rank[upV])
            parent[upU] = upV;

        else if (rank[upU] > rank[upV])
            parent[upV] = upU;

        else
        {
            parent[upV] = upU;
            rank[upU]++;
        }
    }

    void unionBySize(int u, int v)
    {
        int upU = findParent(u); // ultimate parent of U
        int upV = findParent(v); // ultimate parent of V

        // belonging to same component
        if (upU == upV)
            return;

        if (size[upU] < size[upV])
        {
            parent[upU] = upV;
            size[upV] += size[upU];
        }
        else
        {
            parent[upV] = upU;
            size[upU] += size[upV];
        }
    }
};
