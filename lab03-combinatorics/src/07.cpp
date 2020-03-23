#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    freopen("permutations.in", "r", stdin);
    freopen("permutations.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> a;
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++){
        a[i] = i + 1;
        cout << a[i] << " ";
    }
    cout << endl;
    bool f = true;
    while (f){
        int j = -1, min = n + 1, idx = 0;
        for (int i = 0; i < n - 1; i++){
            if (a[i] < a[i + 1]) j = i;
        }
        if (j == -1){
            f = false;
        }else{
            for (int i = n - 1; i > j; i--){
                if (a[i] > a[j] && a[i] < min){
                    min = a[i];
                    idx = i;
                }
            }
            swap(a[j], a[idx]);
            reverse(a.begin() + j + 1, a.end());
            for (int i = 0; i < n; i++){
                cout << a[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}