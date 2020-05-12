#include <bits/stdc++.h>

using namespace std;

int dp[2][2020];
int a[2020];
void setmax(int& a, int b) {
    if (a < b) a = b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, h, l, r;
    cin >> n >> h >> l >> r;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    fill(dp[1], dp[1] + 2020, -2020);
    dp[1][0] = 0;
    for (int i = 0; i < n; i++) {
        fill(dp[i & 1], dp[i & 1] + 2020, -2020);
        for (int cur = 0; cur < h; cur++) {
            for (int dlt = -1; dlt < 1; dlt++) {
                int pre = (h + h + cur - (a[i] + dlt)) % h;
                if (cur >= l && cur <= r) {
                    setmax(dp[i&1][cur], dp[(i + 1) & 1][pre] + 1);
                } else {
                    setmax(dp[i&1][cur], dp[(i + 1) & 1][pre]);
                }
            }
        }
    }
    for (int i = 0; i < h; i++) {
        setmax(ans, dp[(n - 1) & 1][i]);
    }
    cout << ans << '\n';
}
