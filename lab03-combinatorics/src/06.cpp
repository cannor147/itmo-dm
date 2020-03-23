#include <iostream>
using namespace std;

int main(){
    freopen("vectors.in", "r", stdin);
    freopen("vectors.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int two[20], n, k = 0;
    two[0] = 1;
    for (int i = 1; i < 20; i++) two[i] = two[i - 1] * 2;
    cin >> n;
    string c, t[65536];
    for (int i = 0; i < two[n]; i++){
        c = "";
        for (int j = n - 1; j >= 0; j--){
            if ((i & two[j]) == two[j]){
                c += '1';
            }else{
                c += '0';
            }
        }
        bool f = true;
        for (int j = 1; j < n; j++){
            if ((c[j - 1] == '1') && (c[j] == '1')) f = false;
        }
        if (f){
            t[k] = c;
            k++;
        }
    }
    cout << k << endl;
    for (int i = 0; i < k; i++) cout << t[i] << endl;
    return 0;
}