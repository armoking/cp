#include <bits/stdc++.h>
#define all(x) begin(x),end(x)

void InitIO(std::string name = "") {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (name.size()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

using namespace std;

void setmax(string& a, const string& b) {
    if (a < b) a = b;
}

int main() {
    InitIO("");
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int val = 0;
        for (int j = 0; j < 7; j++) {
            val += (s[j] - '0') << j;
        }
        arr[i] = val;
    }
    vector<int> digits;
    vector<string> ds = {
        "1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"
    };
    for (int i = 0; i < 10; i++) {
        int val = 0;
        for (int j = 0; j < 7; j++) {
            val  += (ds[i][j] - '0') << j;
        }
        digits.push_back(val);
    }

#define sz(x) __builtin_popcount(x)

    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));
    vector<vector<pair<int,int>>> from(n + 1, vector<pair<int,int>>(k + 1, {-1, -1}));
    dp[0][k] = true;

    reverse(all(arr));


    for (int i = 0; i < n; i++) {
        int ni = i + 1;
        for (int rem = 0; rem <= k; rem++) {
            for (int j = 0; j < 10; j++) {
                if ((digits[j] | arr[i]) == digits[j]) {
                    int dlt = sz(digits[j]) - sz(arr[i]);
                    if (dlt > rem) continue;
                    if (dp[i][rem] && from[ni][rem - dlt].first <= j) {
                        dp[ni][rem - dlt] = true;
                        from[ni][rem - dlt] = {j, rem};
                    }
                }
            }
        }
    }
    string result = "";
    if (!dp[n][0]) {
        result = "-1";
    } else {
        int x = n;
        int y = 0;
        while (x > 0) {
            auto [dig, pre] = from[x][y];
            result += char(dig + '0');
            y = pre;
            x--;
        }
    }
    cout << result << endl;
}
