#include <iostream>
#include <vector>
#include <cmath>

std::pair<std::pair<long long, long long>, long long> extgcd(long long a, long long b) {
    if (b == 0) {
        return {{a, 1}, 0};
    } else {
        auto v = extgcd(b, a % b);
        return {{v.first.second, v.first.first - (a / b) * v.first.second}, v.second};
    }
}

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
        return (((x + y) % mod) + mod) % mod;
    }
    coefficient_t mmul(const coefficient_t &x, const coefficient_t &y) {
        return (((x * y) % mod) + mod) % mod;
    }
    coefficient_t mdiv(const coefficient_t &x, const coefficient_t &y) {
        return mmul(x, extgcd(y, mod).first.first);
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

    polynom differentiate() {
        polynom result;
        result.coefficients.resize(rang() + 1);
        for (size_t i = 0; i <= rang() - 1; i++) {
            result.coefficients[i] = mmul(i + 1, coefficients[i + 1]);
        }
        return result;
    }
    polynom integrate() {
        polynom result;
        result.coefficients.resize(rang() + 3);
        result.coefficients[0] = 0;
        for (size_t i = 1; i <= rang() + 1; i++) {
            result.coefficients[i] = mdiv(coefficients[i - 1], i);
        }
        return result;
    }

    polynom sqrt(size_t k) {
        polynom result;
        result.coefficients.resize(k + 1, 0);
        result.coefficients[0] = 1;
        for (size_t i = 1; i <= k; i++) {
            coefficient_t x = (i <= rang()) ? coefficients[i] : 0;
            for (size_t j = 1; j < i; j++) {
                x = msum(x, -mmul(result.coefficients[j], result.coefficients[i - j]));
            }
            result.coefficients[i] = mdiv(x, 2);
        }
        return result;
    }
    polynom exp(size_t k) {
        polynom d = differentiate();
        polynom result;
        result.coefficients.resize(k + 1, 0);
        result.coefficients[0] = 1;
        for (size_t i = 1; i <= k; i++) {
            coefficient_t x = 0;
            for (size_t j = 0; j < i; j++) {
                if (i - j - 1 >= d.coefficients.size()) continue;
                x = msum(x, mmul(result.coefficients[j], d.coefficients[i - j - 1]));
            }
            result.coefficients[i] = mdiv(x, i);
        }
        return result;
    }
    polynom log(size_t k) {
        polynom d = differentiate();
        polynom e({1});
        e.add(*this);
        d.divide(e, k - 1);
        auto x = d.integrate();
        if (k == 1) x.coefficients.pop_back();
        return x;
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

    polynom sqrt = a.sqrt(m);
    sqrt.write();

    polynom exp = a.exp(m);
    exp.write();

    polynom log = a.log(m);
    log.write();

    return 0;
}