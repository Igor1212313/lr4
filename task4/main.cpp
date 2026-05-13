#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

    int winner = 1;
    for (int candidate = 2; candidate <= n; ++candidate) {
        if (points[candidate] > points[winner]) {
            winner = candidate;
        }
    }

    return winner;
}

bool isHigher(
    const vector<int>& vote,
    int candidateA,
    int candidateB
) {
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
    cout << "Каждая строка — номера кандидатов от лучшего к худшему.\n";

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

    cout << "Победитель по методу Борда: кандидат "
         << bordaWinner << endl;

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
