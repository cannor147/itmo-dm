#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("cycles.in", "r", stdin);
    freopen("cycles.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m, a;
    cin >> n >> m;
    vector<pair<size_t, size_t>> r;
    for (size_t i = 0; i < n; i++) {
        cin >> a;
        r.push_back({a, i});
    }
    sort(r.rbegin(), r.rend());
    vector<vector<size_t>> v(m);
    for (size_t i = 0; i < m; i++) {
        cin >> a;
        v[i].resize(a);
        for (size_t j = 0; j < a; j++) {
            cin >> v[i][j];
            v[i][j]--;
        }
    }
    size_t count = 0;
    vector<char> result(n, false);
    for (size_t i = 0; i < n; i++) {
        result[r[i].second] = true;
        bool g = true;
        for (size_t j = 0; j < m; j++) {
            bool f = true;
            for (auto &k : v[j]) {
//                cout << k << " " << (result[k] == true) << endl;
                if (!result[k]) {
                    f = false;
                    break;
                }
            }
            if (f) {
                g = false;
                break;
            }
        }
//        cout << g << endl;
        if (!g) {
            result[r[i].second] = false;
        } else {
            count += r[i].first;
        }
    }
    cout << count;
    return 0;
}