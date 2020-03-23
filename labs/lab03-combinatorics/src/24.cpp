#include <iostream>
#include <memory.h>
using namespace std;

const int h = 100001;
void nextPerm();
void prevPerm();
int n, a[h], b[h], c[h], x[h], y[h];

int main() {
    freopen("nextperm.in", "r", stdin);
    freopen("nextperm.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        b[i] = a[i];
        c[i] = a[i];
        x[i] = i + 1;
        y[i] = i + 1;
    }
    prevPerm();
    nextPerm();
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    cout << endl;
    for (int i = 0; i < n; i++) cout << c[i] << " ";
    return 0;
}

void prevPerm(){
    int j = -1, m = 1;
    for (int i = n - 2; i >= 0; i--){
        if (b[i] > b[i + 1]) j = max(j, i);
        if (j != -1) break;
    }
    for (int i = j + 1; i < n; i++){
        if (b[i] < b[j]) m = max(m, b[i]);
    }
    if (j == -1){
        memset(b, 0, sizeof(b));
    }else{
        for (int i = 0; i < j; i++) x[b[i] - 1] = 0;
        b[j] = m;
        x[b[j++] - 1] = 0;
        int i = n - 1;
        while (j < n){
            while (x[i] == 0) i--;
            b[j] = x[i];
            j++;
            i--;
        }
    }
}

void nextPerm(){
    int j = -1, m = n;
    for (int i = n - 2; i >= 0; i--){
        if (c[i] < c[i + 1]) j = max(j, i);
        if (j != -1) break;
    }
    for (int i = j + 1; i < n; i++){
        if (c[i] > c[j]) m = min(m, c[i]);
    }
    if (j == -1){
        memset(c, 0, sizeof(c));
    }else{
        for (int i = 0; i < j; i++) y[c[i] - 1] = 0;
        c[j] = m;
        y[c[j++] - 1] = 0;
        int i = 0;
        while (j < n){
            while (y[i] == 0) i++;
            c[j] = y[i];
            j++;
            i++;
        }
    }
}