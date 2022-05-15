// Suyog Patil
//  https://codeforces.com/problemset/problem/1675/D

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define test_cases \
    int T;         \
    cin >> T;      \
    while (T--)
#define vsort(v) sort(v.begin(), v.end())
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

int fact(int n, int mod)
{
    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        ans = mod_mul(ans, i, mod);
    }
    return (ans % mod);
}

const int N = 2e5 + 5;
vector<int> adj[N];
vector<int> ans[N];
int vis[N];
int grp = 1;

void dfs(int node)
{
    vis[node] = 1;
    ans[grp].push_back(node);

    if (adj[node].size() == 0)
        grp++;

    for (auto it : adj[node])
        if (vis[it] == 0)
            dfs(it);
}

void code()
{
    int n;
    cin >> n;

    for (int i = 0; i < n + 1; i++)
    {
        adj[i].clear();
        ans[i].clear();
        vis[i] = 0;
    }
    grp = 1;

    vector<int> v(n);
    int rootNode = -1;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        if (v[i] == i + 1)
            rootNode = v[i];

        adj[v[i]].push_back(i + 1);
    }
    // cout << "rootNode "<< rootNode << "\n";
    if (n == 1)
    {
        cout << "1\n1\n1\n";
        return;
    }

    dfs(rootNode);

    cout << grp - 1 << "\n";
    for (int i = 1; i < grp; i++)
    {
        cout << ans[i].size() << "\n";
        for (auto vv : ans[i])
        {
            cout << vv << " ";
        }
        cout << "\n";
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test_cases
    code();
}
