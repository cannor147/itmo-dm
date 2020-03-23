#include <iostream>
#include <iomanip>

using namespace std;
const double d = 13;

double pow(double t, int m) {
    switch(m) {
        case 1: return t;
        case 2: return t * t;
        case 3: return t * t * t;
        default: return 0;
    }
}

int main() {
    freopen("shooter.in", "r", stdin);
    freopen("shooter.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    double p = 0, u = 0, s = 0;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p;
        p = pow(1 - p, m);
        if (i == k) u = p;
        s += p;
    }
    cout << setprecision(d) << u / s;
    return 0;
}