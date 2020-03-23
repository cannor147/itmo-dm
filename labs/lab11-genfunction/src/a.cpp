#include <iostream>
#include <vector>
#include <cmath>

class polynom {

    using coefficient_t = long long;

private:
    const coefficient_t mod = 998244353;
    std::vector<coefficient_t> coefficients;

    void normilize() {
        auto &c = coefficients;
        while (c.size() > 1 && c[c.size() - 1] == 0 && c[c.size() - 2] == 0) {
            c.pop_back();
        }
    }
    coefficient_t msum(const coefficient_t &x, const coefficient_t &y) {
        return (x + y + mod) % mod;
    }
    coefficient_t mmul(const coefficient_t &x, const coefficient_t &y) {
        return (((x + mod) % mod) * ((y + mod) % mod)) % mod;
    }

public:
    polynom() {
        coefficients.emplace_back(0);
    }
    polynom(polynom const &p) {
        this->coefficients = p.coefficients;
    }
    polynom(std::vector<coefficient_t> vec) {
        for (auto &i : vec) {
            coefficients.emplace_back(i);
        }
        coefficients.emplace_back(0);
        normilize();
    }

    size_t is_zero() {
        return coefficients.size() == 1;
    }
    size_t rang() {
        if (is_zero()) return 0;
        return coefficients.size() - 2;
    }

    void add(polynom p) {
        coefficients.resize(std::max(p.rang(), rang()) + 2, 0);
        for (size_t i = 0; i <= p.rang(); i++) {
            coefficients[i] = msum(coefficients[i], p.coefficients[i]);
        }
        normilize();
    }
    void multiply(polynom p) {
        size_t len = rang();
        coefficients.resize(rang() + p.rang() + 2, 0);
        for (int i = len; i >= 0; i--) {
            coefficient_t x = coefficients[i];
            for (size_t j = 0; j <= p.rang(); j++) {
                coefficients[i + j] = msum(coefficients[i + j], mmul(p.coefficients[j], x));
            }
            coefficients[i] = msum(coefficients[i], -x);
        }
        normilize();
    }
    void divide(polynom p, size_t k) {
        coefficients.resize(k + 1);
        for (size_t i = 0; i < k; i++) {
            coefficient_t x = 0;
            for (size_t j = 0; j < i; j++) {
                if (i - j >= p.coefficients.size()) continue;
                x = msum(x, mmul(coefficients[j], p.coefficients[i - j]));
            }
            coefficients[i] = msum(coefficients[i], -x);
        }
    }

    void write() {
        for (size_t i = 0; i <= rang(); i++) {
            std::cout << coefficients[i] << " ";
        }
        std::cout << std::endl;
    }
    void scan(size_t s) {
        coefficients.resize(s + 1);
        for (size_t i = 0; i < s; i++) {
            std::cin >> coefficients[i];
        }
        coefficients.back() = 0;
    }
};

int main() {
    size_t n, m;
    std::cin >> n >> m;
    polynom a, b;
    a.scan(n + 1);
    b.scan(m + 1);

    polynom sum(a), pr(a), d(a);
    sum.add(b);
    pr.multiply(b);
    d.divide(b, 1000);

    std::cout << sum.rang() << std::endl;
    sum.write();

    std::cout << pr.rang() << std::endl;
    pr.write();

    d.write();
    return 0;
}