#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct kek {
    int weight, deadline;
    kek(int weight, int deadline) : weight(weight), deadline(deadline) {}
};
bool operator<(kek &a, kek &b) {
    return a.deadline < b.deadline;
}
bool operator<(const kek &a, const kek &b) {
    return a.weight > b.weight;
}

int main() {
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, d, w, time = 0;
    cin >> n;
    vector<kek> v;
    long long count = 0;
    for (size_t i = 0; i < n; i++) {
        cin >> d >> w;
        count += w;
        kek k(w, d);
        v.push_back(k);
    }
    sort(v.begin(), v.end());
    priority_queue<kek> q;
    for (size_t i = 0; i < n; i++) {
        if (v[i].deadline <= time) {
            if (q.empty()) continue;
            if (q.top().weight < v[i].weight) {
                q.pop();
                q.push(v[i]);
            }
        } else {
            q.push(v[i]);
            time++;
        }
    }
    while (!q.empty()) {
        count -= q.top().weight;
        q.pop();
    }
    cout << count;
}