#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n = 9;
    int m = 9;
    vector<string> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    vector<int> p = {0, 4, 8, 1, 3, 7, 2, 5, 6};
    for (int i = 0; i < n; i++) {
      int j = p[i];
      arr[i][j] = ((arr[i][j] - '1' + 1) % 9) + '1';
    }
    for (string s : arr) {
      cout << s << '\n';
    }
  }
}
