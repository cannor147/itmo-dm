#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>

using namespace std;

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    if (m == 0) {
        cout << "NO";
        return 0;
    }
    set<unsigned long> s;
    vector<pair<size_t, vector<size_t>>> v(m);
    for (size_t i = 0; i < m; i++) {
        cin >> v[i].first;
        v[i].second.resize(v[i].first);
        bitset<10> b(0);
        for (size_t j = 0; j < v[i].first; j++) {
            cin >> v[i].second[j];
            v[i].second[j]--;
            b[v[i].second[j]] = true;
        }
        s.insert(b.to_ulong());
    }
    sort(v.begin(), v.end());
    if (v[0].first != 0) {
        cout << "NO";
        return 0;
    }
    for (size_t i = 0; i < m; i++) {
        vector<char> t(10, 0);
        for (size_t k = 0; k < v[i].second.size(); k++) {
            t[v[i].second[k]] = true;
        }
        for (size_t j = 0; j < 1024; j++) {
            bitset<10> b(j);
            bool g = true;
            for (size_t k = 0; k < 10; k++) {
                if (b[k] && !t[k]) g = false;
                if (!g) break;
            }
            if (!g) continue;
            if (s.count(b.to_ulong()) == 0) {
                cout << "NO";
                return 0;
            }
        }
    }
    for (size_t i = 0; i < m; i++) {
        for (size_t j = i + 1; j < m; j++) {
            if (v[i].first < v[j].first) {
                bitset<10> b(0);
                for (size_t k = 0; k < v[i].second.size(); k++) {
                    b[v[i].second[k]] = true;
                }
                bool g = false;
                for (size_t k = 0; k < v[j].second.size(); k++) {
                    if (b[v[j].second[k]]) continue;
                    b[v[j].second[k]] = true;
                    if (s.count(b.to_ulong()) == 1) {
                        g = true;
                    }
                    b[v[j].second[k]] = false;
                }
                if (!g) {
                    cout << "NO";
                    return 0;
                }
            }
        }
    }
    cout << "YES";
    return 0;
}