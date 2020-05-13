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

void setmin(int& a, int b) {
    if (a > b) a = b;
}
void setmax(int& a, int b) {
    if (a < b) a = b;
}


int main() {
    InitIO();
    vector<int> arr(4);
    for (int& val : arr) cin >> val;
    sort(all(arr));
    int a = arr[0];
    int b = arr[1];
    int c = arr[2];
    int d = arr[3];
    if (b - a == d - c && d - b == c - a) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
