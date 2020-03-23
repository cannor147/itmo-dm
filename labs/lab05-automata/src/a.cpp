#include <iostream>
#include <vector>

using namespace std;

struct Transition {
    int destination;
    char symbol;

    Transition(int destination, char symbol) {
        this->destination = destination;
        this->symbol = symbol;
    }
};

vector<bool> final_states;
vector<vector<Transition>> transitions;
int current_state;

int make_transition(char symbol) {
    int source = current_state;
    for (int i = 0; i < transitions[source].size(); i++) {
        if (transitions[source][i].symbol == symbol) {
            return transitions[source][i].destination;
        }
    }
    return -1;
}

bool check_word(string word) {
    current_state = 0;
    for (int i = 0; i < word.length(); i++) {
        current_state = make_transition(word[i]);
        if (current_state == -1) return false;
    }
    return final_states[current_state];
}

int main() {
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string word;
    int n, m, k;
    cin >> word;
    cin >> n >> m >> k;
    final_states.resize(n);
    transitions.resize(n);
    fill(final_states.begin(), final_states.end(), false);
    for (int i = 0; i < k; i++) {
        int d;
        cin >> d;
        final_states[d - 1] = true;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        transitions[a - 1].push_back(Transition(b - 1, c));
    }
    string message = check_word(word) ? "Accepts" : "Rejects";
    cout << message;
    return 0;
}