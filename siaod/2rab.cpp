#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Функция для создания текстового файла с десятичными числами
void createTextFile(const string& fileName) {
    ofstream file(fileName);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи: " << fileName << endl;
        return;
    }

    cout << "Введите десятичные числа (для завершения ввода введите 0):" << endl;
    int num;
    while (cin >> num && num != 0) {
        file << num << endl;
    }

    cout << "Файл '" << fileName << "' создан." << endl;

    file.close();
}

// Функция для вывода содержимого текстового файла
void displayTextFile(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для чтения: " << fileName << endl;
        return;
    }

    cout << "Содержимое файла '" << fileName << "':" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Функция для добавления новой записи в конец файла
void appendToTextFile(const string& fileName, int num) {
    ofstream file(fileName, ios::app);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для добавления записи: " << fileName << endl;
        return;
    }

    file << num << endl;
    cout << "Запись " << num << " добавлена в файл '" << fileName << "'." << endl;

    file.close();
}

// Функция для чтения значения числа по его порядковому номеру
int readNumberByIndex(const string& fileName, int index) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для чтения: " << fileName << endl;
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

    cerr << "Число с порядковым номером " << index << " не найдено в файле." << endl;
    file.close();
    return -1;
}

// Функция для определения количества чисел в файле
int countNumbersInFile(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для чтения: " << fileName << endl;
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

    cout << "Введите имя файла: ";
    cin >> fileName;

    int choice;
    do {
        cout << "Выберите операцию:" << endl;
        cout << "1. Создать текстовый файл с десятичными числами" << endl;
        cout << "2. Вывести содержимое текстового файла" << endl;
        cout << "3. Добавить новую запись в конец файла" << endl;
        cout << "4. Прочитать значение числа по порядковому номеру" << endl;
        cout << "5. Определить количество чисел в файле" << endl;
        cout << "0. Выйти" << endl;
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
            cout << "Введите число для добавления: ";
            cin >> numToAdd;
            appendToTextFile(fileName, numToAdd);
            break;
        case 4:
            int indexToRead;
            cout << "Введите порядковый номер числа для чтения: ";
            cin >> indexToRead;
            int value = readNumberByIndex(fileName, indexToRead);
            if (value != -1) {
                cout << "Значение числа с порядковым номером " << indexToRead << ": " << value << endl;
            }
            break;
        case 5:
            int count = countNumbersInFile(fileName);
            if (count != -1) {
                cout << "Количество чисел в файле: " << count << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}
