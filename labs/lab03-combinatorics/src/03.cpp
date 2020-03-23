#include <iostream>
#include <string>
using namespace std;

int main(){
    freopen("antigray.in", "r", stdin);
    freopen("antigray.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int three[15], n;
    three[0] = 1;
    for (int i = 1; i < 20; i++) three[i] = three[i - 1] * 3;
    cin >> n;
    string c;
    for (int i = 0; i < three[n - 1]; i++){
        c = "0";
        int d = 0, m = i;
        for (int j = n - 2; j >= 0; j--){
            d = m / three[j];
            m %= three[j];
            if (d == 2) c += '2';
            if (d == 1) c += '1';
            if (d == 0) c += '0';
        }
        cout << c << endl;
        for (int k = 0; k < n; k++){
            char p = 's';
            if (c[k] == '2') p = '0';
            if (c[k] == '1') p = '2';
            if (c[k] == '0') p = '1';
            c[k] = p;
        }
        cout << c << endl;
        for (int k = 0; k < n; k++){
            char p = 's';
            if (c[k] == '2') p = '0';
            if (c[k] == '1') p = '2';
            if (c[k] == '0') p = '1';
            c[k] = p;
        }
        cout << c << endl;
    }
    return 0;
}