#include <iostream>
#include <memory.h>
using namespace std;

const int h = 31;

int main() {
    freopen("choose2num.in", "r", stdin);
    freopen("choose2num.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k, a[h];
    long long m, p[h][h];
    cin >> n >> k;
    for (int i = 1; i <= k; i++) cin >> a[i];
    memset(p, 0, sizeof(p));
    p[0][0] = 1;
    for (int i = 1; i <= n; i++){
        p[i][0] = 1;
        for (int j = 1; j <= k; j++){
            p[i][j] = p[i - 1][j] + p[i - 1][j - 1];
        }
    }
    m = 0;
    a[0] = 0;
    for (int i = 1; i <= k; i++){
        for (int j = a[i - 1] + 1; j < a[i]; j++){
            m += p[n - j][k - i];
        }
    }
    cout << m;
    return 0;
}