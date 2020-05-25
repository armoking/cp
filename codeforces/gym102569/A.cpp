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
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int cur = (n - 1 - i) & 1;
        if (cur) {
            sum -= arr[i];
        } else {
            sum += arr[i];
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r, v;
        cin >> l >> r >> v;
        if ((r - l + 1) & 1) {
            int f = (n - r) & 1;
            if (f) {
                sum -= v;
            } else {
                sum += v;
            }
        }
        cout << sum << '\n';
    }
}
