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
        int n0, n1, n2;
        cin >> n0 >> n1 >> n2;
        int n = n0 + n1 + n2 + 1;
        if (n0 == 0 && n1 == 0) {
            cout << string(n, '1') << '\n';
            continue;
        } else if (n0 == n - 1) {
            cout << string(n, '0') << '\n';
            continue;
        }
        string ans = "0";
        for (int i = 0; i < n0; i++) {
            ans.push_back('0');
        }
        if (n1 % 2 == 0) {
            ans = "1" + ans;
            n1--;
        }
        for (int i = 0; i < n1; i++) {
            if (i & 1) {
                ans.push_back('0');
            } else {
                ans.push_back('1');
            }
        }
        for (int i = 0; i < n2; i++) {
            ans.push_back('1');
        }
        cout << ans << '\n';
    }
}
