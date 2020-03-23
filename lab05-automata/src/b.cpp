#include <iostream>
#include <vector>
#include <queue>

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
vector<int> last_pos;
vector<vector<Transition>> transitions;
queue<pair<int, int>> current_states;


void make_transitions(char symbol) {
    int position = current_states.front().second;
    while (!(current_states.empty()) && (current_states.front().second == position)) {
        int i = current_states.front().first;
        current_states.pop();
        for (auto &j : transitions[i]) {
            if ((j.symbol == symbol) && (last_pos[j.destination] != position + 1)) {
                current_states.push(make_pair(j.destination, position + 1));
                last_pos[j.destination] = position + 1;
            }
        }
    }
}

bool check_word(string word) {
    current_states.push(make_pair(0, -1));
    for (char i : word) {
        make_transitions(i);
        if (current_states.empty()) return false;
    }
    bool result = false;
    while (!(current_states.empty())) {
        result |= final_states[current_states.front().first];
        current_states.pop();
    }
    return result;

}

int main() {
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string word;
    int n, m, k;
    cin >> word;
    cin >> n >> m >> k;
    final_states.resize(n);
    last_pos.resize(n);
    transitions.resize(n);
    fill(final_states.begin(), final_states.end(), false);
    fill(last_pos.begin(), last_pos.end(), -1);
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