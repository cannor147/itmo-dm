#include <iostream>
#include <string>
using namespace std;

string nextVector(string, int);
string prevVector(string, int);

int main() {
    freopen("nextvector.in", "r", stdin);
    freopen("nextvector.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    string s;
    cin >> s;
    n = s.size();
    cout << prevVector(s, n) << endl;
    cout << nextVector(s, n);
    return 0;
}

string nextVector(string s, int n){
    int j = -1;
    string ans = s;
    for (int i = n - 1; i >= 0; i--){
        if (ans[i] == '0') j = max(j, i);
    }
    if (j == -1){
        ans = "-";
    }else{
        ans[j] = '1';
        if (j + 1 < n){
            for (int i = j + 1; i < n; i++){
                ans[i] = '0';
            }
        }
    }
    return ans;
}

string prevVector(string s, int n){
    int j = -1;
    string ans = s;
    for (int i = n - 1; i >= 0; i--){
        if (ans[i] == '1') j = max(j, i);
    }
    if (j == -1){
        ans = "-";
    }else{
        ans[j] = '0';
        if (j + 1 < n){
            for (int i = j + 1; i < n; i++){
                ans[i] = '1';
            }
        }
    }
    return ans;
}