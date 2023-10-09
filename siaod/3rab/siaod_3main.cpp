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

����������� ���������, ������� ���������� ���-������� ��� �����������
������� ������� � ������� ��������� �����, ��������� ������ ��������
��������� � ��������.
������������ ����� ���-������� � ���������� ������ ��� ��������:
1) ����������� (����� ���������� ����). +
2) ������ ������ �� ����� � ������� ������ � ������� (������ ��������:
���� � ����� ������ � ���� ������ � �����). +
3) �������� ������ �� ������� �, ��������������, �� �����. +
4) ����� ������ � �������� ������ � �����, ��������� ���-�������. +
5) ���������� �������������. +

*/

struct Record {
    long long readerTicketNumber;
    int bookInventoryNumber;
    int dateIssued;
    int dateReturned;
};

class HashTable {
private:
    static const int TABLE_SIZE = 100; // ������ ���-�������
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

        return nullptr; // ���������� nullptr, ���� ������ �� �������
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
        std::string fileName = "library_" + std::to_string(time(0)) + ".dat"; // �������� ����������� ����� �����
        std::ofstream file(fileName, std::ios::binary);
        std::set<int> usedTicketNumbers; // ��� ������������ �������������� �������

        for (int i = 0; i < recordCount; ++i) {
            Record record;
            long long uniqueTicketNumber;

            do {
                uniqueTicketNumber = rand() % 10000000; // ��������� ���������� ������
            } while (usedTicketNumbers.count(uniqueTicketNumber) > 0); // �������� �� ������������

            usedTicketNumbers.insert(uniqueTicketNumber);
            record.readerTicketNumber = uniqueTicketNumber;
            record.bookInventoryNumber = rand() % 10000;
            record.dateIssued = rand() % 365;
            record.dateReturned = rand() % 365;
            file.write(reinterpret_cast<char*>(&record), sizeof(record));
        }

        file.close();
        std::cout << "������������ ����: " << fileName << std::endl;
        return fileName; // ���������� ��� ���������������� �����
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
    Record* foundRecord = new Record; // �������������� ���������� �����
    int var;

    bool entry = true;
    if (entry) {
        std::cout << "������� 1 ��� �������������� ��������� �����. 2 ��� ������� �����.\n";
        std::cin >> var;

        if (var == 1) {
            std::cout << "������� ���������� ��������� � �����:\n";
            std::cin >> recordCount;
            fileName = hashTable.generateFile(recordCount); 
        }

        if (var == 2) {

            std::ofstream file("library_myself.dat", std::ios::binary);
            fileName = "library_myself.dat";
            if (!file) {
                std::cerr << "������ ��� �������� ����� ��� ������." << std::endl;
                return 1;
            }
            std::cout << "������� ���������� ��������� � �����:\n";
            std::cin >> recordCount;
            std::cin.ignore(); 

            for (int i = 0; i < recordCount; i++) {
                Record book;
                std::string line;

                std::cout << "������� ����� ������������� ������: ";
                std::cin >> book.readerTicketNumber;
                std::cin.ignore(); 

                std::cout << "������� ����������� ����� �����: ";
                std::cin >> book.bookInventoryNumber;
                std::cin.ignore(); 

                std::cout << "������� ���� ������: ";
                std::cin >> book.dateIssued;
                std::cin.ignore(); 

                std::cout << "������� ���� ��������: ";
                std::cin >> book.dateReturned;
                std::cin.ignore(); 

                file.write(reinterpret_cast<char*>(&book), sizeof(book));
            }

            file.close();
        }

    }


    while (true) {
        std::cout << "�������� ��������:\n";
        std::cout << "1 - ������ ������� �� ����� � ������� � �������\n";
        std::cout << "2 - �������� ������ �� ������� � �����\n";
        std::cout << "3 - ����� ������ �� �����\n";
        std::cout << "4 - ����� ����������� �����\n";
        std::cout << "5 - ����� ����������� �������\n";
        std::cout << "6 - ������������ ������� ������ �� ������, �������� � ����� �����\n";

        std::cout << "0 - ����� �� ���������\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
        {
            auto start = std::chrono::high_resolution_clock::now();
            hashTable.readFile(fileName);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "����� ���������� �������� 1: " << duration.count() << " �����������\n";
        }
        break;
        case 2:
        {
            long long index;
            std::cout << "������� ���� ������ ��� ��������:\n";
            std::cin >> index;
            auto start = std::chrono::high_resolution_clock::now();
            hashTable.removeRecord(fileName, index);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "����� ���������� �������� 2: " << duration.count() << " �����������\n";
        }
        break;
        case 3:
        {
            long long index;
            std::cout << "������� ���� ������ ��� ������:\n";
            std::cin >> index;
            auto start = std::chrono::high_resolution_clock::now();
            foundRecord = hashTable.findRecord(index);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "����� ���������� �������� 3: " << duration.count() << " �����������\n";

            if (foundRecord) {
                std::cout << "��������� ������: Reader Ticket Number: " << foundRecord->readerTicketNumber
                    << ", Book Inventory Number: " << foundRecord->bookInventoryNumber
                    << ", Date Issued: " << foundRecord->dateIssued
                    << ", Date Returned: " << foundRecord->dateReturned << "\n";
            }
            else {
                std::cout << "������ �� �������.\n";
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
            // ������������ ������� ������ ������� �� ������, �������� � ����� �����
            int fileRecordCount = recordCount; // ���������� ������� � �����

            // ������ �� ������ �����
            auto start = std::chrono::high_resolution_clock::now();
            hashTable.readFile(fileName);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "����� ������ ������� �� ������ �����: " << duration.count() << " �����������\n";

            // ������ �� �������� �����
            start = std::chrono::high_resolution_clock::now();
            hashTable.readFile(fileName);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            std::cout << "����� ������ ������� �� �������� �����: " << duration.count() << " �����������\n";

            // ������ � ����� �����
            start = std::chrono::high_resolution_clock::now();
            hashTable.readFile(fileName);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            std::cout << "����� ������ ������� � ����� �����: " << duration.count() << " �����������\n";
        } break;
        case 0:
            exit(0);
        }
    }

    return 0;
}
