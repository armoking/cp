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
 
int slv(vector<int> a, int n, int t) {
    int ans = 0;
    int tmp = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] <= 0) {
            tmp = i;
        }
    }
    if (tmp == -1) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) break;
        int cur = 0;
        if (abs(a[i]) > t) continue;
        int rem = t - abs(a[i]);
        int left = i;
        int right = n - 1;
        int mid;
        int st = tmp;
        while (left <= right) {
            mid = (left + right) / 2;
            int f = a[mid] - a[i];
            if (f <= rem) {
                st = max(st, mid);
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        ans = max(ans, st - i + 1);
    }
    return ans;
}
 
 
int main() {
    InitIO();
    int n;
    cin >> n;
    int t;
    cin >> t;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = slv(a, n, t);
    reverse(all(a));
    for (int i = 0; i < n; i++) a[i] = -a[i];
    ans = max(ans, slv(a, n, t));
    cout << ans << endl;
}
