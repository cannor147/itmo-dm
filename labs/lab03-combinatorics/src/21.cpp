#include <iostream>
#include <vector>
using namespace std;

int main() {
    freopen("num2part.in", "r", stdin);
    freopen("num2part.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> b;
    int size;
    long long t;
    cin >> size >> t;
    b.resize(size);
    for (int i = 0; i < size; i++) b[i] = 1;
    while (t != 0){
        b[size - 1]--;
        b[size - 2]++;
        if (b[size - 2] > b[size - 1]){
            b[size - 2] += b[size - 1];
            b.pop_back();
            size--;
        }else{
            while (b[size - 1] - b[size - 2] >= b[size - 2]){
                b.push_back(b[size - 1] - b[size - 2]);
                b[size - 1] = b[size - 2];
                size++;
            }
        }
        t--;
    }
    cout << b[0];
    for (int i = 1; i < size; i++) cout << "+" << b[i];
    return 0;
}