#include <iostream>
#include <string>
using namespace std;

const int t2 = 2000, l = 26;
bool f;
string a[t2]; //словарь;
int m = l; //количество объектов в словаре
int inDictionary(string c);

int main() {
//    freopen("lzw.in", "r", stdin);
//    freopen("lzw.out", "w", stdout);
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);
    string s, c, p;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < l; i++) a[i] = 'a' + i;
    int y;
    c = "";
    for (int i = 0; i < n; i++){
        c += s[i];
        y = inDictionary(c);
        if (y == -1){
            p = c.substr(0, c.size() - 1);
            a[m] = c;
            c = s[i];
            cout << inDictionary(p) << " ";
            m++;
        }
    }
    y = inDictionary(c);
    cout << y;
}

int inDictionary(string c){
    int g = -1;
    for (int i = 0; i < m; i++){
        if (a[i] == c) g = i;
        if (g != -1) break;
    }
    return g;
}