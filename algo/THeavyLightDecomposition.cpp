template<typename TData, typename RMQ, typename Edge>
class THld {
private:
    int n;
    vector<vector<Edge>>& g;
    vector<vector<int>> parent;
    vector<int> indexOfWay;
    vector<int> indexInPath;
    vector<int> path, beginPath, endPath;
    vector<int> depth;
    RMQ rmq;


    int BuildDfs(int from, int par, int d = 0) {
        parent[0][from] = par;
        for (int i = 1; i < int(parent.size()); i++) {
            parent[i][from] = parent[i - 1][parent[i - 1][from]];
        }
        depth[from] = d;
        int tsize = 1;
        int child = -1;
        int maxSize = 0;
        for (int i = 0; i < int(g[from].size()); i++) {
            if (g[from][i].to == par) {
                continue;
            }
            int currentSize = BuildDfs(g[from][i].to, from, d + 1);
            tsize += currentSize;
            if (maxSize < currentSize) {
                maxSize = currentSize;
                child = i;
            }
        }
        if (child != -1) {
            swap(g[from][0], g[from][child]);
        }
        return tsize;
    }

    void BuildWays(int from, int& index) {
        indexOfWay[from] = index;
        while (index >= int(beginPath.size())) {
            beginPath.push_back(-1);
            endPath.push_back(-1);
        }
        if (beginPath[index] == -1) {
            beginPath[index] = path.size();
        }
        indexInPath[from] = path.size();
        path.push_back(from);
        endPath[index] = path.size();
        if (g[from].size() == 0 || (g[from].size() == 1 && g[from][0].to == parent[0][from])) {
            index++;
            return;
        }
        for (int i = 0; i < int(g[from].size()); i++) {
            if (g[from][i].to == parent[0][from]) {
                continue;
            }
            BuildWays(g[from][i].to, index);
            index++;
        }
    }

    vector<TData> GetData() {
        const int n = g.size();
        vector<TData> data;
        for (int i = 0; i < n; i++) {
            TData cur = 0;
            // it may be data in vertexes or weights of edges
            for (int j = 0; j < int(g[i].size()); j++) {
                if (g[i][j].to == parent[0][i]) {
                    cur = g[i][j].w;
                }
            }
            data.push_back(cur);
        }
        return data;
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        for (int i = int(size(parent)) - 1; i >= 0; i--) {
            if (depth[parent[i][a]] >= depth[b]) {
                a = parent[i][a];
            }
        }
        if (a == b) return a;
        for (int i = int(size(parent)) - 1; i >= 0; i--) {
            if (parent[i][a] != parent[i][b]) {
                a = parent[i][a];
                b = parent[i][b];
            }
        }
        return parent[0][a];
    }

public:
    THld(vector<vector<Edge>>& g, int root = 0)
        : n(g.size())
        , g(g)
        , parent(int(log2(n) + 1), vector<int>(n))
        , indexOfWay(n, -1)
        , indexInPath(n, -1)
        , beginPath(1, -1)
        , endPath(1, -1)
        , depth(n, 1)
    {
        BuildDfs(root, root);
        int index = 0;
        BuildWays(root, index);
        rmq = RMQ(GetData());
    }

    void Update(int a, int b, TData value) {
        int c = lca(a, b);

        while (indexOfWay[a] != indexOfWay[c]) {
            int head = beginPath[indexOfWay[a]];
            rmq.Update(head, indexInPath[a], value);
            a = parent[0][head];
        }
        // or indexInPath[c] + 0
        rmq.Update(indexInPath[c] + 1, indexInPath[a], value);
        while (indexOfWay[b] != indexOfWay[b]) {
            int head = beginPath[indexOfWay[b]];
            rmq.Update(head, indexInPath[b], value);
            b = parent[0][head];
        }
        rmq.Update(indexInPath[c] + 1, indexInPath[b], value);
    }

    void Update(int v, TData value) {
        rmq.Update(indexInPath[v], value); // or Update(v, v, value)
    }

    TData Get(int a, int b) {
        TData answer = 0;
        int c = lca(a, b);

        while (indexOfWay[a] != indexOfWay[c]) {
            int head = beginPath[indexOfWay[a]];
            answer = RMQ::UpdateValue(answer, rmq.Get(head, indexInPath[a]));
            a = parent[0][head];
        }
        answer = RMQ::UpdateValue(answer, rmq.Get(indexInPath[c] + 1, indexInPath[a]));

        while (indexOfWay[b] != indexOfWay[b]) {
            int head = beginPath[indexOfWay[b]];
            answer = RMQ::UpdateValue(answer, rmq.Get(head, indexInPath[b]));
            b = parent[0][head];
        }
        // or indexInPath[c] + 0
        answer = RMQ::UpdateValue(answer, rmq.Get(indexInPath[c] + 1, indexInPath[b]));
        return answer;
    }

    TData Get(int v) {
        return rmq.Get(indexInPath[v]);
    }
};

/*
struct Edge {
    int to, w;
};

struct FenwickTree {
    int n;
    vector<int> t;
    FenwickTree(const vector<int>& data = {}) : n(data.size()), t(n) {
        for (int i = 0; i < n; i++) {
            Update(i, data[i]);
        }
    }
    int GetBorder(int r) {
        int ans = 0;
        while (r >= 0) {
            ans += t[r];
            r = ((r + 1) & r) - 1;
        }
        return ans;
    }

    int Get(int l, int r) {
        return GetBorder(r) - GetBorder(l - 1);
    }

    int Get(int index) {
        return Get(index, index - 1);
    }

    void Update(int index, int value) {
        while (index < n) {
            t[index] += value;
            index = (index | (index + 1));
        }
    }

    void Update(int l, int r, int value) {
        for (int i = l; i <= r; i++) {
            Update(i, value);
        }
    }

    static int UpdateValue(int a, int b) {
        return a + b;
    }

};

int main() {
    const int n = 5;
    vector<vector<Edge>> g(n);

    g[1].push_back(Edge{0, 1});
    g[2].push_back(Edge{1, 1});
    g[3].push_back(Edge{2, 1});
    g[4].push_back(Edge{3, 1});


    g[0].push_back(Edge{1, 1});
    g[1].push_back(Edge{2, 1});
    g[2].push_back(Edge{3, 1});
    g[3].push_back(Edge{4, 1});

    THld<int, FenwickTree, Edge> hld(g);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << i << ' ' << j  << ' ' << hld.Get(i, j) << endl;
        }
    }

}
*/
