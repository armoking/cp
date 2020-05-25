#include <bits/stdc++.h>

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
        vector<int> a(n);
        map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mp[a[i]].push_back(i);
        }
        bool good = false;
        for (auto& [val, v] : mp) {
            if (v.back() - v[0] >= 2) {
                good = true;
            }
        }
        cout << (good ? "YES\n" : "NO\n");
    }
}
