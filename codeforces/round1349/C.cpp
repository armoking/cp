#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

const int N = 1001;

char a[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, t;
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<pair<int,int>> steps = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0}
    };
    const int inf = 1e9;
    vector<int> depth(n * m, inf);

    queue<int> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int good = 0;
            for (auto& [dx, dy] : steps) {
                int nx = i + dx;
                int ny = j + dy;
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if (a[i][j] == a[nx][ny]) {
                    good++;
                }
            }
            if (good) {
                depth[i * m + j] = 0;
                q.push(i * m + j);
            }
        }
    }


    while (q.size()) {
        auto v = q.front();
        q.pop();
        int x = v / m;
        int y = v % m;
        for (auto& [dx, dy] : steps) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            int dist = depth[x * m + y] + 1;
            if (depth[nx * m + ny] > dist) {
                depth[nx * m + ny] = dist;
                q.push(nx * m + ny);
            }
        }
    }

    while (t--) {
        int x, y;
        cin >> x >> y;
        ll t;
        cin >> t;
        x--, y--;
        int cur = depth[x * m + y];
        if (cur == inf || cur >= t) {
            cout << a[x][y] << '\n';
        } else {
            int dlt = (t - depth[x * m + y]) & 1;
            cout << ((a[x][y] - '0') ^ dlt) << '\n';
        }
    }

}
