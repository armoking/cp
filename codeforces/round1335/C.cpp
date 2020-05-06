#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      arr[x - 1]++;
    }
    int a = *max_element(begin(arr), end(arr));
    int b = 0;
    for (int i = 0; i < n; i++) {
      b += arr[i] > 0;
    }
    if (b == a) {
      cout << a - 1 << endl;
    } else {
      cout << min(a, b) << endl;
    }
 
  }
}
