#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool isntTruthPreserving(string s, int h);
bool isntFalsityPreserving(string s, int h);
bool isntSelfDual(string s, int h);
bool isntLinear(string s, int h);
bool isntMonotonic(string s, int h);

int main() {
    vector<string> v;
    string t;
    int n, m;
    bool a[5];
    for (int i = 0; i < 5; i++){
        a[i] = false;
    }
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++){
        getline(cin, t);
        v.emplace_back(t);
    }

    bool w0,w1,w2,w3,w4;
    for (int i = 0; i < n; i++){
        m = pow(2, (v[i][0] - '0')) + 2;
        if (v[i][0] == '0') m = 3;
        /*
        w0 = isntTruthPreserving(v[i], m);
        w1 = isntFalsityPreserving(v[i], m);
        w2 = isntSelfDual(v[i], m);
        w3 = isntLinear(v[i], m);
        w4 = isntMonotonic(v[i], m);
        */
        if (a[0] == false) a[0] = isntTruthPreserving(v[i], m);
        if (a[1] == false) a[1] = isntFalsityPreserving(v[i], m);
        if (a[2] == false) a[2] = isntSelfDual(v[i], m);
        if (a[3] == false) a[3] = isntLinear(v[i], m);
        if (a[4] == false) a[4] = isntMonotonic(v[i], m);
        //cout << w0 << w1 << w2 << w3 << w4 << endl;
    }
    int ans = false;
    ans = a[0] && a[1] && a[2] && a[3] && a[4];
    //std::cout << std::boolalpha << a[0] << a[1] << a[2] << a[3] << a[4] << endl;
    if (ans){
        cout << "YES";
    }else{
        cout << "NO";
    }
    return 0;
}

bool isntTruthPreserving(string s, int h){
    bool g = false;
    if (s[h - 1] == '0') g = true;
    return g;
}

bool isntFalsityPreserving(string s, int h){
    bool g = false;
    if (s[2] == '1') g = true;
    return g;
}

bool isntSelfDual(string s, int h){
    bool g = false;
    if (h == 3){
        g = true;
    }else{
        int t = (h-2) / 2;
        for (int i = 0; i < t; i++){
            if (s[2 + i] == s[h - i - 1]) g = true;
            if (g) break;
        }
    }
    return g;
}

bool isntLinear(string s, int h) {
    bool g = false;
    if (h != 3){
        bool b[32], c[32];
        for (int i = 2; i < h; i++){
            if (s[i] == '1'){
                c[i - 2] = true;
            }else{
                c[i - 2] = false;
            }
        }
        b[0] = c[0];
        for (int j = 1; j < h-2; j++){
            for (int i = 0; i < h-3; i++){
                c[i] = c[i] ^ c[i + 1];
            }
            b[j] = c[0];
        }
        for (int i = 0; i < h-2; i++){
            if (i != 0 && i != 1 && i != 2 && i != 4 && i != 8 && i != 16 && i != 32){
                if (b[i] == true){
                    g = true;
                }
            }
            if (g) break;
        }
    }
    return g;
}

bool isntMonotonic(string s, int h){
    bool g = false;
    int u,t,q;
    int y = s[0] - '0';
    if (h != 3){
        for (int j = 0; j < y; j++){
            u = pow(2,j);
            t = pow(2, y-j-1);
            for (int i = 0; i < u; i++){
                if (s.substr(2 + 2*t*i, t) > s.substr(2 + 2*t*i+t, t)) g = true;
                if (g) break;
            }
            if (g) break;
        }
    }
    return g;
}