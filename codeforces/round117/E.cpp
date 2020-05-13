#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

template<typename TData, typename TRMQ, typename TEdge, bool EDGES = false>
class THLD {
private:
    int n;
    vector<vector<TEdge>>& g;
    vector<int> parent;
    vector<int> indexOfWay;
    vector<int> indexInPath;
    vector<int> path;
    vector<int> beginOfWay;
    vector<int> depth;
    TRMQ rmq;

    int BuildDfs(int from, int par, int d = 0) {
        depth[from] = d;
        parent[from] = par;
        int tsize = 1;
        int child = -1;
        int maxSize = 0;
        for (int i = 0; i < int(g[from].size()); i++) {
            if (g[from][i].to != par) {
                int currentSize = BuildDfs(g[from][i].to, from, d + 1);
                tsize += currentSize;
                if (maxSize < currentSize) {
                    maxSize = currentSize;
                    child = i;
                }
            }
        }
        if (child != -1) {
            swap(g[from][0], g[from][child]);
        }
        return tsize;
    }

    void BuildWays(int from, int& index) {
        indexOfWay[from] = index;
        if (beginOfWay[index] == -1) {
            beginOfWay[index] = from;
        }
        indexInPath[from] = path.size();
        path.push_back(from);
        bool leaf = true;
        for (int i = 0; i < int(g[from].size()); i++) {
            if (g[from][i].to != parent[from]) {
                BuildWays(g[from][i].to, index);
                leaf = false;
            }
        }
        index += leaf;
    }

    vector<TData> GetData() {
#if EDGES
        vector<TData> data(n);
        for (int i = 0; i < n; i++) {
            for (auto& edge : g[i]) {
                if (edge.to == parent[i]) {
                    data[i] = edge.w;
                }
            }
        }
        return data;
#else
        return vector<TData>(n, 0);
#endif
    }

    int Head(int v) {
        return beginOfWay[indexOfWay[v]];
    }

public:
    THLD(vector<vector<TEdge>>& g, int root = 0)
        : n(g.size())
        , g(g)
        , parent(n)
        , indexOfWay(n)
        , indexInPath(n)
        , beginOfWay(n, -1)
        , depth(n)
    {
        BuildDfs(root, root);
        int index = 0;
        BuildWays(root, index);
        rmq = TRMQ(GetData());
    }

    void Update(int a, int b, TData value) {
        while (indexOfWay[a] != indexOfWay[b]) {
            if (depth[Head(a)] < depth[Head(b)]) swap(a, b);
            rmq.Update(indexInPath[Head(a)], indexInPath[a], value);
            a = parent[Head(a)];
        }
        if (depth[a] < depth[b]) swap(a, b);
        rmq.Update(indexInPath[b] + EDGES, indexInPath[a], value);
    }

    void Update(int v, TData value) {
        rmq.Update(indexInPath[v], value);
    }

    TData Get(int a, int b) {
        TData answer = 0;
        while (indexOfWay[a] != indexOfWay[b]) {
            if (depth[Head(a)] < depth[Head(b)]) swap(a, b);
            answer = TRMQ::UpdateValue(answer, rmq.Get(indexInPath[Head(a)], indexInPath[a]));
            a = parent[Head(a)];
        }
        if (depth[a] < depth[b]) swap(a, b);
        answer = TRMQ::UpdateValue(answer, rmq.Get(indexInPath[b] + EDGES, indexInPath[a]));
        return answer;
    }

    TData Get(int v) {
        return rmq.Get(indexInPath[v]);
    }
};


class TSegmentTree {
private:
    int n;
    vector<char> a;
    vector<int> t;
    int delta = 0;

public:
    TSegmentTree(const vector<int>& data = {})
        : n(data.size())
        , a(n * 4)
        , t(n * 4)
    {}

    void Push(int v, int tl, int tr) {
        if (a[v]) {
            if (tl + 1 < tr) {
                a[v * 2 + 1] ^= a[v];
                a[v * 2 + 2] ^= a[v];
            }
            t[v] = tr - tl - t[v];
            a[v] = 0;
        }
    }

