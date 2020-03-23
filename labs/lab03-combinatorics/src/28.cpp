#include <iostream>
#include <memory.h>
using namespace std;

const int h = 100001;

int main() {
    freopen("nextmultiperm.in", "r", stdin);
    freopen("nextmultiperm.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, a[h];
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    int j = n - 2;
    while ((j >=0) && (a[j] >= a[j + 1])) j--;
    if (j >= 0){
        int i = j + 1;
        while ((i + 1 < n) && (a[i + 1] > a[j])) i++;
        swap(a[i], a[j]);
        for (int g = j + 1; g < (n + j + 1) / 2; g++) swap(a[g], a[n + j - g]);
    }else{
        memset(a, 0, sizeof(a));
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    return 0;
}