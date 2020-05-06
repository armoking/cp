#include <bits/stdc++.h>
#define all(x) begin(x),end(x)
 
void InitIO(std::string name = "") {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (name.size()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
 
using namespace std;
 
 
 
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> pos(n);
    for (int i = 0; i < n; i++) cin >> a[i];
 
    map<int, set<int>> mp;
    set<int> emp;
 
    for (int i = 0; i < n; i++) {
        a[i]--;
        pos[a[i]] = i;
        mp[1].insert(i);
        emp.insert(i);
    }
    vector<int> cnt(n, 1);
 
    bool possible = true;
 
    for (int i = 0; i < n; i++) {
        int ind = pos[i];
 
        if (!prev(mp.end())->second.count(ind)) {
            possible = false;
            break;
        }
        emp.erase(ind);
        auto it1 = emp.upper_bound(ind);
        auto it = prev(mp.end());
        it->second.erase(ind);
        if (it->second.size() == 0) {
            mp.erase(it);
        }
        if (it1 != emp.end()) {
            int nxt = *it1;
            int preVal = cnt[nxt];
            int nxtVal = cnt[nxt] + cnt[ind];
            mp[preVal].erase(nxt);
            mp[nxtVal].insert(nxt);
            cnt[nxt] = nxtVal;
        }
        cnt[ind] = 0;
    }
    cout << (possible ? "Yes\n" : "No\n");
}
 
int main() {
    InitIO("");
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
