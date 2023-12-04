#include <iostream>
#include <vector>

using namespace std;

// ������� ��� ������� ������ � �������������� ������� ���������
vector<int> greedyCoinChange(const vector<int>& coins, int amount, int& iterations) {
    vector<int> result;
    iterations = 0; // ��������� ������� ��������

    for (int i = coins.size() - 1; i >= 0; --i) {
        while (amount >= coins[i]) {
            result.push_back(coins[i]);
            amount -= coins[i];
            iterations++; // ����������� ������� ��������
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "ru");
    // ������� ������
    vector<int> coinValues = { 1, 2, 5, 10, 20, 50, 100, 200 };
    int targetAmount = 0;

    // ������� ��������� ����
    vector<int> result;
    int iterations;
    int choice;
    do {
        cout << "�������� �����:" << endl;
        cout << "1. ���������� �����" << endl;
        cout << "2. ������ ������" << endl;
        cout << "0. �����" << endl;
        cout << "��� �����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "������� �����: ";
            cin >> targetAmount;
            break;

        case 2:
            result = greedyCoinChange(coinValues, targetAmount, iterations);

            // ����� �����������
            cout << "����������� ���������� �����: " << result.size() << endl;
            cout << "������������ ������: ";
            for (int coin : result) {
                cout << coin << " ";
            }
            cout << endl;
            cout << "���������� ��������: " << iterations << endl; // ������� ���������� ��������
            break;

        case 0:
            cout << "����� �� ���������." << endl;
            break;

        default:
            cout << "������������ �����. ���������� �����." << endl;
        }
    } while (choice != 0);

    return 0;
}