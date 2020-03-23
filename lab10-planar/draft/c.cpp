#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
const double e = 1e-9;
struct edge {
    bool used;
    size_t to, c;
    double a, w;
    size_t facet_index;

    edge(size_t to, double a, size_t c, double w) {
        used = false;
        facet_index = SIZE_MAX;
        this->to = to;
        this->a = a;
        this->c = c;
        this->w = w;
    }
    void use() {
        used = true;
    }
    void set_facet(size_t i) {
        facet_index = i;
    }
};
bool operator<(edge const &first, edge const &second) {
    return (first.c < second.c) || (first.c == second.c && first.a < second.a);
}
struct vertex {
    double x, y;
    size_t index;
    vector<edge> edges;
    vertex(double x1, double y1, size_t i) {
        x = x1;
        y = y1;
        index = i;
    }
    void sort() {
        std::sort(edges.begin(), edges.end());
    }
    void add_edge(vertex &u, double w) {
        double x1 = x, y1 = y, x2 = u.x, y2 = u.y;
        double a;
        if (abs(x1 - x2) < e) {
            a = DBL_MAX;
        } else {
            a = (y1 - y2) / (x1 - x2);
        }
        size_t c;
        if (y1 < y2) {
            if (x1 <= x2) {
                c = 1;
            } else {
                c = 2;
            }
        } else if (y1 > y2) {
            if (x1 >= x2) {
                c = 3;
            } else {
                c = 4;
            }
        } else {
            if (x1 < x2) {
                c = 1;
            } else {
                c = 3;
            }
        }
        edges.emplace_back(u.index, a, c, w);
    }
};
class graph2 {

private:
    struct edge2 {
    private:
        size_t index;
        double weight;
    public:
        edge2() {
            index = 0;
            weight = 0;
        }
        explicit edge2(size_t i, double w = 0) {
            index = i;
            weight = w;
        }
        size_t get_index() {
            return index;
        }
        double get_weight() {
            return weight;
        }
    };
    vector<vector<edge2>> matrix;
    void dijkstra(vector<double> &result, set<pair<double, size_t>> q) {
        for (size_t i = 0; i < size(); i++) {
            size_t j_min = (*q.begin()).second;
            q.erase({result[j_min], j_min});
            if (result[j_min] == DBL_MAX) {
                break;
            }
            for (auto &e : matrix[j_min]) {
                if (result[j_min] + e.get_weight() < result[e.get_index()]) {
                    q.erase({result[e.get_index()], e.get_index()});
                    result[e.get_index()] = result[j_min] + e.get_weight();
                    q.insert({result[e.get_index()], e.get_index()});
                }
            }
        }
    }

public:
    explicit graph2(size_t n) {
        matrix = vector<vector<edge2>>(n, vector<edge2>());
    }
    size_t size() {
        return matrix.size();
    }
    void add_edge(size_t i, size_t j, double w = 0) {
//        cout << "add " << i << " " << j << " " << w << endl;
        matrix[i].emplace_back(j, w);
        matrix[j].emplace_back(i, w);
    }

    vector<double> shortcuts(size_t i) {
        vector<double> result(size(), DBL_MAX);
        set<pair<double, size_t>> q;
        result[i] = 0;
        q.insert({0, i});
        dijkstra(result, q);
        return result;
    }
    double shorcut(size_t i, size_t j) {
        auto a = shortcuts(i);
        return a[j];
    }
};




class graph {

private:
    map<pair<size_t, size_t>, size_t> fast_search;
    vector<vertex> matrix;
    edge &next(size_t u, edge &e) {
        auto &r = matrix[e.to].edges;
        edge &f = r[(fast_search.at({e.to, u}) - 1 + r.size()) % r.size()];
        return f;
    }
    edge &reverse(size_t u, edge &e) {
        auto &r = matrix[e.to].edges;
        edge &f = r[(fast_search.at({e.to, u}) + r.size()) % r.size()];
        return f;
    }
    void dfs_lol(size_t u, edge &e, vector<pair<size_t, edge>> &lol, size_t j) {
        if (e.used) return;
        e.use();
        e.set_facet(j);
        lol.push_back({u, e});
        dfs_lol(e.to, next(u, e), lol, j);
    }

public:
    size_t size() {
        return matrix.size();
    }
    void add_vertex(double x, double y) {
        matrix.emplace_back(x, y, size());
    }
    void add_edge(size_t i, size_t j, double w = 0) {
        matrix[i].add_edge(matrix[j], w);
        matrix[j].add_edge(matrix[i], w);
    }

