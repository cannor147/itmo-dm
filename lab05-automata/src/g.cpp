#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

set<char> alphabet;

class DFA {

private:

    struct State {
        bool is_final;
        map<char, int> transitions;

        State() {
            this->is_final = false;
        }

        void make_final() {
            this->is_final = true;
        }

        void add_transition(int destination, char symbol) {
            transitions.insert({symbol, destination});
        }
    };

    vector<State> states;

public:

    DFA(int size) {
        states.resize(size);
    }

    int size() {
        return states.size();
    }

    void add_transition(int source, int destination, char symbol) {
        states[source].add_transition(destination, symbol);
    }

    void make_final(int index) {
        states[index].make_final();
    }

    bool is_equivalent(DFA &d2) {
        states.emplace_back();
        d2.states.emplace_back();
        vector<vector<bool>> visited(size(), vector<bool>(d2.size(), false));
        queue<pair<int, int>> my_queue;
        my_queue.push({0, 0});
        while (!(my_queue.empty())) {
            int u = my_queue.front().first, v = my_queue.front().second;
            if (states[u].is_final != d2.states[v].is_final) return false;
            visited[u][v] = true;
            for (auto &c : alphabet) {
                int u_child = (states[u].transitions.count(c) != 0) ? states[u].transitions.find(c)->second : size() - 1;
                int v_child = (d2.states[v].transitions.count(c) != 0) ? d2.states[v].transitions.find(c)->second : d2.size() - 1;
                if (!(visited[u_child][v_child])) my_queue.push({u_child, v_child});
            }
            my_queue.pop();
        }
        return true;
    }
};

int main() {
    freopen("equivalence.in", "r", stdin);
    freopen("equivalence.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k, a, b;
    char c;
    vector<DFA> d;
    for (int j = 0; j < 2; j++) {
        cin >> n >> m >> k;
        d.emplace_back(n);
        for (int i = 0; i < k; i++) {
            cin >> a;
            d[j].make_final(a - 1);
        }
        for (int i = 0; i < m; i++) {
            cin >> a >> b >> c;
            alphabet.insert(c);
            d[j].add_transition(a - 1, b - 1, c);
        }
    }
    string message = (d[0].is_equivalent(d[1])) ? "YES" : "NO";
    cout << message;
    return 0;
}