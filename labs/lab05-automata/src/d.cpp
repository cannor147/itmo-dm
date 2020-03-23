#include <iostream>
#include <vector>
#include <map>

using namespace std;

class DFA {

private:

    struct State {
        bool is_final;
        map<char, int> transitions;
        vector<int> words;

        State() {
            this->is_final = false;
        }

        void make_final() {
            this->is_final = true;
        }

        void fwz(unsigned long length) {
            this->words.resize(length + 1);
            fill(this->words.begin(), this->words.end(), 0);
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

    void add_transition(int source, int destination, char symbol) {
        states[source].add_transition(destination, symbol);
    }

    void make_final(int index) {
        states[index].make_final();
    }

    int count_words(int length) {
        for (int i = 0; i < states.size(); i++) {
            states[i].fwz(length);
        }
        states[0].words[0] = 1;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < states.size(); j++) {
                for (auto &k : states[j].transitions) {
                    states[k.second].words[i + 1] += states[j].words[i];
                    states[k.second].words[i + 1] %= (int) 1e9 + 7;
                }
            }
        }
        int s = 0;
        for (int j = 0; j < states.size(); j++) {
            if (states[j].is_final) {
                s += states[j].words[length];
                s %= (int) 1e9 + 7;
            }
        }
        return s;
    }
};

int main() {
    freopen("problem4.in", "r", stdin);
    freopen("problem4.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k, l, a, b;
    char c;
    cin >> n >> m >> k >> l;
    DFA d = DFA(n);
    for (int i = 0; i < k; i++) {
        cin >> a;
        d.make_final(a - 1);
    }
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        d.add_transition(a - 1, b - 1, c);
    }
    cout << d.count_words(l);
    return 0;
}