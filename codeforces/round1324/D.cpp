#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] -= x;
    }
    sort(begin(a), end(a), greater<>());
    long long answer = 0;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        int left = i;
        int right = n - 1;
        int mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (a[mid] + a[i] > 0) {
                cur = mid - i;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        answer += cur;
    }
    cout << answer << endl;
}
