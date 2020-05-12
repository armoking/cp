#import <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 0 ; i < n; i++) {
            int x;
            cin >> x;
            ans += x & 1;
        }
        ans %= n;
        cout << (ans ? "NO\n" : "YES\n");
    }
}
