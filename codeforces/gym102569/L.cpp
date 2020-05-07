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
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(all(arr), greater<>());
    ll ans = 0;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        cur += arr[i];
        cur -= i + 1;
        ans = max(ans, cur);
    }
    cout << ans << endl;
}
