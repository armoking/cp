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
        int n, k;
        cin >> n >> k;
        if (k % 2 == 0 && n % 2 != 0 || k > n
                || k % 2 == 1 && n % 2 == 0 && n < 2 * k) {
            cout << "NO\n";
            continue;
        }
        int rem = n;
        if ((n - k + 1) % 2 == 1) {
            cout << "YES\n";
            for (int i = 1; i < k; i++) {
                cout << 1 << ' ';
            }
            cout << n - k + 1 << '\n';
            continue;
        } else {
            cout << "YES\n";
            for (int i = 1; i < k; i++) {
                cout << 2 << ' ';
            }
            cout << n - 2 * k + 2 << '\n';
            continue;
        }
    }
}
