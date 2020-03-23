#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class graph_dm {

private:
    size_t size;
    vector<vector<char>> matrix;

public:
    void init() {
        cin >> size;
        matrix = vector<vector<char>>(size, vector<char>(size, false));
        string line;
        for (size_t i = 1; i < size; i++) {
            cin >> line;
            for (size_t j = 0; j < line.length(); j++) {
                matrix[i][j] = (line[j] == '1');
                matrix[j][i] = (line[j] != '1');
            }
        }
    }

    deque<size_t> find_hamiltonian_cycle() {
        deque<size_t> result;
        result.push_back(0);
        for (size_t i = 1; i < size; i++) {
            auto it = result.begin();
            for (it = result.begin(); it != result.end(); it++) {
                if (!matrix[*it][i]) {
                    result.insert(it, i);
                    break;
                }
            }
            if (it == result.end()) {
                result.push_back(i);
            }
        }
        if (!matrix[*result.rbegin()][*result.begin()]) {
            stack<size_t> path, insert;
            for (auto it = result.rbegin(); it != result.rend(); it++) {
                if (matrix[*it][*result.begin()]) {
                    break;
                } else {
                    path.push(result.back());
                    result.pop_back();
                }
            }
            while (!path.empty()) {
                size_t j = path.top();
                for (auto it = result.begin(); it != result.end(); it++) {
                    if (matrix[j][*it]) {
                        result.insert(it, j);
                        path.pop();
                        while (!insert.empty()) {
                            result.insert(it, insert.top());
                            insert.pop();
                        }
                        break;
                    }
                }
                if (!path.empty() && j == path.top()) {
                    path.pop();
                    insert.push(j);
                }
            }
        }
        return result;
    }

};

int main() {
    freopen("guyaury.in", "r", stdin);
    freopen("guyaury.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    graph_dm g;
    g.init();
    deque<size_t> ans = g.find_hamiltonian_cycle();
    for (auto it = ans.begin(); it != ans.end(); it++) {
        cout << *it + 1 << " ";
    }
    return 0;
}