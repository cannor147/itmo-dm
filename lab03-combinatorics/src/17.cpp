#include <iostream>
#include <memory.h>
using namespace std;

const int h = 42;

int main() {
    freopen("num2brackets.in", "r", stdin);
    freopen("num2brackets.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, t;
    long long p[h][h], k;
    string s = "";
    cin >> n >> k;
    k++;
    t = n + n;
    memset(p, 0, sizeof(p));
    p[0][0] = 1;
    for (int i = 1; i <= t; i++){
        for (int j = 0; j <= t; j++){
            p[i][j] = p[i - 1][j + 1];
            if (j - 1 >= 0) p[i][j] += p[i - 1][j - 1];
        }
    }
    int b = 0;
    for (int i = 0; i < t; i++){
        if (p[t - i - 1][b + 1] + 1 > k){
            s += "(";
            b++;
        }else{
            k -= p[t - i - 1][b + 1];
            s += ")";
            b--;
        }
    }
    cout << s;
    return 0;
}