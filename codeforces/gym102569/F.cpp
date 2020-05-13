#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

void InitIO(string name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (name.size()) {
        assert(freopen((name + ".in").c_str(), "r", stdin));
        assert(freopen((name + ".out").c_str(), "w", stdout));
    }
}

template<typename T>
void setmax(T& a, T b) {
    if (a < b) a = b;
}

int main() {
    InitIO();
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1\n1\n";
        return 0;
    }
    if (n == 2) {
        cout << "2\n1 2\n";
        return 0;
    }
    int k = n / 2;
    vector<int> ans;
    for (int i = 0; i < k; i++) {
        ans.push_back(k);
    }
    int rem = n - k;
    if (rem <= k + 1) {
        ans.push_back(n);
    } else {
        ans.push_back(n);
        ans.push_back(n);
    }
    cout << ans.size() << endl;
    for (int val : ans) cout << val << ' ';
    cout << endl;
}
