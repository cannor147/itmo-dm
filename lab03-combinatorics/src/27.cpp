#include <iostream>
#include <string>
using namespace std;

int main() {
    freopen("nextbrackets.in", "r", stdin);
    freopen("nextbrackets.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, t;
    string s = "", st = "";
    cin >> s;
    t = s.size();
    n = t / 2;
    for (int i = 0; i < n; i++) st += "()";
    if (s == st){
        s = "-";
    }else{
        int e, b, i;
        bool f;
        i = t, b = 0, e = 0;
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
        for (int j = i + 1; j < t - 1; j++){
            if (b > 0){
                s[j] = '(';
                b--;
            }else{
                s[j] = ')';
            }
        }
    }
    cout << s;
    return 0;
}