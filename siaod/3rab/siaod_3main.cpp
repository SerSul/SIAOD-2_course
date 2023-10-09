#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <set>
#include <list>


/*

Разработать программу, которая использует хеш-таблицу для организации
прямого доступа к записям двоичного файла, структура записи которого
приведена в варианте.
Разработайте класс хеш-таблицы и реализуйте методы для операций:
1) Хеширование (метод определите сами). +
2) Чтение записи из файла и вставка записи в таблицу (запись включает:
ключ и номер записи с этим ключом в файле). +
3) Удаление записи из таблицы и, соответственно, из файла. +
4) Поиск записи с заданным ключом в файле, используя хеш-таблицу. +
5) Выполнение рехеширования. +

*/

struct Record {
    long long readerTicketNumber;
    int bookInventoryNumber;
    int dateIssued;
    int dateReturned;
};

class HashTable {
private:
    static const int TABLE_SIZE = 100; // Размер хеш-таблицы
    std::vector<std::list<Record>> table;
    int tableSize;
    int recordCount;

    int hash(long long index) {
        return static_cast<int>(index % tableSize);
    }

public:
    HashTable() {
        tableSize = TABLE_SIZE;
        table.resize(tableSize);
        recordCount = 0;
    }

    void readFile(std::string fileName) {
        Record record;
        tableSize = 1;
        recordCount = 0;
        table.clear();
        table.resize(1);

        std::ifstream file(fileName, std::ios::binary);

        while (file.read(reinterpret_cast<char*>(&record), sizeof(record))) {
            if (static_cast<float>(recordCount) / static_cast<float>(tableSize) >= 0.75)
                rehash();

            int index = hash(record.readerTicketNumber);
            table[index].push_back(record);
            recordCount++;
        }
        file.close();
    }

    void removeRecord(std::string fileName, long long index) {
        int hashIndex = hash(index);
        auto& list = table[hashIndex];
        auto iter = list.begin();

        for (; iter != list.end(); ++iter) {
            if (iter->readerTicketNumber == index) {
                iter = list.erase(iter);
                recordCount--;
                break;
            }
        }

        std::ifstream inFile(fileName, std::ios::binary);
        std::ofstream tempFile("temp.bin", std::ios::binary);

        Record record;
        while (inFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
            if (record.readerTicketNumber != index) {
                tempFile.write(reinterpret_cast<char*>(&record), sizeof(record));
            }
        }
        inFile.close();
        tempFile.close();
        remove(fileName.c_str());
        (void)rename("temp.bin", fileName.c_str());
    }

    Record* findRecord(long long index) {
        int hashIndex = hash(index);
        auto& list = table[hashIndex];

        for (auto& record : list) {
            if (record.readerTicketNumber == index) {
                return &record;
            }
        }

        return nullptr; // Возвращаем nullptr, если запись не найдена
    }

    void rehash() {
        tableSize *= 2;
        std::vector<std::list<Record>> newTable(tableSize);

        for (const auto& list : table) {
            for (const auto& record : list) {
                int newIndex = hash(record.readerTicketNumber);
                newTable[newIndex].push_back(record);
            }
        }
        table = std::move(newTable);
    }


    void outputFile(std::string fileName) {
        std::ifstream file(fileName, std::ios::binary);
        Record record;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(record))) {
            std::cout << "Reader Ticket Number: " << record.readerTicketNumber
                << ", Book Inventory Number: " << record.bookInventoryNumber
                << ", Date Issued: " << record.dateIssued
                << ", Date Returned: " << record.dateReturned << "\n";
        }
        file.close();
    }

    void outputTable() {
        std::cout << "Table size: " << tableSize << "\n";
        for (int i = 0; i < tableSize; i++) {
            std::cout << "Index: " << i << "\n";
            for (const auto& record : table[i]) {
                std::cout << "  Reader Ticket Number: " << record.readerTicketNumber
                    << ", Book Inventory Number: " << record.bookInventoryNumber
                    << ", Date Issued: " << record.dateIssued
                    << ", Date Returned: " << record.dateReturned << "\n";
            }
        }
    }


    std::string generateFile(int recordCount) {
        std::string fileName = "library_" + std::to_string(time(0)) + ".dat"; // Создание уникального имени файла
        std::ofstream file(fileName, std::ios::binary);
        std::set<int> usedTicketNumbers; // Для отслеживания использованных номеров

        for (int i = 0; i < recordCount; ++i) {
            Record record;
            long long uniqueTicketNumber;

            do {
                uniqueTicketNumber = rand() % 10000000; // Генерация случайного номера
            } while (usedTicketNumbers.count(uniqueTicketNumber) > 0); // Проверка на уникальность

            usedTicketNumbers.insert(uniqueTicketNumber);
            record.readerTicketNumber = uniqueTicketNumber;
            record.bookInventoryNumber = rand() % 10000;
            record.dateIssued = rand() % 365;
            record.dateReturned = rand() % 365;
            file.write(reinterpret_cast<char*>(&record), sizeof(record));
        }

        file.close();
        std::cout << "Сгенерирован файл: " << fileName << std::endl;
        return fileName; // Возвращаем имя сгенерированного файла
    }

   
};




