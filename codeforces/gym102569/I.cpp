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
 
void setmin(int& a, int b) {
    if (a > b) a = b;
}
void setmax(int& a, int b) {
    if (a < b) a = b;
}
 
 
int main() {
    InitIO();
    int n;
    cin >> n;
    map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        mp[y].push_back(x);
    }
    bool poss = true;
    vector<pair<int,int>> arr;
    for (auto& [val, v] : mp) {
        poss &= is_sorted(all(v));
        arr.push_back({v[0], v.back()});
    }
    cout << (poss ? "YES\n" : "NO\n");
}
