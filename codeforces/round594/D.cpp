#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
const int N = 200200;

ll a[N];
ll pref[N];
ll revpref[N];
ll rev[int(1e6) + 1];

ll fastPow(ll a, ll p) {
    ll ans = 1;
    while (p) {
        if (p & 1) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        p >>= 1;
    }
    return ans;
}

struct SegmentTree { 
    vector<vector<pair<int,ll>>> t;
    vector<vector<ll>> pref;
    SegmentTree(int n, vector<vector<int>> data) : t(n * 4), pref(n * 4) {
        vector<pair<int, int>> arr;
        map<int,int> mp;
        vector<int> from(n);
        vector<int> to(n);
        for (int i = 0; i < n; i++) {
            from[i] = arr.size();
            for (int val : data[i]) {
                arr.push_back({i, val});
            }
            to[i] = arr.size();
        }
        for (auto& [ind, val] : arr) {
            mp[val] = -1;
        }

        vector<pair<int,int>> build;
        for (auto& [ind, val] : arr) {
            build.push_back({mp[val], val});
            mp[val] = ind;
        }
        for (int i = 0; i < n; i++) {
            sort(build.begin() + from[i], build.begin() + to[i]);
        }
        Build(0, 0, n, build, from, to);
    }

    void Build(int v, int tl, int tr, vector<pair<int,int>>& arr, vector<int>& from, vector<int>& to) {
        if (tl + 1 == tr) {
            t[v].reserve(to[tl] - from[tl]);
            for (int i = from[tl]; i < to[tl]; i++) {
                t[v].push_back(arr[i]);
            }
        } else {
            int tm = (tl + tr) / 2;
            Build(v * 2 + 1, tl, tm, arr, from, to);
            Build(v * 2 + 2, tm, tr, arr, from, to);
            merge(all(t[v * 2 + 1]), all(t[v * 2 + 2]), back_inserter(t[v]));
            while (t[v].back().first > tl) t[v].pop_back(); 
            t[v].shrink_to_fit();
        }
        pref[v].resize(t[v].size());
        for (int i = 0; i < t[v].size(); i++) {
            pref[v][i] = (1 + mod - rev[t[v][i].second]) % mod;
            if (i) {
                pref[v][i] = (pref[v][i] * pref[v][i - 1]) % mod;
            }
        }
    }
    
    ll Get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 1;
        if (tl >= l && tr <= r) {
            int left = 0;
            int right = t[v].size() - 1;
            int mid;
            int cur = -1;
            while (left <= right) {
                mid = (left + right) >> 1;
                if (t[v][mid].first < l) {
                    cur = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            if (cur == -1) return 1;
            return pref[v][cur];
        } else {
            int tm = (tl + tr) / 2;
            return Get(v * 2 + 1, tl, tm, l, r) * Get(v * 2 + 2, tm, tr, l, r) % mod;
        }
    }

};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= 1e6; i++) {
        rev[i] = fastPow(i, mod - 2);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = a[i];
        revpref[i] = fastPow(a[i], mod - 2);
        if (i) {
            pref[i] = (pref[i - 1] * pref[i]) % mod;
            revpref[i] = (revpref[i - 1] * revpref[i]) % mod;
        }
    }
    
    vector<ll> primes;
    vector<bool> eq(int(1e6 + 1));
    for (int i = 2; i <= 1e6; i++) {
        if (eq[i]) continue;
        primes.push_back(i);
        for (int j = i + i; j <= 1e6; j += i) {
            eq[j] = true;
        }
    }

    int q;
    cin >> q;
    vector<pair<int,int>> queries;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries.push_back({l, r});
    }
    
    vector<vector<int>> data(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < primes.size(); j++) {
            if (primes[j] * primes[j] > a[i]) {
                break;
            }
            if (a[i] % primes[j]) continue;
            data[i].push_back(primes[j]);
            while (a[i] % primes[j] == 0) {
                a[i] /= primes[j];    
            }
        }    
        if (a[i] > 1) {
            data[i].push_back(a[i]);
        }
    }
    SegmentTree tree(n, data);
    
    vector<ll> ans(q);
    for (int i = 0; i < q; i++) {
        auto& [l, r] = queries[i];
        ans[i] = pref[r] * (l ? revpref[l - 1] : 1) % mod;
        
        ll value = tree.Get(0, 0, n, l, r + 1);
        ans[i] = (ans[i] * value) % mod;
        cout << ans[i] << '\n';
    }
    
}
