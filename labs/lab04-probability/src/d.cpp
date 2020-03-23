#include <iostream>
#include <vector>

using namespace std;
const int d = 15;
vector<vector<double>> a, b;

int main() {
    freopen("markchain.in", "r", stdin);
    freopen("markchain.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    double s;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        a[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }


    for (int u = 1; u <= min(d, n); u++) {
        b = a;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                s = 0;
                for (int k = 0; k < n; k++) {
                    s += a[i][k] * a[k][j];
                }
                b[i][j] = s;
            }
        }
        a = b;
    }
    for (int i = 0; i < n; i++) {
        s = 0;
        for (int j = 0; j < n; j++) {
            s += a[j][i];
        }
        cout << s / n << endl;
    }
    return 0;
}