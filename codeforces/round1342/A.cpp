#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

void InitIO(std::string name = "") {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (name.size()) {
        assert(freopen((name + ".in").c_str(), "r", stdin));
        assert(freopen((name + ".out").c_str(), "w", stdout));
    }
}

using namespace std;
using ll = long long;

int main() {
    InitIO();
    int t;
    cin >> t;
    while (t--) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        b = min(b, 2 * a);
        ll ans = 1ll * min(x, y) * b;
        ans += 1ll * a * (max(x, y) - min(x, y));
        cout << ans << endl;
    }
}
