#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

const double EPS = 1e-4;

double f(double x) {
    return x * x + exp(x) - 2.0;
}

double df(double x) {
    return 2.0 * x + exp(x);
}

double phiNegative(double x) {
    return -sqrt(2.0 - exp(x));
}

double phiPositive(double x) {
    return log(2.0 - x * x);
}

double bisection(double a, double b) {
    int n = 0;

    cout << "\nМетод половинного деления\n";
    cout << "N\tan\t\tbn\t\tbn - an\n";

    while (fabs(b - a) > EPS) {
        cout << n << "\t"
             << fixed << setprecision(6) << a << "\t"
             << b << "\t"
             << fabs(b - a) << endl;

        double c = (a + b) / 2.0;

        if (f(a) * f(c) <= 0) {
            b = c;
        } else {
            a = c;
        }

        n++;
    }

    cout << n << "\t"
         << fixed << setprecision(6) << a << "\t"
         << b << "\t"
         << fabs(b - a) << endl;

    return (a + b) / 2.0;
}

double newton(double x0) {
    int n = 0;
    double x1;

    cout << "\nМетод Ньютона\n";
    cout << "N\txn\t\txn+1\t\txn+1 - xn\n";

    do {
        x1 = x0 - f(x0) / df(x0);

        cout << n << "\t"
             << fixed << setprecision(6) << x0 << "\t"
             << x1 << "\t"
             << fabs(x1 - x0) << endl;

        x0 = x1;
        n++;

    } while (fabs(f(x0)) > EPS);

    return x0;
}

double simpleIteration(double x0, bool isNegativeRoot) {
    int n = 0;
    double x1;

    cout << "\nМетод простых итераций\n";
    cout << "N\txn\t\txn+1\t\txn+1 - xn\n";

    do {
        if (isNegativeRoot) {
            x1 = phiNegative(x0);
        } else {
            x1 = phiPositive(x0);
        }

        cout << n << "\t"
             << fixed << setprecision(6) << x0 << "\t"
             << x1 << "\t"
             << fabs(x1 - x0) << endl;

        x0 = x1;
        n++;

    } while (fabs(f(x0)) > EPS);

    return x0;
}

int main() {
    cout << fixed << setprecision(6);

    cout << "Уравнение: x^2 + e^x = 2\n";
    cout << "f(x) = x^2 + e^x - 2\n";
    cout << "Точность: " << EPS << endl;

    vector<pair<double, double>> intervals = {
        {-2.0, -1.0},
        {0.0, 1.0}
    };

    for (int i = 0; i < intervals.size(); i++) {
        double a = intervals[i].first;
        double b = intervals[i].second;

        cout << "\n====================================\n";
        cout << "Корень " << i + 1 << " на отрезке ["
             << a << "; " << b << "]\n";

        double rootBisection = bisection(a, b);

        double x0Newton = b;
        if (i == 1) {
            x0Newton = a;
        }

        double rootNewton = newton(x0Newton);

        double x0Iter = (a + b) / 2.0;
        double rootIteration = simpleIteration(x0Iter, i == 0);

        cout << "\nИтог для корня " << i + 1 << ":\n";
        cout << "Метод половинного деления: " << rootBisection << endl;
        cout << "Метод Ньютона:             " << rootNewton << endl;
        cout << "Метод простых итераций:    " << rootIteration << endl;
    }

    cout << "\nСравнение методов:\n";
    cout << "Метод половинного деления сходится надежно, но медленнее.\n";
    cout << "Метод Ньютона сходится быстрее всего при хорошем начальном приближении.\n";
    cout << "Метод простых итераций проще по формуле, но обычно медленнее метода Ньютона.\n";

    return 0;
}
