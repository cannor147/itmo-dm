#include <iostream>
#include <vector>
using namespace std;

int main() {
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> a;
    int n;
    cin >> n;
    a.resize(n);
    a[0] = 1;
    cout << a[0];
    for (int i = 1; i < n; i++){
        a[i] = 1;
        cout << "+" << a[i];
    }
    cout << endl;
    bool f = true;
    int size = n;
    while (f){
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
        if (a[0] == n){
            f = false;
        }else{
            for (int i = 1; i < size; i++){
                cout << "+" << a[i];
            }
            cout << endl;
        }
    }
    return 0;
}