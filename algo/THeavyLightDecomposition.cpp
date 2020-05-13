template<typename TData, typename RMQ, typename Edge, bool EDGES = false>
class THld {
private:
    int n;
    vector<vector<Edge>>& g;
    vector<vector<int>> parent;
    vector<int> indexOfWay;
    vector<int> indexInPath;
    vector<int> path;
    vector<int> beginOfPath;
    vector<int> depth;
    vector<int> tin;
    vector<int> tout;
    int timer = 0;
    RMQ rmq;

    int BuildDfs(int from, int par, int d = 0) {
        parent[0][from] = par;
        tin[from] = timer++;
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
        tout[from] = timer++;
        return tsize;
    }

    void BuildWays(int from, int& index) {
        indexOfWay[from] = index;
        if (beginOfPath[index] == -1) {
            beginOfPath[index] = from;
        }
        indexInPath[from] = path.size();
        path.push_back(from);
        if (g[from].size() == 0 || (g[from].size() == 1 && g[from][0].to == parent[0][from])) {
            index++;
            return;
        }
        for (int i = 0; i < int(g[from].size()); i++) {
            if (g[from][i].to == parent[0][from]) {
                continue;
            }
            BuildWays(g[from][i].to, index);
        }
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

public:
    THld(vector<vector<Edge>>& g, int root = 0)
        : n(g.size())
        , g(g)
        , parent(int(log2(n) + 1), vector<int>(n))
        , indexOfWay(n, -1)
        , indexInPath(n, -1)
        , beginOfPath(n, -1)
        , depth(n, 1)
        , tin(n)
        , tout(n)
    {
        BuildDfs(root, root);
        int index = 0;
        BuildWays(root, index);
        rmq = RMQ(GetData());
    }

    void Update(int a, int b, TData value) {
        int c = LCA(a, b);

        while (indexOfWay[a] != indexOfWay[c]) {
            int head = beginOfPath[indexOfWay[a]];
            rmq.Update(indexInPath[head], indexInPath[a], value);
            a = parent[0][head];
        }
        rmq.Update(indexInPath[c] + 1, indexInPath[a], value);

        while (indexOfWay[b] != indexOfWay[c]) {
            int head = beginOfPath[indexOfWay[b]];
            rmq.Update(indexInPath[head], indexInPath[b], value);
            b = parent[0][head];
        }
        rmq.Update(indexInPath[c] + EDGES, indexInPath[b], value);
    }

    void Update(int v, TData value) {
        rmq.Update(indexInPath[v], value);
    }

    TData Get(int a, int b) {
        TData answer = 0;
        int c = LCA(a, b);

        while (indexOfWay[a] != indexOfWay[c]) {
            int head = beginOfPath[indexOfWay[a]];
            answer = RMQ::UpdateValue(answer, rmq.Get(indexInPath[head], indexInPath[a]));
            a = parent[0][head];
        }
        answer = RMQ::UpdateValue(answer, rmq.Get(indexInPath[c] + 1, indexInPath[a]));

        while (indexOfWay[b] != indexOfWay[c]) {
            int head = beginOfPath[indexOfWay[b]];
            answer = RMQ::UpdateValue(answer, rmq.Get(indexInPath[head], indexInPath[b]));
            b = parent[0][head];
        }
        answer = RMQ::UpdateValue(answer, rmq.Get(indexInPath[c] + EDGES, indexInPath[b]));

        return answer;
    }

    TData Get(int v) {
        return rmq.Get(indexInPath[v]);
    }

    int LCA(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        if (tin[a] >= tin[b] && tout[a] <= tout[b]) {
            return b;
        }
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
};
