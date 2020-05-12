#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(all(arr));
    arr.erase(unique(all(arr)), end(arr));
    n = arr.size();
    
    vector<int> primes;
    vector<bool> r(200200);
    for (int i = 2; i < 200200; i++) {
        if (r[i]) continue;
        primes.push_back(i);
        for (int j = i + i; j < 200200; j += i) {
            r[j] = true;
        }
    }
    vector<vector<int>> deg(200200);
    for (int i = 0; i < n; i++) {
        for (int val : primes) {
            if (1ll * val * val > arr[i]) break;
            if (arr[i] % val) continue;
            int itr = 0;
            while (arr[i] % val == 0) {
                itr++;
                arr[i] /= val;
            }    
            deg[val].push_back(itr);
        }
        if (arr[i] > 1) {
            deg[arr[i]].push_back(1);
        }
    } 
    ll ans = 1;
    for (int i = 2; i < 200200; i++) {
        if (deg[i].size() <= n - 2) continue;
        while (deg[i].size() < n) deg[i].push_back(0);
        sort(all(deg[i]));
        int a = deg[i][0];
        int b = deg[i][1];
        ans *= pow(i, b);
    }
    cout << ans << endl;
}
