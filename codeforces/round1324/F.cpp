#include <bits/stdc++.h>

using namespace std;

#define N 200200

vector<int> g[N];
int ans[N];
int ans2[N];
int clr[N];

void dfs1(int from, int par) {
    ans[from] = clr[from];
    for (int v : g[from]) {
        if (v == par) continue;
        dfs1(v, from);
        ans[from] += max(0, ans[v]);
    }
}

void dfs2(int from, int par, int cur) {
    ans2[from] = ans[from] + cur;
    int dlt = clr[from];
    for (int v : g[from]) {
        if (v == par) continue;
        dlt += max(0, ans[v]);
    }
    cur += dlt;
    for (int v : g[from]) {
        if (v == par) continue;
        if (ans[v] > 0) {
            dfs2(v, from, max(cur - ans[v], 0));
        } else {
            dfs2(v, from, max(cur, 0));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> clr[i];
        if (clr[i] == 0) clr[i]--;
    }
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        f--, t--;
        g[f].push_back(t);
        g[t].push_back(f);
    }
    dfs1(0, 0);
    dfs2(0, 0, 0);
    for (int i = 0; i < n; i++) {
        cout << ans2[i] << ' ';
    }
    cout << endl;
}
