#include <bits/stdc++.h>
#define all(x) begin(x),end(x)

using namespace std;
using ll = long long;
template<typename T> int size(T& x) {
    return x.size();
}

template<typename TData, typename RMQ, typename Edge, bool EDGES = false>
class THld {
private:
    int n;
    vector<vector<Edge>>& g;
    vector<int> parent;
    vector<int> indexOfWay;
    vector<int> indexInPath;
    vector<int> path;
    vector<int> beginOfWay;
    vector<int> depth;
    RMQ rmq;

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
                if (edge.to == parent[0][i]) {
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
    THld(vector<vector<Edge>>& g, int root = 0)
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
        rmq = RMQ(GetData());
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
            answer = RMQ::UpdateValue(answer, rmq.Get(indexInPath[Head(a)], indexInPath[a]));
            a = parent[Head(a)];
        }
        if (depth[a] < depth[b]) swap(a, b);
        answer = RMQ::UpdateValue(answer, rmq.Get(indexInPath[b] + EDGES, indexInPath[a]));
        return answer;
    }

    TData Get(int v) {
        return rmq.Get(indexInPath[v]);
    }
};

struct Edge {
    int to;
};

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(const vector<int>& data = {})
        : n(data.size())
        , t(n * 2, 0)
    {}

    void Update(int v, int val) {
        for (t[v += n] += val; v > 1; v >>= 1) {
            t[v >> 1] = UpdateValue(t[v], t[v ^ 1]);
        }
    }

    int Get(int l, int r) {
        int ans = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = UpdateValue(ans, t[l++]);
            if (r & 1) ans = UpdateValue(ans, t[--r]);
        }
        return ans;
    }

    static int UpdateValue(int a, int b) {
        return max(a, b);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < n - 1; i++) {
        int f, t;
        cin >> f >> t;
        f--, t--;
        graph[f].push_back(Edge{t});
        graph[t].push_back(Edge{f});
    }
    THld<int, SegmentTree, Edge> hld(graph, 0);
    int q;
    cin >> q;
    while (q--) {
        char type;
        int a, b;
        cin >> type >> a >> b;
        if (type == 'I') {
            hld.Update(a - 1, b);
        } else {
            cout << hld.Get(a - 1, b - 1) << '\n';
        }
    }
}
