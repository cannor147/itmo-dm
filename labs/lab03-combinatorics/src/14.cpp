#include <iostream>
using namespace std;

const int h = 19;

int main() {
    freopen("perm2num.in", "r", stdin);
    freopen("perm2num.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    long long k, ans, m, fac[h], a[h];
    fac[0] = 1;
    for (int i = 0; i < h; i++) fac[i + 1] = fac[i] * (i + 1);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    ans = 0;
    for (int i = n - 2; i >= 0; i--){
        k = a[i];
        for (int j = 0; j < i; j++){
            if (a[j] <= a[i]) k--;
        }
        ans += fac[n - i - 1] * (--k);
    }
    cout << ans;
    return 0;
}