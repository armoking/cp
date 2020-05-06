#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
 
using namespace std;
using ll = long long;
 
void InitIO(std::string name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
 
 
struct Segment {
    int l, r, index;
    Segment(int a = 0, int b = 0, int c = 0)
        : l(a), r(b), index(c)
        {}
    bool operator < (const Segment& o) {
        return tie(l, r, index) < tie(o.l, o.r, o.index);
    }
};
 
struct SegmentTree {
    vector<int> t;
    SegmentTree(int n) : t(n * 4, -1) {}
 
    void update(int v, int tl, int tr, int index, int value) {
        if (tl + 1 == tr) {
            t[v] = value;
        } else {
            int tm = (tl + tr) >> 1;
            if (index < tm) {
                update(v * 2 + 1, tl, tm, index, value);
            } else {
                update(v * 2 + 2, tm, tr, index, value);
            }
            t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
    int find(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l || t[v] < 0) return -1;
        if (tl + 1 == tr) {
            return t[v];
        } else {
            int tm = (tl + tr) >> 1;
            int res = find(v * 2 + 1, tl, tm, l, r);
            if (res == -1) res = find(v * 2 + 2, tm, tr, l, r);
            return res;
        }
    }
};
 
const int N = 200200;
 
int l[N], p[N], r[N], ans[N];
Segment arr[N];
vector<int> rem[N];
 
int main() {
    InitIO();
    int n;
    cin >> n;
 
    set<pair<int,int>> st;
 
    for (int i = 0; i < n; i++) {
        cin >> arr[i].l >> arr[i].r;
        arr[i].index = i;
        arr[i].l--;
        arr[i].r--;
 
        l[i] = arr[i].l;
        r[i] = arr[i].r;
        rem[r[i]].push_back(i);
    }
    sort(arr, arr + n);
 
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < n && arr[j].l == i) {
            st.insert({arr[j].r, arr[j].index});
            j++;
        }
        auto [rightBorder, index] = *st.begin();
        st.erase(st.begin());
        ans[index] = i;
        p[i] = index;
    }
 
    int first = -1;
    int second = -1;
    SegmentTree tree(n);
 
    for (int i = 0; i < n; i++) {
        int index = tree.find(0, 0, n, l[p[i]], i);
 
        if (index != -1) {
            first = index;
            second = p[i];
            break;
        }
        for (int ind : rem[i]) {
            tree.update(0, 0, n, ans[ind], -1);
        }
        if (r[p[i]] != i) {
            tree.update(0, 0, n, i, p[i]);
        }
    }
 
    if (first == -1) {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "NO\n";
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << ' ';
        }
        cout << '\n';
 
        swap(ans[first], ans[second]);
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << ' ';
        }
        cout << '\n';
    }
}
