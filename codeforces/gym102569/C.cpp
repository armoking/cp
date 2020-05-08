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
 
const int N = 100000;
const int inf = 4e8 + 1;
 
int ny, n;
int x[N], y[N], ys[N], t[N];
pair<int,int> arr[N];
 
void add(int i, int val) {
    while (i < ny) {
        t[i] += val;
        i = ((i + 1) | i);
    }
}
 
int get(int i) {
    ll ans = 0;
    while (i >= 0) {
        ans += t[i];
        i = ((i + 1) & i) - 1;
    }
    return ans;
}
 
int get(int l, int r) {
    return get(r) - get(l - 1);
}
 
ll Count(int dist) {
    fill(t, t + ny, 0);
    ll ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j <= i && x[i] - x[j] > dist) {
            add(lower_bound(ys, ys + ny, y[j]) - ys, -1);
            j++;
        }
 
        int from = lower_bound(ys, ys + ny, y[i] - dist) - ys;
        int to = upper_bound(ys, ys + ny, y[i] + dist) - ys - 1;
 
        ans += get(from, to);
 
        add(lower_bound(ys, ys + ny, y[i]) - ys, 1);
    }
 
    return ans;
}
 
int main() {
    InitIO();
    ll k;
    cin >> n >> k;
 
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
        auto [tmpx, tmpy] = arr[i];
        x[i] = tmpx - tmpy + 2e8;
        y[i] = tmpx + tmpy + 2e8;
        arr[i] = {x[i], y[i]};
        ys[i] = y[i];
    }
 
    sort(ys, ys + n);
    ny = unique(ys, ys + n) - ys;
 
    sort(arr, arr + n);
    for (int i = 0; i < n; i++) {
        x[i] = arr[i].first;
        y[i] = arr[i].second;
    }
 
    int left = 0;
    int right = inf;
    int mid;
    int ans = inf;
 
    while (left <= right) {
        mid = (left + right) >> 1;
        if (Count(mid) >= k) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    cout << ans << endl;
}
