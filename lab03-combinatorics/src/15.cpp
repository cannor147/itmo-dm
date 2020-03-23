#include <iostream>
#include <memory.h>
using namespace std;

const int h = 31;

int main() {/*
	freopen("num2choose.in", "r", stdin);
	freopen("num2choose.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
*/
    int n, k, a[h];
    long long m, p[h][h];
    cin >> n >> k >> m;
    memset(p, 0, sizeof(p));
    p[0][0] = 1;
    for (int i = 1; i <= n; i++){
        p[i][0] = 1;
        for (int j = 1; j <= k; j++){
            p[i][j] = p[i - 1][j] + p[i - 1][j - 1];
        }
    }
    int i = 1, t = k;
    while (t > 0){
        if (m < p[n - 1][t - 1]){
            a[k - t] = i;
            t--;
        }else{
            m -= p[n - 1][t - 1];
        }
        n--;
        i++;
    }
    for (int i = 0; i < k; i++) cout << a[i] << " ";
    return 0;
}