#include <iostream>
#include <iomanip>

using namespace std;
const double d = 14;

int main() {
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, a, b = 0, u;
    double p = 1, t, s = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        u = b;
        cin >> a >> b;
        p = p / a;
        t = p * (b - u);
        s += t;
    }
    cout << setprecision(d) << n - s;
    return 0;
}