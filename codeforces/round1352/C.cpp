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
        ll n, k;
        cin >> n >> k;
        ll left = 1;
        ll right = k * 2 + 2;
        ll mid;
        ll ans = 0;
        while (left <= right) {
            mid = (left + right) / 2;
            ll cur = mid - mid / n;
            if (cur >= k) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        cout << ans << '\n';
    }
}
