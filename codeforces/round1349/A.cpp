#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> deg(200200);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (int j = 2; j * j <= x; j++) {
            if (x % j) continue;
            int d = 0;
            while (x % j == 0) {
                x /= j;
                d++;
            }
            deg[j].push_back(d);
        }
        if (x > 1) {
            deg[x].push_back(1);
        }
    }
    ll ans = 1;
    for (int i = 2; i < 200200; i++) {
        if (deg[i].size() <= n - 2) continue;
        while (deg[i].size() < n) deg[i].push_back(0);
        sort(all(deg[i]));
        ans *= pow(i, deg[i][1]);
    }
    cout << ans << '\n';
}
