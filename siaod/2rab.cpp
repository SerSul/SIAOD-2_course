#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



/*
1. Реализация ввода-вывода на основе файловых потоков С++: ofstream, ifstrim. ++
2. Имя физического файла вводится пользователем и передается в функции
обработки через параметр. ++
3. При открытии файла выполнять контроль его существования и открытия.
Примечание. При отладке программы можете имя физического файла
определить через константу. ++
4. Разработать функции для выполнения операций над текстовым файлом.
1) создание текстового файла средствами текстового редактора кодировки
ASCII, содержащего десятичные числа по несколько чисел на строке;
2) вывод содержимого текстового файла;
3) добавление новой записи в конец файла;
4) прочитать значение числа, указав его порядковый номер в файле, и вернуть
его значение;
5) определить количество чисел в файле.
5. Разработать приложение и выполнить тестирование всех функций.
Приложение должно содержать диалоговый интерфейс на основе текстового
меню.
6. Контроль открытия и существования файла выполнить в основной программе
перед вызовом функции. Перед закрытием файла, проверить отсутствие
ошибок ввода и вывода (метод good)
//

7. Создать модуль и перенести в него все отлаженные функции. Исключить
функции из приложения. Отладить приложение, подключив к нему модуль с
функциями.


8. Разработать функции для реализации дополнительных операций,
определенных вариантом и сохранить их в модуле с остальными функциями.
9. Выполнить тестирование приложения в полном объеме.
*/


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



// Функ-я для создания нового файла из исходного
void createNewFileWithThreeNumbersPerLine(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия исходного файла для чтения: " << inputFileName << endl;
        return;
    }

    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия нового файла для записи: " << outputFileName << endl;
        inputFile.close();
        return;
    }

    int num;
    int count = 0;

    while (inputFile >> num) {
        if (count == 3) {
            outputFile << endl; // Переход на некст строку после трех чисел
            count = 0;
        }
        outputFile << num << " ";
        count++;
    }

    inputFile.close();
    outputFile.close();

    cout << "Создан новый файл '" << outputFileName << "' с по три числа на строке." << endl;
}


int main() {
    setlocale(LC_ALL, "ru");
    string fileName;

    cout << "Введите имя файла: ";
    cin >> fileName;
    int value = -1;
    int count = -1;
    int choice = -1;
    string newFileName;
    // Проверка существования файла перед выполнением операций




    do {
        ifstream checkFileExistence(fileName);
        bool fileExists;
        fileExists = checkFileExistence.good(); // Проверяем состояние файла
        checkFileExistence.close();
        cout << "Выберите операцию:" << endl;
        cout << "1. Создать текстовый файл с десятичными числами" << endl;
        cout << "2. Вывести содержимое текстового файла" << endl;
        cout << "3. Добавить новую запись в конец файла" << endl;
        cout << "4. Прочитать значение числа по порядковому номеру" << endl;
        cout << "5. Определить количество чисел в файле" << endl;
        cout << "6. Создать новый файл из значений исходного, размещая по три числа на строке" << endl;
        cout << "0. Выйти" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            createTextFile(fileName);
            break;
        case 2:
            if (!fileExists) {
                cerr << "Файл '" << fileName << "' не существует или не может быть открыт." << endl;
                break;
            }
            displayTextFile(fileName);

            break;
        case 3:
            if (!fileExists) {
                cerr << "Файл '" << fileName << "' не существует или не может быть открыт." << endl;
                break;
            }
            int numToAdd;
            cout << "Введите число для добавления: ";
            cin >> numToAdd;
            appendToTextFile(fileName, numToAdd);
            break;
        case 4:
            if (!fileExists) {
                cerr << "Файл '" << fileName << "' не существует или не может быть открыт." << endl;
                break;
            }
            int indexToRead;
            cout << "Введите порядковый номер числа для чтения: ";
            cin >> indexToRead;
            value = readNumberByIndex(fileName, indexToRead); // Используем существующую переменную value
            if (value != -1) {
                cout << "Значение числа с порядковым номером " << indexToRead << ": " << value << endl;
            }
            break;
        case 5:

            if (!fileExists) {
                cerr << "Файл '" << fileName << "' не существует или не может быть открыт." << endl;
                break;
            }
            count = countNumbersInFile(fileName); // Используем существующую переменную count
            if (count != -1) {
                cout << "Количество чисел в файле: " << count << endl;
            }
            break;
        case 6:
            if (!fileExists) {
                cerr << "Файл '" << fileName << "' не существует или не может быть открыт." << endl;
                break;
            }
            cout << "Введите имя нового файла: ";
            cin >> newFileName;
            createNewFileWithThreeNumbersPerLine(fileName, newFileName);
            break;

        case 0:
            break;
        }
    } while (choice != 0);

    return 0;
}
