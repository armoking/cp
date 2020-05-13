#include <bits/stdc++.h>
#define all(x) begin(x),end(x)
#define size(x) int(x.size())

using namespace std;
using ll = long long;

template<typename TKey, typename TValue, int TABLE_SIZE = 1024 /* should be power of two */,
         int MAXN = 1024 /* max amount of elements */, TValue VALUE_BY_DEFAULT = 0>
class THashMap {
private:
    std::pair<TKey, TValue> buffer[MAXN];
    std::list<int> table[TABLE_SIZE];
    std::vector<int> indexes;

    int GetHash(const TKey& key) const {
        return (key ^ (key << 5) ^ (key >> 7)) & (TABLE_SIZE - 1);
    }

    int GetFreeIndex() {
        int index = indexes.back();
        indexes.pop_back();
        return index;
    }
public:
    THashMap()
        : indexes(MAXN)
    {
        std::iota(std::begin(indexes), std::end(indexes), 0);
        for (int i = 0; i < MAXN; i++) {
            buffer[i].second = VALUE_BY_DEFAULT;
        }
    }

    bool contains(const TKey& key) const {
        int h = GetHash(key);
        for (int index : table[h]) {
            if (buffer[index].first == key) {
                return true;
            }
        }
        return false;
    }

    TValue& operator [] (const TKey& key) {
        int h = GetHash(key);
        for (int index : table[h]) {
            if (buffer[index].first == key) {
                return buffer[index].second;
            }
        }
        int index = GetFreeIndex();
        buffer[index].first = key;
        table[h].push_back(index);
        return buffer[index].second;
    }

    void put(const TKey& key, const TValue& value) {
        (*this)[key] = value;
    }

    bool erase(const TKey& key) {
        int h = GetHash(key);
        auto it = std::begin(table[h]);
        while (it != std::end(table[h])) {
            if (buffer[*it].first == key) {
                buffer[*it].second = VALUE_BY_DEFAULT;
                indexes.push_back(*it);
                table[h].erase(it);
                return true;
            }
        }
        return false;
    }

    bool insert(const TKey& key, const TValue& value) {
        int h = GetHash(key);
        for (int index : table[h]) {
            if (buffer[index].first == key) {
                if (buffer[index].second == value) {
                    return false;
                } else {
                    buffer[index].second = value;
                    return true;
                }
            }
        }
        int index = GetFreeIndex();
        buffer[index].first = key;
        buffer[index].second = value;
        table[h].push_back(index);
        return true;
    }

    std::vector<std::pair<TKey, TValue>> data() const {
        std::vector<std::pair<TKey, TValue>> result;
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (int index : table[i]) {
                result.push_back(buffer[index]);
            }
        }
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    THashMap<int, int, 1 << 8, 8 << 10> hashMap;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        auto pref = a;
        for (int i = 1; i < n; i++) {
            pref[i] += pref[i - 1];
        }

        auto sum = [&] (int l, int r) {
            return pref[r] - (l > 0 ? pref[l - 1] : 0);
        };

        int ans = 0;
        for (int i = 0; i < n; i++) {
            hashMap[a[i]]++;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int cur = sum(i, j);
                if (cur <= n && hashMap.contains(cur)) {
                    auto& val = hashMap[cur];
                    ans += val;
                    val = 0;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            hashMap.erase(a[i]);
        }

        cout << ans << '\n';
    }

}
