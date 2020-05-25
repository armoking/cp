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

int main() {
    InitIO();
    int n;
    cin >> n;
    vector<int> deg(n);
    for (int i = 0; i < n - 1; i++) {
        int f, t;
        cin >> f >> t;
        f--, t--;
        deg[f]++;
        deg[t]++;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] <= 1) {
            ans++;
        }
    }
    cout << (ans + 1) / 2 << endl;
}