    void Update(int v, int tl, int tr, int l, int r) {
        Push(v, tl, tr);
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            delta += tr - tl - t[v] - t[v];
            a[v] = 1;
            Push(v, tl, tr);
        } else {
            int tm = (tl + tr) >> 1;
            Update(v * 2 + 1, tl, tm, l, r);
            Update(v * 2 + 2, tm, tr, l, r);
            t[v] = UpdateValue(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }

    void Update(int l, int r, int val) {
        Update(0, 0, n, l, r + 1);
    }

    int Get(int v) {
        int ans = delta;
        delta = 0;
        return ans;
    }

    static int UpdateValue(int a, int b) {
        return a + b;
    }
};

class TEdge {
public:
    int to, w;
    TEdge(int to, int w)
        : to(to)
        , w(w)
    {}
};


vector<int> color;
vector<int> cycle;
vector<vector<TEdge>> g;

int Dfs (int from, int parent) {
    color[from] = 1;
    for (auto& [to, w] : g[from]) {
        if (to == parent) continue;
        if (color[to] == 1) {
            cycle.push_back(from);
            return to;
        } else if (color[to] == 0) {
            int res = Dfs(to, from);
            if (res == -2 || res == from) {
                if (res == from) {
                    cycle.push_back(from);
                }
                return -2;
            } else if (res >= 0) {
                cycle.push_back(from);
                return res;
            }
        }
    }
    color[from] = 2;
    return -1;
}

void Draw(int from, int parent) {
    color[from] = color[parent];
    for (auto& [to, w] : g[from]) {
        if (color[to] == -1) {
            Draw(to, from);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, tests;
    cin >> n >> tests;
    g.resize(n);
    color.resize(n);

    for (int i = 0; i < n; i++) {
        int f, t;
        cin >> f >> t;
        f--, t--;
        g[f].emplace_back(t, 0);
        g[t].emplace_back(f, 0);
    }

    Dfs(0, 0);

    int m = cycle.size();
    vector<int> arr(n);
    vector<int> ind(n);

    fill(all(color), -1);
    for (int i = 0; i < m; i++) {
        color[cycle[i]] = cycle[i];
        ind[cycle[i]] = i;
    }

    for (int v : cycle) {
        Draw(v, v);
    }

    int a = cycle[0];
    int b = cycle[1];

    for (int i = 0; i < int(size(g[a])); i++) {
        if (g[a][i].to == b) {
            swap(g[a][i], g[a].back());
            g[a].pop_back();
            break;
        }
    }

    for (int i = 0; i < int(size(g[b])); i++) {
        if (g[b][i].to == a) {
            swap(g[b][i], g[b].back());
            g[b].pop_back();
            break;
        }
    }

    THLD<int, TSegmentTree, TEdge, true> hld(g, 0);
    TSegmentTree tree(cycle);

    int answerTrees = 0;
    int answerCycle = 0;

    while (tests--) {
        int from, to;
        cin >> from >> to;
        from--, to--;

        if (color[from] == color[to]) {
            hld.Update(from, to, 0);
            answerTrees += hld.Get(0);
        } else {
            int headFrom = color[from];
            int headTo = color[to];

            bool normal = true;
            int nextVertex = cycle[(ind[headFrom] + 1) % m];
            int prevVertex = cycle[(ind[headFrom] + m - 1) % m];

            int firstLen = abs(ind[headFrom] - ind[headTo]);
            int secondLen = m - firstLen;
            if (secondLen < firstLen) {
                normal = false;
            } else if (secondLen == firstLen) {
                if ((ind[headFrom] < ind[headTo]) ^ (nextVertex < prevVertex)) {
                    normal = false;
                }
            }

            hld.Update(from, headFrom, 0);
            hld.Update(to, headTo, 0);

            int u = ind[headFrom];
            int v = ind[headTo];
            if (u > v) swap(u, v);

            if (normal) {
                tree.Update(u, v - 1, 0);
            } else {
                tree.Update(0, u - 1, 0);
                tree.Update(v, m - 1, 0);
            }

            answerTrees += hld.Get(0);
            answerCycle += tree.Get(0);
        }

        cout << n - answerTrees - min(m - 1, answerCycle) << '\n';
    }

}
