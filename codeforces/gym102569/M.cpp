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
 
int main() {
    InitIO();
    int n;
    cin >> n;
    vector<pair<ll, ll>> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }
    ll lst = 0;
    for (int i = 0; i < n; i++) {
        lst = max(lst, arr[i].first);
        lst += arr[i].second;
    }
    cout << lst << endl;
}
