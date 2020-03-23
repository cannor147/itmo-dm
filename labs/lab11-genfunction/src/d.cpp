#include <iostream>
#include <vector>
#include <stack>

unsigned long long c(unsigned long long n, int k) {
    if (k > n) return 0;
    if (k == n) return 1;
    unsigned long long x = 1;
    for (int i = 1; i <= k; i++) {
        x *= (n - i + 1);
        x /= i;
    }
    return x;
}

unsigned long long c(int i, int n, int k, std::vector<unsigned long long> &w) {
    if (n > 0) {
        return c(i, n - 1, k, w) + c(i, n - 1, k - 1, w);
    } else {
        if (k > w[i]) return 0;
        return c(w[i], k);
    }
}

unsigned long long m(int n, int k, std::vector<unsigned long long> &w) {
    if (n == 0) return 1;
    if (k == 0) return 0;
    unsigned long long result = 0;
    for (int i = 0; i <= n / k; i++) {
        unsigned long long v = m(n - i * k, k - 1, w);
        if (v == 0) continue;
        unsigned long long u = c(k, i - 1, i, w);
        if (u == 0) continue;

        result += u * v;
    }
    return result;
}

std::vector<unsigned long long> count_mset(std::vector<unsigned long long> &w) {
    std::vector<unsigned long long> result(7, 0);
    for (size_t i = 0; i < 7; i++) {
        result[i] = m(i, i, w);
    }
    return result;
}

class construct_object {

private:
    int var;
    std::vector<construct_object> vec;

public:
    explicit construct_object(int var = 0) {
        this->var = var;
    }
    std::string type() {
        switch (var) {
            case 0: return "B";
            case 1: return "P";
            case 2: return "L";
            case 3: return "S";
        }
        return "error";
    }
    void write() {
        std::cout << type();
        if (var == 0) return;
        std::cout << "(";
        for (int i = vec.size() - 1; i >= 0; i--) {
            vec[i].write();
            if (i != 0) std::cout << ",";
        }
        std::cout << ")";

    }

    void add(construct_object &o) {
        vec.emplace_back(o);
    }
    void add(std::vector<construct_object> &v) {
        for (auto &i : v) {
            add(i);
        }
    }
    std::vector<unsigned long long> count() {
        std::vector<unsigned long long> ans(7, 0);
        if (var == 0) {
            ans[1] = 1;
        } else if (var == 1) {
            auto u = vec[0].count(), v = vec[1].count();
            for (size_t i = 0; i < 7; i++) {
                for (size_t j = 0; j <= i; j++) {
                    ans[i] += u[j] * v[i - j];
                }
            }
        } else if (var == 2) {
            std::vector<unsigned long long> w(7, 0);
            for (auto &i : vec) {
                auto x = i.count();
                for (size_t j = 0; j < 7; j++) {
                    w[j] += x[j];
                }
            }
            ans[0] = 1;
            for (size_t i = 1; i < 7; i++) {
                for (size_t j = 1; j <= i; j++) {
                    ans[i] += w[j] * ans[i - j];
                }
            }
        } else if (var == 3) {
            std::vector<unsigned long long> w(7, 0);
            for (auto &i : vec) {
                auto x = i.count();
                for (size_t j = 0; j < 7; j++) {
                    w[j] += x[j];
                }
            }
            ans = count_mset(w);
        }
        return ans;
    }
};

int main() {
    std::string str;
    std::cin >> str;

    int level = 0;
    std::stack<std::pair<construct_object, int>> stack;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            level++;
        } else if (str[i] == ')') {
            std::vector<construct_object> kek;
            while (stack.top().second == level) {
                kek.emplace_back(stack.top().first);
                stack.pop();
            }
            stack.top().first.add(kek);
            level--;
        } else if (str[i] == 'B') {
            stack.emplace(construct_object(0), level);
        } else if (str[i] == 'P') {
            stack.emplace(construct_object(1), level);
        } else if (str[i] == 'L') {
            stack.emplace(construct_object(2), level);
        } else if (str[i] == 'S') {
            stack.emplace(construct_object(3), level);
        }
    }
    auto x = stack.top().first.count();
    for (auto y : x) {
        std::cout << y << " ";
    }
//    stack.top().first.write();
    return 0;
}