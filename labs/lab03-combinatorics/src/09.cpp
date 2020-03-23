#include <iostream>
using namespace std;

int main() {
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    string s = "", t = "";
    cin >> n;
    for (int i = 0; i < n; i++){
        s = "(" + s + ")";
        t += "()";
    }
    cout << s << endl;
    int e, b, i;
    bool f;
    while (s != t){
        i = 2 * n, b = 0, e = 0;
        f = true;
        while (f){
            i--;
            if (s[i] == ')'){
                e++;
            }else{
                b++;
                if (e > b) f = false;
            }
        }
        s[i] = ')';
        for (int j = i + 1; j < 2 * n - 1; j++){
            if (b > 0){
                s[j] = '(';
                b--;
            }else{
                s[j] = ')';
            }
        }
        cout << s << endl;
    }
    return 0;
}