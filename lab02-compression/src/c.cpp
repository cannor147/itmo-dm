#include <iostream>
#include <string>
using namespace std;

const int t = 1000, l = 26;
int n;
int a[l], p[l];
int shift(int d);

int main() {
    freopen("mtf.in", "r", stdin);
    freopen("mtf.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++){
        p[s[i] - 'a']++;
    }
    for (int i = 0; i < l; i++){
        a[i] = i + 1;
    }
    int b[t];
    for (int i = 0; i < n; i++){
        b[i] = shift(s[i] - 'a');
    }
    for (int i = 0; i < n; i++){
        cout << b[i] << ' ';
    }
}

int shift(int d){
    int temp = a[d];
    for (int i = 0; i < l; i++){
        if (a[i] < temp){
            a[i]++;
        }
        //cout << a[i] << ' ';
    }
    //cout << endl;
    a[d] = 1;
    return temp;
}