#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        set<int> ind;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == k) {
                ind.insert(i);
            }
            a[i] = a[i] >= k ? 1 : -1;
            if (i) a[i] += a[i - 1];
        }
        vector<int> mx = a;
        for (int i = n - 2; i >= 0; i--) {
            mx[i] = max(mx[i], mx[i + 1]);
        }
        bool contains = false;
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
        for (int i = 0; i < n; i++) {
            cout << mx[i] << ' ';
        }
        cout << '\n';
        for (int val : ind) {
            cout << val << ' ';
        }
        cout << '\n';
        for (int i = 0; i + 1 < n; i++) {
            auto it = ind.lower_bound(i);
            if (it == ind.end()) break;
            int from = max(*it, i + 1);
            int pre = i > 0 ? a[i - 1] : 0;
            if (mx[from] - pre > 0) {
                contains = true;
                break;
            }
        }
        contains |= ind.size() == n;
        cout << (contains ? "yes\n" : "no\n");
    }
}
