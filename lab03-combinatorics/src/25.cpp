#include <iostream>
using namespace std;

const int h = 10001;
void nextChoose();
int n, k, a[h];

int main() {
    freopen("nextchoose.in", "r", stdin);
    freopen("nextchoose.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < k; i++) cin >> a[i];
    nextChoose();
    return 0;
}

void nextChoose(){
    bool f = false;
    for (int i = k - 1; i >= 0; i--){
        if (a[i] < n - k + i + 1){
            a[i]++;
            for (int j = i + 1; j < k; j++) a[j] = a[j - 1] + 1;
            f = true;
        }
        if (f) break;
    }
    if (f){
        for (int i = 0; i < k; i++) cout << a[i] << " ";
    }else{
        cout << -1;
    }
}