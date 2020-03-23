#include <iostream>
#include <vector>

const long long mod = 104857601;

long long msum(const long long &x, const long long &y) {
    return (((x + y) % mod) + mod) % mod;
}
long long mmul(const long long &x, const long long &y) {
    return (((x * y) % mod) + mod) % mod;
}

int main() {
    int k;
    long long n;
    std::cin >> k >> n;
    std::vector<long long> a(2 * k, 0), c(k, 0), q(k + 1, 0);
    for (size_t i = 0; i < k; i++) {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < k; i++) {
        std::cin >> c[i];
    }

    n--;
    q[0] = 1;
    for (size_t i = 1; i <= k; i++) {
        q[i] = msum(-c[i - 1], 0);
        std::cout << q[i] << " ";
    }
    while (n >= k) {
        for (size_t i = k; i < 2 * k; i++) {
            a[i] = 0;
            for (size_t j = 1; j <= k; j++) {
                a[i] = msum(a[i], -mmul(q[j], a[i - j]));
            }
        }

        std::vector<long long> r(2 * k, 0);
        r[0] = 1;
        for (size_t i = 0; i < 2 * k; i++) {
//            if (i % 2 == 1) continue;
            for (size_t j = 0; j <= i; j++) {
                long long x = ((i - j) % 2 == 1) ? -1 : 1;
                r[i] = msum(r[i], mmul(x * q[j], q[i - j]));
            }
        }
        for (size_t i = 0; i < k; i++) {
            q[i] = r[i * 2];
        }

        int x = (n % 2 == 1) ? 1 : 0;
        for (size_t i = 0; i < k; i++) {
            a[i] = a[2 * i + x];
        }
        n /= 2;
    }
    std::cout << a[n];
    return 0;
}