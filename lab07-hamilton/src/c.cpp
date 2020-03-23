#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool comp(size_t first, size_t second) {
    cout << 1 << " " << first << " " << second << endl;
    string tmp;
    cin >> tmp;
    return tmp == "YES";
}

int main() {
    size_t size;
    cin >> size;
    vector<size_t> a(size);
    for (size_t i = 0; i < size; i++) {
        a[i] = i + 1;
    }
    stable_sort(a.begin(), a.end(), comp);
    cout << 0 << " ";
    for (int j = 0; j < size; j++) {
        cout << a[j] << " ";
    }
    cout.flush();
    return 0;
}