int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(nullptr))); 

    std::string fileName = "library.dat";
    HashTable hashTable;

    int choice;
    bool autoGenerate = false;
    int recordCount = 1000;
    Record* foundRecord = new Record; // Инициализируем переменную здесь
    int var;

    bool entry = true;
    if (entry) {
        std::cout << "Введите 1 для автоматической генерации файла. 2 для ручного ввода.\n";
        std::cin >> var;

        if (var == 1) {
            std::cout << "Введите количество элементов в файле:\n";
            std::cin >> recordCount;
            fileName = hashTable.generateFile(recordCount); 
        }

        if (var == 2) {

            std::ofstream file("library_myself.dat", std::ios::binary);
            fileName = "library_myself.dat";
            if (!file) {
                std::cerr << "Ошибка при открытии файла для записи." << std::endl;
                return 1;
            }
            std::cout << "Введите количество элементов в файле:\n";
            std::cin >> recordCount;
            std::cin.ignore(); 

            for (int i = 0; i < recordCount; i++) {
                Record book;
                std::string line;

                std::cout << "Введите номер читательского билета: ";
                std::cin >> book.readerTicketNumber;
                std::cin.ignore(); 

                std::cout << "Введите инвентарный номер книги: ";
                std::cin >> book.bookInventoryNumber;
                std::cin.ignore(); 

                std::cout << "Введите дату выдачи: ";
                std::cin >> book.dateIssued;
                std::cin.ignore(); 

                std::cout << "Введите дату возврата: ";
                std::cin >> book.dateReturned;
                std::cin.ignore(); 

                file.write(reinterpret_cast<char*>(&book), sizeof(book));
            }

            file.close();
        }

    }


    while (true) {
        std::cout << "Выберите операцию:\n";
        std::cout << "1 - Чтение записей из файла и вставка в таблицу\n";
        std::cout << "2 - Удаление записи из таблицы и файла\n";
        std::cout << "3 - Поиск записи по ключу\n";
        std::cout << "4 - Вывод содержимого файла\n";
        std::cout << "5 - Вывод содержимого таблицы\n";
        std::cout << "6 - Исследование времени чтения из начала, середины и конца файла\n";

        std::cout << "0 - Выход из программы\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
        {
            auto start = std::chrono::high_resolution_clock::now();
            hashTable.readFile(fileName);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "Время выполнения операции 1: " << duration.count() << " миллисекунд\n";
        }
        break;
        case 2:
        {
            long long index;
            std::cout << "Введите ключ записи для удаления:\n";
            std::cin >> index;
            auto start = std::chrono::high_resolution_clock::now();
            hashTable.removeRecord(fileName, index);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "Время выполнения операции 2: " << duration.count() << " миллисекунд\n";
        }
        break;
        case 3:
        {
            long long index;
            std::cout << "Введите ключ записи для поиска:\n";
            std::cin >> index;
            auto start = std::chrono::high_resolution_clock::now();
            foundRecord = hashTable.findRecord(index);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "Время выполнения операции 3: " << duration.count() << " миллисекунд\n";

            if (foundRecord) {
                std::cout << "Найденная запись: Reader Ticket Number: " << foundRecord->readerTicketNumber
                    << ", Book Inventory Number: " << foundRecord->bookInventoryNumber
                    << ", Date Issued: " << foundRecord->dateIssued
                    << ", Date Returned: " << foundRecord->dateReturned << "\n";
            }
            else {
                std::cout << "Запись не найдена.\n";
            }
        }
        break;
        case 4:
            hashTable.outputFile(fileName);
            break;
        case 5:
            hashTable.outputTable();
            break;
        case 6: {
            // Исследование времени чтения записей из начала, середины и конца файла
            int fileRecordCount = recordCount; // Количество записей в файле

            // Чтение из начала файла
            auto start = std::chrono::high_resolution_clock::now();
            hashTable.readFile(fileName);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "Время чтения записей из начала файла: " << duration.count() << " миллисекунд\n";

            // Чтение из середины файла
            start = std::chrono::high_resolution_clock::now();
            hashTable.readFile(fileName);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            std::cout << "Время чтения записей из середины файла: " << duration.count() << " миллисекунд\n";

            // Чтение с конца файла
            start = std::chrono::high_resolution_clock::now();
            hashTable.readFile(fileName);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            std::cout << "Время чтения записей с конца файла: " << duration.count() << " миллисекунд\n";
        } break;
        case 0:
            exit(0);
        }
    }

    return 0;
}
