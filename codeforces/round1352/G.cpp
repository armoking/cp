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
        if (n <= 3) {
            cout << -1 << '\n';
            continue;
        }
        if (n == 6) {
            cout << "5 3 6 2 4 1\n";
            continue;
        }
        if (n == 7) {
            cout << "5 1 3 6 2 4 7\n";
            continue;
        }
        if (n == 11) {
            cout << "1 4 2 5 3 6 9 7 11 8 10\n";
            continue;
        }
        vector<int> temp4 = {1, 3, 0, 2};
        vector<int> temp5 = {0, 3, 1, 4, 2};
        int a4 = 0, a5 = 0;
        for (int c4 = 0; c4 <= n / 4; c4++) {
            int rem = n - c4 * 4;
            if (rem % 5 == 0) {
                a4 = c4;
                a5 = rem / 5;
                break;
            }
        }
        int cur = 1;
        for (int i = 0; i < a4; i++) {
            for (int val : temp4) {
                cout << (val + cur) << ' ';
            }
            cur += 4;
        }
        for (int i = 0; i < a5; i++) {
            for (int val : temp5) {
                cout << (val + cur) << ' ';
            }
            cur += 5;
        }
        cout << '\n';
    }
}

