#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

void InitIO(std::string name = "") {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (name.size()) {
        assert(freopen((name + ".in").c_str(), "r", stdin));
        assert(freopen((name + ".out").c_str(), "w", stdout));
    }
}

using namespace std;
using ll = long long;

int main() {
    InitIO();
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        const int n = s.size();
        string t = s;
        sort(all(t));
        if (t[0] == t.back()) {
            cout << s << endl;
        } else {
            for (int i = 0; i < 2 * n; i++) {
                cout << char('0' + (i & 1));
            }
            cout << endl;
        }
    }
}
