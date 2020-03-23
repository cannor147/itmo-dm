#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool check_k33(size_t n, vector<vector<size_t>> &matrix) {
    if (n == 6) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = i + 1; j < n; j++) {
                for (size_t k = j + 1; k < n; k++) {
                    bool f = true;
                    for (size_t t = 0; t < n; t++) {
                        if (t == i || t == j || t == k) continue;
                        if (!(matrix[i][t] && matrix[j][t] && matrix[k][t])) {
                            f = false;
                            break;
                        }
                    }
                    if (f) return false;
                }
            }
        }
    }
    return true;
}
bool check_k5(size_t n, vector<vector<size_t>> &matrix, size_t y = SIZE_MAX) {
    if (n == 5) {
        size_t count = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                if (i == y || j == y) continue;
                if (matrix[i][j] == 1) {
                    count++;
                }
            }
        }
        return count != 20;
    }
    if (n == 6) {
        for (size_t i = 0; i < n; i++) {
            vector<vector<size_t>> matrix2 = vector<vector<size_t>>(n, vector<size_t>(n, 0));
            for (size_t j = 0; j < n ; j++) {
                if (j == i) continue;
                for (size_t k = 0; k < n; k++) {
                    if (k == i) continue;
                    matrix2[j][k] = matrix2[k][j] = matrix[j][k];
                }
            }
            if (!check_k5(n - 1, matrix2, i)) {
                return false;
            }
            for (size_t j = 0; j < n; j++) {
                if (matrix[i][j] == 0) continue;
                for (size_t k = 0; k < n; k++) {
                    if (j == k || matrix[i][k] == 0) continue;
                    size_t u = matrix2[j][k];
                    matrix2[j][k] = matrix2[k][j] = 1;
                    if (!check_k5(n - 1, matrix2, i)) {
                        return false;
                    }
                    matrix2[j][k] = matrix2[k][j] = u;
                }
            }
        }
    }
    return true;
}

void kek() {
    string a;
    getline(cin, a);
    size_t m = a.length(), n;
    for (size_t i = 1; i <= 6; i++) {
        if (i * i - i == 2 * m) {
            n = i;
        }
    }
    size_t w = 0;
    vector<vector<size_t>> matrix = vector<vector<size_t>>(n, vector<size_t>(n, 0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            if (a[w] == '1') {
                matrix[i][j] = matrix[j][i] = 1;
            }
            w++;
        }
    }
    bool f = check_k33(n, matrix) && check_k5(n, matrix);
    if (f) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    string t;
    getline(cin, t);
    int tt = stoi(t);
    for (size_t i = 0; i < tt; i++) {
        kek();
    }
    return 0;
};