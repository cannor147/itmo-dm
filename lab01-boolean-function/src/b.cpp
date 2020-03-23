#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int N = 2e6;

int a[200][200], kol[200], zn[200], mark[200];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < 200; i++) zn[i] = -1;
    for (int i = 0; i < k; i++){
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
            if (a[i][j] != -1) kol[i]++;
        }
    }
    while (true){
        int f = 0;
        for (int i = 0; i < k; i++){
            if (kol[i] == 1 && !mark[i]){
                mark[i] = 1;
                f = 1;
                int ind;
                for (int j = 0; j < n; j++){
                    if (a[i][j] != -1){
                        zn[j] = a[i][j];
                        ind = j;
                        break;
                    }
                }
                for (int j = 0; j < k; j++){
                    if (!mark[j]){
                        if (a[j][ind] == -1) continue;
                        if (a[j][ind] == zn[ind]){
                            mark[j] = 1;
                        }else{
                            if (kol[j] == 1) return cout << "YES", 0;
                            a[j][ind] = -1;
                            kol[j]--;
                        }
                    }
                }
            }
        }
        if (!f)	break;
    }
    cout << "NO";
    return 0;
}