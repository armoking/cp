#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        s = "R" + s + "R";
        const int n = size(s);
        int ans = 0;
        int cur = 1;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'L') {
                cur++;
            } else {
                cur = 1;
            }
            ans = max(ans, cur);
        }
        cout << ans << '\n';
    }
}
