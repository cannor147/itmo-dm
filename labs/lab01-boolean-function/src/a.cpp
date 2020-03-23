#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int b = pow(2,n);
    bool a[31][31];
    int p[16];
    for (int i = 0; i < 16; i++){
        p[i] = pow(2,i);
    }
    for (int i = 0; i < 31; i++){
        for (int j = 0; j < 31; j++){
            a[i][j] = false;
        }
    }
    int x, y;
    for (int i = 0; i < m; i++){
        cin >> x >> y;
        x += 15;
        y += 15;
        a[x][y] = true;
        a[y][x] = true;
    }
    bool r = false, f;
    int q,w;
    for (int i = 0; i < b; i++){
        f = true;
        for (int j = 15-n; j < 16+n; j++){
            if (j != 15){
                for (int k = 15-n; k < 16+n; k++){
                    if (k != 15){
                        //cout << '[' << j << ',' << k << ']' << endl;
                        if (a[j][k]){
                            q = (i / p[abs(j-15) - 1]) % 2;
                            w = (i / p[abs(k-15) - 1]) % 2;
                            if (j < 15) q = abs(q - 1);
                            if (k < 15) w = abs(w - 1);
                            if (q == 0 && w == 0){
                                f = false;
                            }
                            //cout << i << " - " << q << ' ' << w <<endl;
                        }
                    }
                    if (!f) break;
                }
            }
            if (!f) break;
        }
        r = r || f;
        //std::cout << std::boolalpha << r << ' ' << f << endl;
        if (r) break;
    }
    if (r){
        cout << "NO";
    }else{
        cout << "YES";
    }
    return 0;
}