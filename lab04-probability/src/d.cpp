#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
vector<vector<long double>> a;

int main() {
    freopen("markchain.in", "r", stdin);
    freopen("markchain.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    a.assign(n, vector<long double>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[j][i];
        }
    }


    for (int i = 0; i < n; i++) {
        a[i][i] = 0;
        for (int j = 0; j < n; j++) if (i != j) a[i][i] -= a[j][i];
    }
    for (int j = 0; j <= n; j++) a[n - 1][j] = 1;
    for (int col = 0; col < n; col++) {
        int pivot = col;
        for (int i = col + 1; i < n; i++)
            if (abs(a[i][col]) > abs(a[pivot][col])) pivot = i;
        swap(a[col], a[pivot]);
        long double divisor = a[col][col];
        for (int j = col; j <= n; j++) a[col][j] /= divisor;
        for (int i = 0; i < n; i++) if (i != col) {
            long double factor = a[i][col];
            for (int j = col; j <= n; j++) a[i][j] -= factor * a[col][j];
        }
    }
    cout.precision(12);
    for (int i = 0; i < n; i++) cout << a[i][n] << '\n';
    return 0;
}