#include <iostream>
#include <string>
using namespace std;
const int t = 1000;

void quickSort(string arr[], int left, int right);

int main() {
    freopen("bwt.in", "r", stdin);
    freopen("bwt.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string a[t], s, b;
    cin >> s;
    int n = s.size();
    a[0] = s;
    for (int i = 1; i < n; i++){
        a[i] = a[i-1][n-1] + a[i-1].substr(0, n - 1);
    }
    quickSort(a, 0, n-1);
    b = "";
    for (int i = 0; i < n; i++){
        b = b + a[i][n-1];
        //cout << a[i] << endl;
    }
    cout << b;
}

void quickSort(string arr[], int left, int right) {
    int l = left, r = right;
    string temp;
    string pivot = arr[(l + r) / 2];

    /* partition */
    while (l <= r) {
        while (arr[l] < pivot)
            l++;
        while (arr[r] > pivot)
            r--;
        if (l <= r) {
            temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }
    };

    /* recursion */
    if (left < r)
        quickSort(arr, left, r);
    if (l < right)
        quickSort(arr, l, right);
}