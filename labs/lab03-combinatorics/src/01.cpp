#include <iostream>
using namespace std;

int main(){
    freopen("allvectors.in", "r", stdin);
    freopen("allvectors.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int two[20], n;
    two[0] = 1;
    for (int i = 1; i < 20; i++) two[i] = two[i - 1] * 2;
    cin >> n;
    for (int i = 0; i < two[n]; i++){
        for (int j = n - 1; j >= 0; j--){
            if ((i & two[j]) == two[j]){
                cout << '1';
            }else{
                cout << '0';
            }
        }
        cout << endl;
    }
    return 0;
}