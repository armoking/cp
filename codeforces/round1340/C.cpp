#pragma GCC Optimaze("Ofast")
#pragma GCC target("avx,avx2")
 
#include <bits/stdc++.h>
#define all(x) begin(x),end(x)
 
using namespace std;
 
void InitIO(std::string name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (name.size()) {
        assert(freopen((name + ".in").c_str(), "r", stdin));
        assert(freopen((name + ".out").c_str(), "w", stdout));
    }
}
 
const int QMAX = 1e4 + 1e3 + 1;
const int RMAX = 1e3 + 1;
int inf = 1e9 + 1;
 
int d[QMAX];
int depth[QMAX][RMAX];
vector<pair<int,int>> queries[QMAX];
 
int n, m, g, r;
 
int Bfs0K() {
    fill(&depth[0][0], &depth[QMAX - 1][RMAX - 1], inf);
    depth[0][g] = 0;
    int res = inf;
    int cnt = 1;
    queries[0].emplace_back(0, g);
 
    while (cnt > 0) {
        for (int index = 0; index < QMAX; index++) {
            for (auto& [w, v] : queries[index]) {
                cnt--;
 
                int i = v / (g + 1);
                int rem = v % (g + 1);
 
                if (depth[i][rem] < w) {
                    continue;
                }
 
                for (int j : {i - 1, i + 1}) {
                    if (j < 0 || j >= m) {
                        continue;
                    }
 
                    int dist = abs(d[i] - d[j]);
 
                    if (dist > rem) {
                        continue;
                    }
 
                    int nxt = rem - dist;
                    int w = rem - nxt + (nxt == 0 && j + 1 != m ? r : 0);
 
                    if (nxt == 0) {
                        nxt = g;
                    }
 
                    if (depth[j][nxt] > depth[i][rem] + w) {
                        depth[j][nxt] = depth[i][rem] + w;
                        queries[(index + w) % QMAX].emplace_back(depth[j][nxt], j * (g + 1) + nxt);
                        cnt++;
                    }
                }
            }
            queries[index] = {};
        }
    }
 
    for (int i = 1; i <= g; i++) {
        res = min(res, depth[m - 1][i]);
    }
    return res;
}
 
 
 
int main() {
    InitIO("");
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> d[i];
    }
    cin >> g >> r;
 
    sort(d, d + m);
 
    int res = Bfs0K();
 
    if (res == inf) {
        res = -1;
    }
 
    cout << res << endl;
}
