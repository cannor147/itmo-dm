#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <map>
#include <set>
#include <cmath>

const double e = 1e-9;

using namespace std;

struct line {
    double a, b;
    line(double x1, double y1, double x2, double y2) {
        if (abs(x1 - x2) < e) {
            a = DBL_MAX;
            b = x1;
        } else {
            a = (y1 - y2) / (x1 - x2);
            b = -x1 * a + y1;
        }
    }
    bool contains(double x, double y) {
        if (a == DBL_MAX) {
            return abs(x - b) < e;
        } else {
            return abs(a * x + b - y) < e;
        }
    }
};
struct point {
    size_t index;
    double x, y;
    point(line &l1, line &l2) {
        if (l1.a == DBL_MAX) {
            x = l1.b;
            y = l2.a * x + l2.b;
        } else if (l2.a == DBL_MAX) {
            x = l2.b;
            y = l1.a * x + l1.b;
        } else {
            x = (l2.b - l1.b) / (l1.a - l2.a);
            y = l1.a * x + l1.b;
        }
    }

};

struct edge {
    bool used;
    size_t to;
    size_t c;
    double a;
    edge(point &v1, point &v2, double kek) {
        used = false;
        to = v2.index;
        a = kek;
        if (v1.y < v2.y) {
            if (v1.x <= v2.x) {
                c = 1;
            } else {
                c = 2;
            }
        } else if (v1.y > v2.y) {
            if (v1.x >= v2.x) {
                c = 3;
            } else {
                c = 4;
            }
        } else {
            if (v1.x < v2.x) {
                c = 1;
            } else {
                c = 3;
            }
        }
    }
    void use() {
        used = true;
    }
};
struct vertex {
    double x, y;
    vector<edge> edges;
    void set(double x1, double y1) {
        x = x1;
        y = y1;
    }
    void sort() {
        std::sort(edges.begin(), edges.end());
    }
};

bool operator<(point const &first, point const &second) {
    return (first.x < second.x || (abs(first.x - second.x) < e && first.y < second.y));
}
bool operator<(edge const &first, edge &second) {
    return (first.c < second.c) || (first.c == second.c && first.a < second.a);
}

class graph {

private:
    vector<vertex> matrix;
    map<pair<size_t, size_t>, size_t> fast_search;
    void dfs_lol(size_t u, edge &e, vector<edge> &lol) {
        if (e.used) return;
        e.use();
        lol.push_back(e);
        auto &r = matrix[e.to].edges;
        edge &f = r[(fast_search.at({e.to, u}) - 1 + r.size()) % r.size()];
        dfs_lol(e.to, f, lol);
    }
    double count(vector<edge> &edges) {
        double result = 0;
        for (size_t i = 0; i < edges.size(); i++) {
            result += matrix[edges[i].to].x * matrix[edges[(i + 1) % edges.size()].to].y;
            result -= matrix[edges[i].to].x * matrix[edges[(i - 1 + edges.size()) % edges.size()].to].y;
        }
        result /= 2;
        if (result < 0) result = -result;
        return result;
    }

public:
    graph(size_t n) {
        matrix = vector<vertex>(n, vertex());
    }
    size_t size() {
        return matrix.size();
    }
    void add_data(set<point> &sp) {
        vector<size_t> colors(size(), 0);
        for (auto &p : sp) {
            matrix[p.index].set(p.x, p.y);
        }
    }
    void add_edge(point &u, point &v, line &l) {
        matrix[u.index].edges.emplace_back(u, v, l.a);
        matrix[v.index].edges.emplace_back(v, u, l.a);
    }
    vector<double> solve() {
        vector<double> result;
        for (size_t i = 0; i < size(); i++) {
            matrix[i].sort();
        }
        for (size_t i = 0; i < size(); i++) {
            for (size_t j = 0; j < matrix[i].edges.size(); j++) {
                fast_search.insert({{i, matrix[i].edges[j].to}, j});
            }
        }
        for (size_t i = 0; i < size(); i++) {
            for (auto &e : matrix[i].edges) {
                if (!e.used) {
                    vector<edge> lol;
                    dfs_lol(i, e, lol);
                    double f = count(lol);
                    if (f > 1e-8) {
                        result.push_back(f);
                    }
                }
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};

int main() {
    size_t n;
    int x1, y1, x2, y2;
    cin >> n;
    vector<line> lines;
    vector<vector<point>> points(n, vector<point>());
    for (size_t i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        lines.emplace_back(x1, y1, x2, y2);
    }
    size_t count = 0;
    set<point> sp;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (abs(lines[i].a - lines[j].a) < e) continue;
            point p(lines[i], lines[j]);
            if (sp.count(p) == 0) {
                p.index = count;
                sp.insert(p);
                count++;
            }
        }
    }
    for (size_t i = 0; i < n; i++) {
        for (auto &p : sp) {
            if (lines[i].contains(p.x, p.y)) {
                points[i].push_back(p);
            }
        }
    }
    graph g(count);
    g.add_data(sp);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 1; j < points[i].size(); j++) {
            point &v1 = points[i][j], &v2 = points[i][j - 1];
            g.add_edge(v1, v2, lines[i]);
        }
    }
    vector<double> kek = g.solve();
    if (kek.size() == 0) {
        cout << 0;
        return 0;
    }
    cout << kek.size() - 1 << endl;
    cout.precision(15);
    for (size_t i = 0; i < kek.size() - 1; i++) {
        cout << kek[i];
        if (i != kek.size() - 2) cout << endl;
    }
    return 0;
}