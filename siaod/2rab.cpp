#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// ������� ��� �������� ���������� ����� � ����������� �������
void createTextFile(const string& fileName) {
    ofstream file(fileName);

    if (!file.is_open()) {
        cerr << "������ �������� ����� ��� ������: " << fileName << endl;
        return;
    }

    cout << "������� ���������� ����� (��� ���������� ����� ������� 0):" << endl;
    int num;
    while (cin >> num && num != 0) {
        file << num << endl;
    }

    cout << "���� '" << fileName << "' ������." << endl;

    file.close();
}

// ������� ��� ������ ����������� ���������� �����
void displayTextFile(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "������ �������� ����� ��� ������: " << fileName << endl;
        return;
    }

    cout << "���������� ����� '" << fileName << "':" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// ������� ��� ���������� ����� ������ � ����� �����
void appendToTextFile(const string& fileName, int num) {
    ofstream file(fileName, ios::app);

    if (!file.is_open()) {
        cerr << "������ �������� ����� ��� ���������� ������: " << fileName << endl;
        return;
    }

    file << num << endl;
    cout << "������ " << num << " ��������� � ���� '" << fileName << "'." << endl;

    file.close();
}

// ������� ��� ������ �������� ����� �� ��� ����������� ������
int readNumberByIndex(const string& fileName, int index) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "������ �������� ����� ��� ������: " << fileName << endl;
        return -1;
    }

    int number;
    int currentIndex = 0;
    while (file >> number) {
        currentIndex++;
        if (currentIndex == index) {
            file.close();
            return number;
        }
    }

    cerr << "����� � ���������� ������� " << index << " �� ������� � �����." << endl;
    file.close();
    return -1;
}

// ������� ��� ����������� ���������� ����� � �����
int countNumbersInFile(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "������ �������� ����� ��� ������: " << fileName << endl;
        return -1;
    }

    int count = 0;
    int number;
    while (file >> number) {
        count++;
    }

    file.close();
    return count;
}

int main() {
    string fileName;

    cout << "������� ��� �����: ";
    cin >> fileName;

    int choice;
    do {
        cout << "�������� ��������:" << endl;
        cout << "1. ������� ��������� ���� � ����������� �������" << endl;
        cout << "2. ������� ���������� ���������� �����" << endl;
        cout << "3. �������� ����� ������ � ����� �����" << endl;
        cout << "4. ��������� �������� ����� �� ����������� ������" << endl;
        cout << "5. ���������� ���������� ����� � �����" << endl;
        cout << "0. �����" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            createTextFile(fileName);
            break;
        case 2:
            displayTextFile(fileName);
            break;
        case 3:
            int numToAdd;
            cout << "������� ����� ��� ����������: ";
            cin >> numToAdd;
            appendToTextFile(fileName, numToAdd);
            break;
        case 4:
            int indexToRead;
            cout << "������� ���������� ����� ����� ��� ������: ";
            cin >> indexToRead;
            int value = readNumberByIndex(fileName, indexToRead);
            if (value != -1) {
                cout << "�������� ����� � ���������� ������� " << indexToRead << ": " << value << endl;
            }
            break;
        case 5:
            int count = countNumbersInFile(fileName);
            if (count != -1) {
                cout << "���������� ����� � �����: " << count << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "�������� �����. ���������� �����." << endl;
        }
    } while (choice != 0);

    return 0;
}
