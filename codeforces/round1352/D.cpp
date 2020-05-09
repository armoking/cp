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
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];
        int apre = 0;
        int bpre = 0;
        int a = 0;
        int b = 0;
        int i = 0;
        int j = n - 1;
        vector<bool> used(n, false);
        int ans = 0;
        while (i < n && !used[i] || j >= 0 && !used[j]) {
            apre = 0;
            while (i < n && !used[i] && apre <= bpre) {
                apre += arr[i];
                a += arr[i];
                used[i] = true;
                i++;
            }
            ans += apre > 0;

            bpre = 0;
            while (j >= 0 && !used[j] && bpre <= apre) {
                bpre += arr[j];
                b += arr[j];
                used[j] = true;
                j--;
            }
            ans += bpre > 0;
        }
        cout << ans << ' ' << a << ' ' << b << '\n';
    }
}
