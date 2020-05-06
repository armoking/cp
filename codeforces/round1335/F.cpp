#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1000001;
 
char c[N];
char s[N];
int dist[N];
int inCycle[N];
int color[N];
int mp[N];
int n, m;
int64_t buffer[N];
 
inline int dir(char ch) {
  if (ch == 'U') return -m;
  if (ch == 'D') return m;
  if (ch == 'L') return -1;
  return 1;
}
 
unordered_set<int64_t> used;
 
 
int Dfs(int from) {
  color[from] = 1;
  int nxt = from + dir(s[from]);
  int ans = -1;
  if (color[nxt] == 1) {
    dist[from] = 1;
    inCycle[from] = nxt;
    ans = nxt;
  } else {
    int res = color[nxt] ? -1 : Dfs(nxt);
    if (res == -1) {
      dist[from] = dist[nxt] + 1;
      inCycle[from] = inCycle[nxt] >= 0 ? - 1 - inCycle[nxt] : inCycle[nxt];
      ans = -1;
    } else if (res == from) {
      dist[from] = 0;
      inCycle[from] = res;
      ans = -1;
    } else {
      dist[from] = dist[nxt] + 1;
      inCycle[from] = res;
      ans = res;
    }
  }
  color[from] = 2;
  return ans;
}
 
void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> (&c[i * m]);
  }
  for (int i = 0; i < n; i++) {
    cin >> (&s[i * m]);
  }
 
  memset(dist, 0, sizeof(int) * n * m);
  memset(inCycle, 0, sizeof(int) * n * m);
  memset(color, 0, sizeof(int) * n * m);
  memset(mp, 0, sizeof(int) * n * m);
 
  for (int i = 0; i < n * m; i++) {
    if (color[i] == 0) {
      Dfs(i);
    }
    if (inCycle[i] >= 0) {
      mp[inCycle[i]]++;
    }
  }
 
  int ans1 = accumulate(mp, mp + n * m, 0);
  int ans2 = 0;
  int itr = 0;
  for (int i = 0; i < n * m; i++) {
    if (c[i] == '0') {
      int currentCycle = inCycle[i] >= 0 ? inCycle[i] : -inCycle[i] - 1;
      int currentDistance = dist[i] % mp[currentCycle];
      int64_t curBlackCell = currentCycle * 1ll * N + currentDistance;
      auto it = used.insert(curBlackCell);
      if (it.second) {
        buffer[itr++] = curBlackCell;
        ans2++;
      }
    }
  }
  for (int i = 0; i < itr; i++) {
    used.erase(buffer[i]);
  }
 
  cout << ans1 << ' ' << ans2 << '\n';
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  used.reserve(N * 8);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
