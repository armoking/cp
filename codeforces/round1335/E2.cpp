#include <bits/stdc++.h>
 
using namespace std;
 
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<array<int, 201>> arr(n);
  for (int i = 0; i < n; i++) {
    fill(begin(arr[i]), end(arr[i]), 0);
    if (i) arr[i] = arr[i - 1];
    arr[i][a[i]]++;
  }
  int ans = *max_element(arr.back().begin(), arr.back().end());
  for (int i = 0; i < n; i++) {
    int cur = a[i];
    int prefix = arr[i][cur];
    int total = arr.back()[cur];
    if (total < prefix * 2) continue;
    int left = 0;
    int right = n - 1;
    int mid;
    int suffix = i + 1;
    while (left <= right) {
      mid = (left + right) / 2;
      if (total - arr[mid][cur] >= prefix) {
        suffix = mid + 1;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    int from = i + 1;
    int to = suffix - 1;
    int mx = 0;
    for (int j = 1; j <= 200; j++) {
      if (j == cur) continue;
      mx = max(mx, arr[to][j] - arr[i][j]);
    }
    ans = max(ans, prefix * 2 + mx);
  }
  cout << ans << '\n';
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
