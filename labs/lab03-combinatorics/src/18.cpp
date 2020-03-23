#include <iostream>
#include <string>
#include <memory.h>
using namespace std;

const int h = 42;

int main() {
    freopen("brackets2num.in", "r", stdin);
    freopen("brackets2num.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    long long p[h][h], k = 0;
    string s;
    cin >> s;
    t = s.size();
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
        if (s[i] == '('){
            b++;
        }else{
            k += p[t - i - 1][b + 1];
            b--;
        }
    }
    cout << k;
    return 0;
}