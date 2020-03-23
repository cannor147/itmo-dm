#include <iostream>
#include <memory.h>
using namespace std;

const int h = 19;

int main() {
    freopen("num2perm.in", "r", stdin);
    freopen("num2perm.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    long long k, s, m, fac[h], a[h];
    bool visited[h];
    fac[0] = 1;
    for (int i = 0; i < h; i++) fac[i + 1] = fac[i] * (i + 1);
    memset(visited, false, sizeof(visited));
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        s = k / fac[n - i];
        k %= fac[n - i];
        m = 0;
        for (int j = 1; j <= n; j++){
            if (!(visited[j])){
                if (m == s){
                    a[i] = j;
                    visited[j] = true;
                }
                m++;
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    return 0;
}