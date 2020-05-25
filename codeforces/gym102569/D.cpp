#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

void InitIO(string name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (name.size()) {
        assert(freopen((name + ".in").c_str(), "r", stdin));
        assert(freopen((name + ".out").c_str(), "w", stdout));
    }
}

struct E {
    int t;
    char ch;
};

const int N = 200200;
vector<E> g[N];
int depth[N];
int depth2[N];

void bfs(int from, int depth[N]) {
    depth[from] = 0;
    queue<int> q;
    q.push(from);
    while (q.size()) {
        int v = q.front();
        q.pop();
        for (auto [to, ch] : g[v]) {
            if (depth[to] > depth[v] + 1) {
                depth[to] = depth[v] + 1;
                q.push(to);
            }
        }
    }
}

int main() {
    InitIO();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int f, t;
        char ch;
        cin >> f >> t >> ch;
        f--, t--;
        g[f].push_back({t, ch});
        g[t].push_back({f, ch});
    }
    const int inf = 1e9;
    fill(depth, depth + N, inf);
    bfs(0, depth);
    fill(depth2, depth2 + N, inf);
    bfs(n - 1, depth2);
    vector<vector<E>> dirgraph(n), kek(n);
    for (int i = 0; i < n; i++) {
        for (auto& [to, ch] : g[i]) {
            if (depth2[to] + depth[i] + 1 == depth[n - 1]) {
                dirgraph[i].push_back({to, ch});
                kek[to].push_back({i, ch});
            }
        }
    }
    vector<int> q = {0};
    string ans = "";
    vector<bool> poss(n);
    poss[0] = true;
    while (q.size()) {
        set<pair<char, int>> nxt;
        for (int v : q) {
            for (auto& [to, ch] : dirgraph[v]) {
                nxt.insert({ch, to});
            }
        }
        if (nxt.size() == 0) break;

        while (nxt.begin()->first != prev(nxt.end())->first) nxt.erase(prev(nxt.end()));
        q.clear();

        ans.push_back(nxt.begin()->first);
        for (auto& [ch, to] : nxt) {
            q.push_back(to);
            poss[to] = true;
        }
    }

    cout << ans.size() << endl;

    int cur = n - 1;
    vector<int> res = {cur};
    int itr = ans.size() - 1;
    while (cur > 0) {
        for (auto& [to, ch] : kek[cur]) {
            if (poss[to] && depth[to] + 1 == depth[cur] && ch == ans[itr]) {
                res.push_back(to);
                cur = to;
                itr--;
                break;
            }
        }
    }
    reverse(all(res));
    for (int v : res) cout << v + 1 << ' ';

    cout << endl;

    cout << ans << endl;
}
