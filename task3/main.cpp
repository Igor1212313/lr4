#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

using ull = unsigned long long;

bool isPrime(ull n) {
    if (n < 2) {
        return false;
    }

    if (n == 2) {
        return true;
    }

    if (n % 2 == 0) {
        return false;
    }

    for (ull i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

ull modMultiply(ull a, ull b, ull mod) {
    return (__uint128_t)a * b % mod;
}

ull modSquare(ull x, ull mod) {
    return modMultiply(x, x, mod);
}

int main() {
    ull p, q, x;
    int n;

    cout << "Генератор BBS\n";
    cout << "Введите p: ";
    cin >> p;

    cout << "Введите q: ";
    cin >> q;

    cout << "Введите x: ";
    cin >> x;

    cout << "Введите количество чисел N: ";
    cin >> n;

    if (!isPrime(p)) {
        cout << "Ошибка: p должно быть простым числом.\n";
        return 1;
    }

    if (!isPrime(q)) {
        cout << "Ошибка: q должно быть простым числом.\n";
        return 1;
    }

    if (p % 4 != 3) {
        cout << "Ошибка: p должно быть сравнимо с 3 по модулю 4.\n";
        return 1;
    }

    if (q % 4 != 3) {
        cout << "Ошибка: q должно быть сравнимо с 3 по модулю 4.\n";
        return 1;
    }

    if (p == q) {
        cout << "Ошибка: p и q должны быть различными.\n";
        return 1;
    }

    if (n <= 0) {
        cout << "Ошибка: N должно быть положительным.\n";
        return 1;
    }

    ull m = p * q;

    if (gcd(x, m) != 1) {
        cout << "Ошибка: x должно быть взаимно простым с M.\n";
        return 1;
    }

    vector<ull> sequence;
    sequence.reserve(n);

    ull current = modSquare(x, m);

    for (int i = 0; i < n; ++i) {
        sequence.push_back(current);
        current = modSquare(current, m);
    }

    cout << "\nПараметры генератора:\n";
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "M = p * q = " << m << endl;
    cout << "x = " << x << endl;
    cout << "N = " << n << endl;

    cout << "\nСгенерированная последовательность BBS:\n";
    for (ull value : sequence) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}
