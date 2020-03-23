#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <bitset>

using namespace std;
const int max_size = 100;

set<char> alphabet;

class DFA {

private:

    struct State {
        bool is_final;
        map<char, int> transitions;
        vector<int> words;
        int components;

        State(int number) {
            this->is_final = false;
            components = number;
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

    int size_of_states;
    vector<State> states;

public:

    DFA() {
        size_of_states = 0;
    }

    int size() {
        return size_of_states;
    }

    int comp(int index) {
        return states[index].components;
    }

    void add_transition(int source, int destination, char symbol) {
        states[source].add_transition(destination, symbol);
    }

    void make_final(int index) {
        states[index].make_final();
    }

    void add_state(int components) {
        states.emplace_back(components);
        size_of_states++;
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
class NFA {

private:

    struct State {
        bool is_final;
        map<char, set<int>> transitions;

        State() {
            this->is_final = false;
        }

        void make_final() {
            this->is_final = true;
        }

        void add_transition(int destination, char symbol) {
            if (transitions.count(symbol) == 0) {
                set <int> tmp;
                transitions.insert({symbol, tmp});
            }
            transitions.find(symbol)->second.insert(destination);
        }
    };

    vector<State> states;

public:

    NFA(int size) {
        states.resize(size);
    }

    void add_transition(int source, int destination, char symbol) {
        states[source].add_transition(destination, symbol);
    }

    void make_final(int index) {
        states[index].make_final();
    }

    void dfa(DFA &e) {
        int size = states.size(), number = 1;
        bitset<max_size> ts;
        ts[0] = true;
        vector<bitset<max_size>> good;
        queue<int> my_queue;
        good.push_back(ts);
        e.add_state(0);
        my_queue.push(0);

        while (!(my_queue.empty())) {
            for (auto &c : alphabet) {
                bitset<max_size> tmp;
                for (int i = 0; i < size; i++) {
                    if (good[my_queue.front()][i] && (states[i].transitions.count(c) > 0)) {
                        for (auto &j : states[i].transitions.find(c)->second) {
                            tmp[j] = true;
                        }
                    }
                }
                bool was = false;
                int i;
                for (i = 0; i < good.size(); i++) {
                    was |= (good[i] == tmp);
                    if (was) break;
                }
                if (!(was)) {
                    e.add_state(number);
                    good.push_back(tmp);
                    my_queue.push(number);
                    i = number;
                    number++;
                }
                e.add_transition(my_queue.front(), i, c);
            }
            my_queue.pop();
        }
        for (int i = 0; i < e.size(); i++) {
            for (int j = 0; j < size; j++) {
                if ((good[e.comp(i)][j]) && (states[j].is_final)) {
                    e.make_final(i);
                }
            }
        }
    }
};

int main() {
    freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k, l, a, b;
    char c;
    cin >> n >> m >> k >> l;
    NFA d = NFA(n);
    for (int i = 0; i < k; i++) {
        cin >> a;
        d.make_final(a - 1);
    }
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        alphabet.insert(c);
        d.add_transition(a - 1, b - 1, c);
    }
    DFA e;
    d.dfa(e);
    cout << e.count_words(l);
    return 0;
}