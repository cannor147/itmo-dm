#include <iostream>
#include <vector>
using namespace std;

int main() {
    freopen("choose.in", "r", stdin);
    freopen("choose.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> a;
    int n, k;
    cin >> n >> k;
    a.resize(k + 1);
    for (int i = 0; i < k; i++){
        a[i] = i + 1;
        cout << a[i] << " ";
    }
    cout << endl;
    bool f = true;
    while (f){
        a[k] = n + 1;
        int j = -1;
        for (int i = k - 1; i >= 0; i--){
            if (a[i + 1] - a[i] > 1){
                j = i;
                a[j]++;
            }
            if (j != -1) break;
        }
        if (j == -1){
            f = false;
        }else{
            for (int i = 0; i < k; i++){
                if (i > j) a[i] = a[i - 1] + 1;
                cout << a[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}