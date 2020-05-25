#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

void InitIO(std::string name = "") {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (name.size()) {
        assert(freopen((name + ".in").c_str(), "r", stdin));
        assert(freopen((name + ".out").c_str(), "w", stdout));
    }
}

using namespace std;
using ll = long long;

vector<int> ans[200200];
int itr = 0;

int main() {
    InitIO();
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    vector<int> c(k);
    for (int i = 0; i < k; i++) cin >> c[i];
    sort(all(arr));
    reverse(all(arr));

    for (int val : arr) {
        int cnt = c[val - 1];
        bool exists = false;
        int left = 0;
        int right = itr;
        int mid;
        int cur = itr;
        while (left <= right) {
            mid = (left + right) / 2;
            if (int(ans[mid].size()) < cnt) {
                cur = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (cur == itr) itr++;
        auto& v = ans[cur];
        v.push_back(val);
    }
    cout << itr << endl;
    for (int i = 0; i < itr; i++) {
        auto& v = ans[i];
        cout << v.size() << ' ';
        for (int value : v) {
            cout << value << ' ';
        }
        cout << '\n';
    }
}
