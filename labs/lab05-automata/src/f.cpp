#include <iostream>
#include <vector>
#include <map>

using namespace std;

class DFA {

private:

    struct State {
        bool is_final, is_devilish;
        map<char, int> transitions;

        State() {
            this->is_final = false;
            this->is_devilish = false;
        }

        void make_final() {
            this->is_final = true;
        }

        void make_devilish() {
            this->is_devilish = true;
        }

        void add_transition(int destination, char symbol) {
            transitions.insert({symbol, destination});
        }
    };

    vector<State> states;

    bool rec(vector<bool> &visited, DFA &d2, int u, int v) {
        visited[v] = true;
        if (states[u].is_final != d2.states[v].is_final) return false;
        bool result = true;
        for (const auto &j : states[u].transitions) {
            if (d2.states[v].transitions.count(j.first) == 0) return false;
            int u_child = j.second;
            int v_child = states[v].transitions.find(j.first)->second;
            if (states[u].is_devilish != d2.states[v].is_devilish) return false;
            if (!(visited[u])) {
                result &= rec(visited, d2, u_child, v_child);
            }
        }
        return result;
    }

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

    void count_devilish() {
        for (int i = 0; i < states.size(); i ++) {
            bool tmp = false;
            for (const auto &j : states[i].transitions) {
                if (j.second != i) tmp = true;
                if (tmp) break;
            }
            if (!(tmp)) states[i].make_devilish();
        }
    }

    bool is_isomorphic(DFA &d2) {
        vector<bool> visited(size());
        fill(visited.begin(), visited.end(), false);
        return rec(visited, d2, 0, 0);
    }
};

int main() {
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);
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
            d[j].add_transition(a - 1, b - 1, c);
        }
        d[j].count_devilish();
    }
    string message = (d[0].is_isomorphic(d[1])) ? "YES" : "NO";
    cout << message;
    return 0;
}