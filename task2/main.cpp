#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>

using namespace std;

void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    // Генератор minstd_rand по методичке (вариант 14 -> вариант 4)
    random_device rd;
    minstd_rand gen(rd());
    uniform_int_distribution<int> dist(10, 100);

    int n;
    cout << "Введите размер массива (n >= 10): ";
    cin >> n;

    if (n < 10) {
        cout << "Ошибка: n должно быть не меньше 10." << endl;
        return 1;
    }

    // 1. Генерация массива
    vector<int> a(n);
    for (int& x : a) {
        x = dist(gen);
    }

    cout << "\nИсходный массив:\n";
    printArray(a);

    // 2. Минимальный элемент и сумма остатков
    int minValue = *min_element(a.begin(), a.end());

    int remainderSum = 0;
    for (int x : a) {
        remainderSum += x % minValue;
    }

    cout << "\nМинимальный элемент: " << minValue << endl;
    cout << "Сумма остатков от деления на минимальный элемент: "
         << remainderSum << endl;

    // 3. Самая длинная непрерывная возрастающая последовательность
    int bestStart = 0;
    int bestLength = 1;

    int currentStart = 0;
    int currentLength = 1;

    for (int i = 1; i < n; ++i) {
        if (a[i] > a[i - 1]) {
            ++currentLength;
        } else {
            if (currentLength > bestLength) {
                bestLength = currentLength;
                bestStart = currentStart;
            }

            currentStart = i;
            currentLength = 1;
        }
    }

    if (currentLength > bestLength) {
        bestLength = currentLength;
        bestStart = currentStart;
    }

    vector<int> increasingSequence(
        a.begin() + bestStart,
        a.begin() + bestStart + bestLength
    );

    cout << "\nСамая длинная непрерывная возрастающая последовательность:\n";
    cout << "Размер последовательности: "
         << increasingSequence.size() << endl;
    cout << "Элементы последовательности:\n";
    printArray(increasingSequence);

    // 4. Элементы больше среднего
    double average =
        accumulate(a.begin(), a.end(), 0.0) / a.size();

    vector<int> greaterThanAverage;

    for (int x : a) {
        if (x > average) {
            greaterThanAverage.push_back(x);
        }
    }

    sort(
        greaterThanAverage.begin(),
        greaterThanAverage.end(),
        greater<int>()
    );

    int sumGreater =
        accumulate(
            greaterThanAverage.begin(),
            greaterThanAverage.end(),
            0
        );

    cout << "\nСреднее арифметическое: "
         << fixed << setprecision(2)
         << average << endl;

    cout << "Элементы больше среднего значения (по убыванию):\n";
    printArray(greaterThanAverage);

    cout << "Количество элементов в новом массиве: "
         << greaterThanAverage.size() << endl;

    cout << "Сумма элементов нового массива: "
         << sumGreater << endl;

    // 5. Массив длиной N x 8 по рисунку
    cout << "\nМассив длиной N x 8 по рисунку:\n";

    vector<int> specialArray;
    specialArray.reserve(n * 8);

    int value = 100;
    specialArray.push_back(value);

    for (int i = 1; i < n * 8; ++i) {
        // Приращения: 10, 20, 30, ..., 100, 10, 20, ...
        int increment = ((i - 1) % 10 + 1) * 10;
        value += increment;
        specialArray.push_back(value);
    }

    for (int i = 0; i < n * 8; ++i) {
        cout << setw(6) << specialArray[i];

        if ((i + 1) % 8 == 0) {
            cout << endl;
        }
    }

    return 0;
}
