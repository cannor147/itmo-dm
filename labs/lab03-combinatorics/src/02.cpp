#include <iostream>
using namespace std;

int main(){
    freopen("gray.in", "r", stdin);
    freopen("gray.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int two[20], n;
    char t;
    string c;
    two[0] = 1;
    for (int i = 1; i < 20; i++) two[i] = two[i - 1] * 2;
    cin >> n;
    for (int i = 0; i < two[n]; i++){
        c = "";
        for (int j = n - 1; j >= 0; j--){
            if ((i & two[j]) == two[j]){
                c += '1';
            }else{
                c += '0';
            }
        }for (int j = n - 1; j > 0; j--){
            if (c[j] == c[j - 1]){
                c[j] = '0';
            }else{
                c[j] = '1';
            }
        }
        cout << c << endl;
    }
    return 0;
}