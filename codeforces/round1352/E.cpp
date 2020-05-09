#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<int> pref = a;
        for (int i = 1; i < n; i++) {
            pref[i] += pref[i - 1];
        }
        auto sum = [&] (int l, int r) {
            return pref[r] - (l > 0 ? pref[l - 1] : 0);
        };
        int ans = 0;
        vector<int> cnt(n + 1);
        for (int val : a) cnt[val]++;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int cur = sum(i, j);
                if (cur <= n) {
                    ans += cnt[cur];
                    cnt[cur] = 0;
                }
            }
        }

        cout << ans << '\n';
    }
}
