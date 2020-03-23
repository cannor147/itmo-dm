#include <iostream>
#include <vector>

using namespace std;

const int h = 101;
vector<int> a, b;

int main() {
    freopen("part2num.in", "r", stdin);
    freopen("part2num.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    a.resize(h);
    int n = 0, k = 0, j = 0, m;
    string s;
    cin >> s;
    s += "+";
    m = s.size();
    for (int i = 0; i < m; i++){
        if (s[i] == '+'){
            a[k] = j;
            n += j;
            j = 0;
            k++;
        }else{
            int c = (int)(s[i] - '0');
            j = j * 10 + c;
        }
    }
    int size = 0;
    for (int i = 0; i < k; i++) size += a[i];
    a.resize(k);
    b.resize(size);
    for (int i = 0; i < size; i++) b[i] = 1;
    long long t = 0;
    while (a != b){
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
        t++;
    }
    cout << t;
    return 0;
}