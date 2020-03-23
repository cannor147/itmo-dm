#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    vector<string> v;
    int l, m, n;
    string t;
    bool a[1024], b[1024];
    cin >> n;
    m = pow(2, n);
    l = n + 1;
    cin.ignore();
    for (int i = 0; i < m; i++){
        getline(cin, t);
        v.emplace_back(t);
    }

    for (int i = 0; i < m; i++){
        if (v[i][l] == '1'){
            a[i] = true;
        }else{
            a[i] = false;
        }
    }
    b[0] = a[0];
    for (int j = 1; j < m; j++){
        for (int i = 0; i < m-1; i++){
            a[i] = a[i] ^ a[i+1];
        }
        b[j] = a[0];
    }
    for (int i = 0; i < m; i++){
        if (b[i] == true){
            v[i][l] = '1';
        }else{
            v[i][l] = '0';
        }
        cout << v[i] << endl;
    }
    return 0;
}