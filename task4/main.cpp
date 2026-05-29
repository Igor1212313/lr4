#include <iostream>
#include <vector>

using namespace std;

// Проверка корректности одного голоса:
// каждый кандидат должен встретиться ровно один раз
bool checkVote(const vector<int>& vote, int n) {
    if ((int)vote.size() != n) {
        return false;
    }

    vector<int> used(n + 1, 0);

    for (int candidate : vote) {
        if (candidate < 1 || candidate > n) {
            return false;
        }

        if (used[candidate]) {
            return false;
        }

        used[candidate] = 1;
    }

    return true;
}

// Метод Борда
// Возвращает номер победителя.
// Если победителя нет из-за равенства баллов, возвращает -1.
int findBordaWinner(const vector<vector<int>>& votes, int n) {
    vector<int> points(n + 1, 0);

    for (const vector<int>& vote : votes) {
        for (int place = 0; place < n; ++place) {
            int candidate = vote[place];
            points[candidate] += n - 1 - place;
        }
    }

    cout << "\nМетод Борда:\n";

    for (int candidate = 1; candidate <= n; ++candidate) {
        cout << "Кандидат " << candidate
             << ": " << points[candidate] << " баллов\n";
    }

    int maxPoints = points[1];

    for (int candidate = 2; candidate <= n; ++candidate) {
        if (points[candidate] > maxPoints) {
            maxPoints = points[candidate];
        }
    }

    vector<int> winners;

    for (int candidate = 1; candidate <= n; ++candidate) {
        if (points[candidate] == maxPoints) {
            winners.push_back(candidate);
        }
    }

    if (winners.size() > 1) {
        cout << "Победитель по методу Борда отсутствует: равенство баллов между кандидатами ";

        for (int candidate : winners) {
            cout << candidate << " ";
        }

        cout << endl;
        return -1;
    }

    return winners[0];
}

// Проверяет, стоит ли candidateA выше candidateB в голосе одного избирателя
bool isHigher(const vector<int>& vote, int candidateA, int candidateB) {
    for (int candidate : vote) {
        if (candidate == candidateA) {
            return true;
        }

        if (candidate == candidateB) {
            return false;
        }
    }

    return false;
}

// Метод Кондорсе
// Возвращает номер победителя.
// Если победителя нет, возвращает -1.
int findCondorcetWinner(const vector<vector<int>>& votes, int n) {
    for (int candidate = 1; candidate <= n; ++candidate) {
        bool winsAll = true;

        for (int opponent = 1; opponent <= n; ++opponent) {
            if (candidate == opponent) {
                continue;
            }

            int candidateWins = 0;
            int opponentWins = 0;

            for (const vector<int>& vote : votes) {
                if (isHigher(vote, candidate, opponent)) {
                    ++candidateWins;
                } else {
                    ++opponentWins;
                }
            }

            if (candidateWins <= opponentWins) {
                winsAll = false;
                break;
            }
        }

        if (winsAll) {
            return candidate;
        }
    }

    return -1;
}

int main() {
    int n, k;

    cout << "Введите количество кандидатов: ";
    cin >> n;

    cout << "Введите количество избирателей: ";
    cin >> k;

    if (n < 2 || k < 1) {
        cout << "Ошибка: кандидатов должно быть не меньше 2, избирателей не меньше 1.\n";
        return 1;
    }

    vector<vector<int>> votes(k, vector<int>(n));

    cout << "\nВведите предпочтения каждого избирателя.\n";
    cout << "Каждая строка - номера кандидатов от лучшего к худшему.\n";

    for (int i = 0; i < k; ++i) {
        cout << "Избиратель " << i + 1 << ": ";

        for (int j = 0; j < n; ++j) {
            cin >> votes[i][j];
        }

        if (!checkVote(votes[i], n)) {
            cout << "Ошибка: некорректное ранжирование у избирателя "
                 << i + 1 << ".\n";
            return 1;
        }
    }

    int bordaWinner = findBordaWinner(votes, n);

    if (bordaWinner != -1) {
        cout << "Победитель по методу Борда: кандидат "
             << bordaWinner << endl;
    }

    cout << "\nМетод Кондорсе:\n";

    int condorcetWinner = findCondorcetWinner(votes, n);

    if (condorcetWinner == -1) {
        cout << "Победитель Кондорсе отсутствует.\n";
    } else {
        cout << "Победитель по методу Кондорсе: кандидат "
             << condorcetWinner << endl;
    }

    return 0;
}
