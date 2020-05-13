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
