#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;

// Функция вывода массива
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    // Генератор случайных чисел
    // Для варианта 14 используется генератор minstd_rand
    random_device rd;
    minstd_rand gen(rd());

    // Диапазон основного массива: [-200; 200]
    uniform_int_distribution<int> distMain(-200, 200);

    // Диапазон второго массива: [0; 10]
    uniform_int_distribution<int> distSmall(0, 10);

    int n;

    cout << "Введите размер основного массива (n >= 10): ";
    cin >> n;

    if (n < 10) {
        cout << "Ошибка: n должно быть не меньше 10." << endl;
        return 1;
    }

    // Пункт 1
    // Создание и заполнение массива случайными числами
    vector<int> arr(n);

    for (int& x : arr) {
        x = distMain(gen);
    }

    cout << "\nИсходный массив:\n";
    printArray(arr);

    // Пункт 2
    // Подсчет четных и нечетных элементов
    int evenCount = 0;
    int oddCount = 0;

    for (int x : arr) {
        if (x % 2 == 0) {
            ++evenCount;
        } else {
            ++oddCount;
        }
    }

    cout << "\nКоличество четных элементов: "
         << evenCount << endl;

    cout << "Количество нечетных элементов: "
         << oddCount << endl;

    // Копия массива для сортировки
    vector<int> sortedArray = arr;

    // Если четных больше — сортировка по убыванию
    if (evenCount > oddCount) {

        sort(sortedArray.begin(),
             sortedArray.end(),
             greater<int>());

        cout << "\nЧетных элементов больше."
             << " Массив отсортирован по убыванию:\n";

        printArray(sortedArray);
    }

    // Если нечетных больше — сортировка по возрастанию
    else if (oddCount > evenCount) {

        sort(sortedArray.begin(),
             sortedArray.end());

        cout << "\nНечетных элементов больше."
             << " Массив отсортирован по возрастанию:\n";

        printArray(sortedArray);
    }

    // Если количество одинаковое
    else {
        cout << "\nКоличество четных и нечетных элементов одинаково."
             << "\nСортировка не требуется.\n";
    }

    // Пункт 3
    // Циклический сдвиг массива на 2 элемента вправо
    vector<int> shiftedArray = arr;

    rotate(shiftedArray.rbegin(),
           shiftedArray.rbegin() + 2,
           shiftedArray.rend());

    cout << "\nМассив после циклического сдвига"
         << " на 2 элемента вправо:\n";

    printArray(shiftedArray);

    // Пункт 4
    // Среднее арифметическое положительных элементов
    int positiveSum = 0;
    int positiveCount = 0;

    for (int x : arr) {
        if (x > 0) {
            positiveSum += x;
            ++positiveCount;
        }
    }

    if (positiveCount == 0) {

        cout << "\nВ массиве нет положительных чисел."
             << endl;
    }
    else {

        double positiveAverage =
            static_cast<double>(positiveSum)
            / positiveCount;

        // Новый массив из чисел,
        // которые больше среднего положительных
        vector<int> greaterThanAverage;

        for (int x : arr) {
            if (x > positiveAverage) {
                greaterThanAverage.push_back(x);
            }
        }

        cout << fixed << setprecision(2);

        cout << "\nСреднее арифметическое"
             << " положительных чисел: "
             << positiveAverage << endl;

        cout << "Числа больше этого"
             << " среднего значения:\n";

        printArray(greaterThanAverage);
    }

    // Пункт 5
    // Создание второго массива
    int m;

    cout << "\nВведите размер второго массива"
         << " (m >= 20): ";

    cin >> m;

    if (m < 20) {
        cout << "Ошибка: m должно быть не меньше 20."
             << endl;
        return 1;
    }

    vector<int> secondArray(m);

    for (int& x : secondArray) {
        x = distSmall(gen);
    }

    cout << "\nВторой массив:\n";
    printArray(secondArray);

    // Подсчет количества повторений
    map<int, int> frequency;

    for (int x : secondArray) {
        ++frequency[x];
    }

    // Поиск числа,
    // которое повторяется меньше всего раз
    int leastFrequentNumber =
        frequency.begin()->first;

    int leastFrequency =
        frequency.begin()->second;

    for (const auto& item : frequency) {

        if (item.second < leastFrequency) {

            leastFrequency = item.second;
            leastFrequentNumber = item.first;
        }
    }

    cout << "\nЧисло, которое повторяется"
         << " меньше всего раз: "
         << leastFrequentNumber << endl;

    cout << "Количество повторений: "
         << leastFrequency << endl;

    // Замена чисел,
    // которые повторяются более двух раз
    for (int& x : secondArray) {

        if (frequency[x] > 2) {
            x = leastFrequentNumber;
        }
    }

    cout << "\nВторой массив после замены"
         << " чисел, повторяющихся"
         << " более двух раз:\n";

    printArray(secondArray);

    return 0;
}
