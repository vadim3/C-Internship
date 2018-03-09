#include <cmath>
#include <vector>
#include <iostream>
#include <tuple>
#include <chrono>

using namespace std;

vector<int> primes({ 2, 3, 5, 7, 11, 13 });

void genPrimes(int max) {
    for (int n = 15; n <= max; n += 2) {
        auto it = primes.begin() + 1;
        for (;;) {
            if (it == primes.end()) {
                primes.push_back(n);
                break;
            }
            if (n % *it == 0) break;
            ++it;
        }
    }
}

int s(int n);

int main() {
    auto t1 = chrono::high_resolution_clock::now();
    constexpr int m = 9800000;
    constexpr int n = 9900000;
    genPrimes(static_cast<int>(sqrt(n)));
    int64_t result = 0;
    for (auto i = m; i <= n; ++i)
    {
        result += s(i);
    }
    cout << result << endl;
    auto t2 = chrono::high_resolution_clock::now();
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms" << endl;
}

vector<tuple<int, int>> factorize(int n);
int factorial_power(int m, int p);

int s(int n)
{
    auto factors = factorize(n);
    int lb = 1;
    for (auto v: factors)
    {
        int p;
        int count;
        tie(p, count) = v;
        int lb_value = factorial_power(lb, p);
        if (lb_value >= count) continue;
        int ub = p * count;
        if (count < p)
        {
            lb = ub;
            continue;
        }
        while (lb < ub)
        {
            int median = lb + (ub - lb) / 2;
            int m_value = factorial_power(median, p);
            if (m_value < count)
            {
                lb = median + 1;
            }
            else
            {
                ub = median;
            }
        }
    }
    return lb;
}

int factorial_power(int m, int p)
{
    int result = 0;
    while (m >= p)
    {
        result += m / p;
        m /= p;
    }
    return result;
}

vector<tuple<int, int>> factorize(int n) {
    vector<tuple<int, int>> result;
    for (auto p : primes) {
        int count = 0;
        while (n % p == 0)
        {
            ++count;
            n /= p;
        }
        if (count > 0)
        {
            result.push_back(make_tuple(p, count));
        }
        if (p > n) break;
    }
    if (n > 1)
    {
        result.push_back(make_tuple(n, 1));
    }
    return result;
}