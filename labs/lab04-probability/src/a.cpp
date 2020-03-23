#include <iostream>
#include <cmath>

using namespace std;
const double d = 0.00001;

int main() {
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int k, n, p, m;
    double u, s = 0;
    cin >> k >> n;
    for (int i = 0; i < k; i++) {
        cin >> p >> m;
        u = ((double) p * m) / 100;
        s += u;
    }
    s = s / n;
    cout << s-remainder(s, d);
    return 0;
}