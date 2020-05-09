#include <bits/stdc++.h>


using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        vector<string> ans;
        for (int i = 6; i >= 0; i--) {
            int d = x / pow(10, i);
            if (d == 0) continue;
            x -= d * pow(10, i);
            string cur = "";
            cur.push_back(char(d + '0'));
            cur += string(i, '0');
            ans.push_back(cur);
        }
        cout << ans.size() << '\n';
        for (auto& s : ans) {
            cout << s << ' ';
        }
        cout << '\n';
    }
}

