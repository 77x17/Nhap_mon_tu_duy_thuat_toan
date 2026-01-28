#include <iostream>
#include <vector>

using namespace std;

vector<bool> sieve(int max) {
    vector<bool> is_prime(max + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= max; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

int g(int n, const vector<bool>& is_prime) {
    int count = 0;
    int sum = 2 * n;
    for (int p = 2; p <= sum / 2; ++p) {
        int q = sum - p;
        if (is_prime[p] && is_prime[q] && p != q) {
            ++count;
        }
    }
    return count;
}

int main() {
    int n;
    cin >> n;

    vector<bool> is_prime;
    is_prime = sieve(2 * n);

    int result = 0;
    for (int i = 2; i <= n; ++i) {
        result += g(i, is_prime);
    }

    cout << result << endl;

    return 0;
}

// 2, 3, 5, 7, 11, 13, 17
// g(4) -> 8  = 3 + 5           => f(4) = 1
// g(5) -> 10 = 3 + 7           => f(5) = 2
// g(6) -> 12 = 5 + 7           => f(6) = 3
// g(7) -> 14 = 3 + 11          => f(7) = 4
// g(8) -> 16 = 3 + 13 = 5 + 11 => f(8) = 6
// g(9) -> 18 = 5 + 13 = 7 + 11 => f(9) = 8