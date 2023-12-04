#include <iostream>
#include <vector>

using namespace std;

// Функция для решения задачи с использованием жадного алгоритма
vector<int> greedyCoinChange(const vector<int>& coins, int amount, int& iterations) {
    vector<int> result;
    iterations = 0; // Добавляем счетчик итераций

    for (int i = coins.size() - 1; i >= 0; --i) {
        while (amount >= coins[i]) {
            result.push_back(coins[i]);
            amount -= coins[i];
            iterations++; // Увеличиваем счетчик итераций
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Условие задачи
    vector<int> coinValues = { 1, 2, 5, 10, 20, 50, 100, 200 };
    int targetAmount = 0;

    // Простое текстовое меню
    vector<int> result;
    int iterations;
    int choice;
    do {
        cout << "Выберите опцию:" << endl;
        cout << "1. Установить сумму" << endl;
        cout << "2. Решить задачу" << endl;
        cout << "0. Выйти" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите сумму: ";
            cin >> targetAmount;
            break;

        case 2:
            result = greedyCoinChange(coinValues, targetAmount, iterations);

            // Вывод результатов
            cout << "Минимальное количество монет: " << result.size() << endl;
            cout << "Используемые монеты: ";
            for (int coin : result) {
                cout << coin << " ";
            }
            cout << endl;
            cout << "Количество итераций: " << iterations << endl; // Выводим количество итераций
            break;

        case 0:
            cout << "Выход из программы." << endl;
            break;

        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}