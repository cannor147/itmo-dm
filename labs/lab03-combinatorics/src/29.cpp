#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int h = 100001;

int main() {
    freopen("nextpartition.in", "r", stdin);
    freopen("nextpartition.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> a;
    a.resize(h);
    string s;
    int n, m, k = 0, j = -1;
    cin >> s;
    s += "+";
    m = s.size();
    for (int i = 0; i < m; i++){
        if ((s[i] == '+') || (s[i] == '=')){
            if (s[i] == '+') a[j] = k;
            if (s[i] == '=') n = k;
            k = 0;
            j++;
        }else{
            int c = (int)(s[i] - '0');
            k = k * 10 + c;
        }
    }
    if (a[0] == n){
        cout << "No solution";
    }else{
        cout << n << "=";
        int size = j;
        a[size - 1]--;
        a[size - 2]++;
        if (a[size - 2] > a[size - 1]){
            a[size - 2] += a[size - 1];
            a[size - 1] = 0;
            size--;
        }else{
            while (a[size - 1] - a[size - 2] >= a[size - 2]){
                a[size] = a[size - 1] - a[size - 2];
                a[size - 1] = a[size - 2];
                size++;
            }
        }
        cout << a[0];
        for (int i = 1; i < size; i++) cout << "+" << a[i];
    }
    return 0;
}