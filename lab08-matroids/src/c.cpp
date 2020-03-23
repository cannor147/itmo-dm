#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class bipartial_graph {

private:
    vector<vector<size_t>> right, left;
    bool dfs_kunh(size_t i, vector<size_t> &colors, vector<size_t> &matching) {
        if (colors[i] == 0) {
            colors[i] = 1;
            for (auto j : right[i]) {
                if (matching[j] == SIZE_MAX || dfs_kunh(matching[j], colors, matching)) {
                    matching[j] = i;
                    return true;
                }
            }
        }
        return false;
    }

public:
    bipartial_graph(size_t n, size_t m) {
        right.resize(n);
        left.resize(m);
    }
    void add_edge(size_t i, size_t j) {
        right[i].push_back(j);
        left[j].push_back(i);
    }
    size_t lsize() {
        return left.size();
    }
    size_t rsize() {
        return right.size();
    }

    vector<pair<size_t, size_t>> find_maximum_matching() {
        vector<size_t> matching(lsize(), SIZE_MAX);
        for (size_t i = 0; i < rsize(); i++) {
            vector<size_t> colors(rsize(), 0);
            dfs_kunh(i, colors, matching);
        }
        vector<pair<size_t, size_t>> result;
        for (size_t i = 0; i < lsize(); i++) {
            if (matching[i] != SIZE_MAX) {
                result.push_back({i, matching[i]});
            }
        }
        return result;
    }
};

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m, a;
    cin >> n;
    vector<pair<pair<size_t, size_t>, vector<size_t>>> kek;
    for (size_t i = 0; i < n; i++) {
        cin >> a;
        kek.push_back({{a, i}, vector<size_t>()});
    }
    bipartial_graph g(n, n);
    for (size_t i = 0; i < n; i++) {
        cin >> m;
        for (size_t j = 0; j < m; j++) {
            cin >> a;
            kek[i].second.push_back(a - 1);
        }
    }
    sort(kek.rbegin(), kek.rend());
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < kek[i].second.size(); j++) {
            g.add_edge(i, kek[i].second[j]);
        }
    }
    auto max_match = g.find_maximum_matching();
    vector<size_t> result(n, 0);
    for (auto &p : max_match) {
        result[kek[p.second].first.second] = p.first + 1;
    }
    for (size_t i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    return 0;
}