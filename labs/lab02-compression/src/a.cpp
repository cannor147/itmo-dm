#include <iostream>
#include <stdlib.h>
using namespace std;

const int t = 1000;
void merge(long long arr[], int l, int m, int r);
void mergeSort(long long arr[], int l, int r);
void oneSort(long long arr[], int l, int r);

int main() {
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    long long s = 0, a[t];
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    mergeSort(a, 0, n - 1);
    for (int i = 1; i < n; i++){
        a[i] += a[i - 1];
        s += a[i];
        oneSort(a, i, n - 1);
    }
    cout << s;
}

void merge(long long arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 =  r - m;
    long long* left;
    long long* right;
    left = new long long[n1];
    right = new long long[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        right[i] = arr[m + i + 1];

    int i = 0, j = 0, k = l;
    while ((i < n1) && (j < n2)){
        if (left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = right[j];
        j++;
        k++;
    }
    delete [] left;
    delete [] right;
}

void mergeSort(long long arr[], int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void oneSort(long long arr[], int l, int r) {
    long long temp;
    int ll = l;
    while (ll < r){
        if (arr[ll] > arr[ll + 1]){
            temp = arr[ll];
            arr[ll] = arr[ll + 1];
            arr[ll + 1] = temp;
            ll++;
        }else break;
    }
}