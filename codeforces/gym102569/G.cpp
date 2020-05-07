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
 
mt19937 rnd(1423);
const int N = 1000;
int p[N];
map<pair<int,int>, int> cmp;
 
int ask(int a, int b) {
    if (cmp.count({a, b})) {
        return cmp[make_pair(a, b)];
    }
    cout << "? " << a + 1 << ' ' << b + 1 << endl;
    char res;
    cin >> res;
    int cur = 0;
    if (res == '<') {
        cur = -1;
    } else if (res == '>') {
        cur = 1;
    }
    return cmp[make_pair(a, b)] = cur;
}
 
void Solve(vector<int> a, vector<int> b) {
    assert(a.size() == b.size());
    if (a.size() == 0) return;
    if (a.size() == 1) {
        p[a[0]] = b[0];
        return;
    }
    int i1 = rnd() % a.size();
    vector<int> firstHalf, secondHalf;
    int center = -1;
    for (int j = 0; j < b.size(); j++) {
        int res = ask(a[i1], b[j]);
        if (res == 0) {
            center = b[j];
            p[a[i1]] = b[j];
        } else if (res < 0) {
            firstHalf.push_back(b[j]);
        } else {
            secondHalf.push_back(b[j]);
        }
    }
    vector<int> a1, a2;
    for (int i = 0; i < a.size(); i++) {
        if (i == i1) continue;
        int res = ask(a[i], center);
        if (res > 0) {
            a1.push_back(a[i]);
        } else {
            a2.push_back(a[i]);
        }
    }
    Solve(a1, firstHalf);
    Solve(a2, secondHalf);
}
 
int main() {
    InitIO();
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    iota(all(a), 0);
    iota(all(b), 0);
    Solve(a, b);
    cout << "! ";
    for (int i = 0; i < n; i++) {
        cout << p[i] + 1 << ' ';
    }
    cout << endl;
}
