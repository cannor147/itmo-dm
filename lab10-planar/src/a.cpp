#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cfloat>

using namespace std;

class graph {

private:
    class edge {
    private:
        size_t i, j;
    public:
        edge(size_t i, size_t j) {
            this->i = i;
            this->j = j;
        }
        size_t get_first() {
            return i;
        }
        size_t get_second() {
            return j;
        }
    };
    vector<vector<edge>> matrix;
    bool dfs_bi(size_t i, int color, vector<int> &colors) {
        if (colors[i] == 0) {
            colors[i] = color;
            bool f = true;
            for (auto &e : matrix[i]) {
                f &= dfs_bi(e.get_second(), -color, colors);
                if (!f) break;
            }
            return f;
        } else {
            return colors[i] == color;
        }
    }

public:
    explicit graph(size_t n) {
        matrix = vector<vector<edge>>(n, vector<edge>());
    }
    size_t size() {
        return matrix.size();
    }
    pair<bool, set<size_t>> is_bipartite() {
        vector<int> colors(size(), 0);
        bool result = true;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                result &= dfs_bi(i, 1, colors);
            }
        }
        set<size_t> right;
        if (result) {
            for (size_t i = 0; i < size(); i++) {
                if (colors[i] == 1) right.insert(i);
            }
        }
        return {result, right};
    }
    void add_edge(size_t i, size_t j) {
        matrix[i].emplace_back(i, j);
        matrix[j].emplace_back(j, i);
    }

};

class graph2 {

private:
    size_t count;
    vector<vector<size_t>> matrix;
public:
    explicit graph2(size_t n) {
        matrix = vector<vector<size_t>>(n, vector<size_t>(n, SIZE_MAX));
        count = 0;
    }
    size_t size() {
        return matrix.size();
    }
    void add_edge(size_t i, size_t j) {
        matrix[i][j] = matrix[j][i] = count;
        count++;
    }
    void solve(vector<size_t> &ham) {
        vector<size_t> order(size());
        for (size_t i = 0; i < ham.size(); i++) {
            size_t a = ham[i], b = ham[(i + 1) % ham.size()];
            order[a] = i;
        }
        vector<pair<size_t, size_t>> edges(count);
        for (size_t i = 0; i < size(); i++) {
            for (size_t j = i + 1; j < size(); j++) {
                if (matrix[i][j] == SIZE_MAX) continue;
                size_t a = order[i], b = order[j];
                edges[matrix[i][j]] = {min(a, b), max(a, b)};
            }
        }
        graph e(count);
        for (size_t i = 0; i < count; i++) {
            size_t a1 = edges[i].first, b1 = edges[i].second;
            for (size_t j = i + 1; j < count; j++) {
                size_t a2 = edges[j].first, b2 = edges[j].second;
                if (a1 == a2 || b1 == b2) continue;
                size_t a = max(a1, a2), b = min(b1, b2);
                if (a < b && (((a == a1) && (b == b2)) || ((a == a2) && (b == b1)))) {
//                    cout << a1 << " " << b1 << ", " << a2 << " " << b2 << endl;
                    e.add_edge(i, j);
                }
            }
        }
        auto h = e.is_bipartite();
        if (h.first) {
            cout << "YES" << endl;
            cout.precision(10);
            vector<pair<double, double>> kek(size());
            for (size_t i = 0; i < size(); i++) {
                kek[ham[i]] = {2 * i, 0};
            }
            for (size_t i = 0; i < size(); i++) {
                cout << kek[i].first << " " << kek[i].second << " ";
            }
            cout << endl;
            for (size_t i = 0; i < count; i++) {
                double x1 = kek[ham[edges[i].first]].first;
                double x2 = kek[ham[edges[i].second]].first;
                double y1 = kek[ham[edges[i].first]].second;
                double y2 = kek[ham[edges[i].second]].second;
                double t = abs(x1 - x2) / 2;
                double x = min(x1, x2) + t;
                double y = (h.second.count(i) == 0) ? t : - t;
                cout << x << " " <<  y << endl;
            }
        } else {
            cout << "NO" << endl;
        }
    }
};

int main() {
    size_t n, m;
    cin >> n >> m;
    graph2 g(n);
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1);
    }
    vector<size_t> ham;
    for (size_t i = 0; i < n; i++) {
        size_t a;
        cin >> a;
        ham.push_back(a - 1);
    }
    g.solve(ham);
    return 0;
}