    double solve(size_t s, size_t t) {
        vector<double> result;
        for (size_t i = 0; i < size(); i++) {
            matrix[i].sort();
        }
        for (size_t i = 0; i < size(); i++) {
            for (size_t j = 0; j < matrix[i].edges.size(); j++) {
                fast_search.insert({{i, matrix[i].edges[j].to}, j});
            }
        }
        vector<vector<pair<size_t, edge>>> facets;
        for (size_t i = 0; i < size(); i++) {
            for (auto &e : matrix[i].edges) {
                if (!e.used) {
                    facets.emplace_back();
                    vector<pair<size_t, edge>> &lol = facets.back();
                    dfs_lol(i, e, lol, facets.size() - 1);
                }
            }
        }
        size_t ii, jj = SIZE_MAX;
        for (ii = 0; ii < facets.size(); ii++) {
            bool ss = false, tt = false;
            for (size_t j = 0; j < facets[ii].size(); j++) {
                auto &u = facets[ii][j];
                if (u.first == s || u.second.to == s) {
                    if (u.first == s) {
                        jj = j;
                    }
                    ss = true;
                }
                if (u.first == t || u.second.to == t) tt = true;
            }
            if (ss && tt) {
//                cout << ii << " " << jj << endl;
                break;
            }
        }
        vector<pair<size_t, edge>> first, second;
        for (size_t i = jj; facets[ii][i].first != t; i = (i + 1) % facets[ii].size()) {
            second.push_back({facets[ii][i].first, facets[ii][i].second});
            second.back().second.set_facet(facets.size());

            auto &edg = matrix[facets[ii][i].first].edges;
            for (size_t j = 0; j < edg.size(); j++) {
                if (edg[j].to == second.back().second.to) {
                    edg[j].set_facet(facets.size());
                }
            }
        }
        for (size_t i = 0; i < facets[ii].size(); i++) {
            bool f = false;
            for (size_t j = 0; j < second.size(); j++) {
                if (second[j].first == facets[ii][i].first && second[j].second.to == facets[ii][i].second.to) {
                    f = true;
                }
            }
            if (!f) first.push_back(facets[ii][i]);
        }
//        cout << "first" << endl;
//        for (size_t i = 0; i < first.size(); i++) {
//            cout << first[i].first + 1 << " " << first[i].second.to + 1 << endl;
//        }
//        cout << "second" << endl;
//        for (size_t i = 0; i < second.size(); i++) {
//            cout << second[i].first + 1 << " " << second[i].second.to + 1 << endl;
//        }
//        cout << endl;
        facets[ii] = first;
        facets.push_back(second);
        graph2 h(facets.size());
        for (size_t i = 0; i < facets.size(); i++) {
            for (size_t j = 0; j < facets[i].size(); j++) {
                edge &e = facets[i][j].second, &f = reverse(facets[i][j].first, e);
                h.add_edge(e.facet_index, f.facet_index, e.w);
            }
        }
//        cout << ii << " " << facets.size() - 1 << endl;
        return h.shorcut(ii, facets.size() - 1);
    }
};

int main() {
    size_t n, m, s, t;
    cin >> n >> m >> s >> t;
    graph g;
    for (size_t i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g.add_vertex(x, y);
    }
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        double w;
        cin >> a >> b >> w;
        g.add_edge(a - 1, b - 1, w);
    }
    cout << g.solve(s - 1, t - 1);
    return 0;
}