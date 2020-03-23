#include <iostream>
#include <string>
#include <memory.h>
using namespace std;

const int h = 65536;
string c[h];
bool visited[h];

int main(){
    freopen("chaincode.in", "r", stdin);
    freopen("chaincode.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(visited, false, sizeof(visited));
    int n, k = 0;
    cin >> n;
    c[0] = "";
    for (int i = 0; i < n; i++) c[0] += "0";
    cout << c[0] << endl;
    visited[0] = true;
    bool f = true;
    while (f){
        string u = c[k].substr(1, n - 1);
        string d = u + "1";
        k++;
        int l = 1, r = 0;
        for (int i = 0; i < n; i++){
            if (d[i] == '1') r += l;
            l *= 2;
        }
        bool g = visited[r];
        if (!g){
            c[k] = d;
            visited[r] = true;
        }else{
            d = u + "0";
            l = 1;
            r = 0;
            for (int i = 0; i < n; i++){
                if (d[i] == '1') r += l;
                l *= 2;
            }
            f = !(visited[r]);
            if (f) c[k] = d;
        }
        if (f) cout << c[k] << endl;
    }
    return 0;
}