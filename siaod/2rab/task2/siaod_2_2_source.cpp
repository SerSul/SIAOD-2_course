#include "siaod_2_head.h"

/*
struct Record {
    int readerTicketNumber;
    int bookInventoryNumber;
    int dateIssued;
    int dateReturned;
};
*/

void txt_to_bin(ifstream& txt_file, ofstream& bin_file) { // 1 задание
    Record tt;
    while (true) {
        txt_file >> tt.readerTicketNumber;
        if (!txt_file.eof()) {
            txt_file >> tt.bookInventoryNumber >> tt.dateIssued >> tt.dateReturned;
            bin_file.write((char*)&tt, sizeof(Record));
        }
        else break;
    }

}

void bin_to_txt(ifstream& bin_file, ofstream& txt_file) { // 2 задание
    //Проверка на существование;
    Record tt;
    while (true) {
        bin_file.read((char*)&tt, sizeof(tt));
        if (!bin_file.eof())
            txt_file << tt.readerTicketNumber << " " << tt.bookInventoryNumber << " " << tt.dateIssued << " " << tt.dateReturned << "\n";
        else break;
    }
}

void print_bin(ifstream& bin_file) {
    Record tt;
    while (bin_file.read((char*)&tt, sizeof(tt))) {
        cout << tt.readerTicketNumber << ' ' << tt.bookInventoryNumber << ' ' << tt.dateIssued << ' ' << tt.dateReturned << '\n';
    }
}


int line_counter(ifstream& file) {
    string num_string = "";
    int counter = 1;
    while (!file.eof()) {
        while (getline(file, num_string)) {
            counter++;
        }
    }

    return counter;
}

Record get_struct(string filename, int position) { // 4 задание
    ifstream bin_file(filename, ios::binary | ios::in);
    Record tt;
    if (position == -1) {
        bin_file.seekg(-1 * sizeof(tt), ios::end);
    }
    else {
        bin_file.seekg((position) * sizeof(tt));
    }
    bin_file.read((char*)&tt, sizeof(Record));
    bin_file.close();
    return tt;
}


void remove_struct(string bin_name, int key) { // 5 задание

    Record tt, replace{};
    replace = get_struct(bin_name, -1);
    ifstream bin_file(bin_name, ios::binary | ios::in);
    ofstream tmp("tmp_rem.txt");
    while (true) {
        bin_file.read((char*)&tt, sizeof(tt));

        if (!bin_file.eof()) {
            if (tt.readerTicketNumber != key) {
                tmp << tt.readerTicketNumber << " " << tt.bookInventoryNumber << " " << tt.dateIssued << " " << tt.dateReturned<< "\n";
            }
            else {
                tmp << replace.readerTicketNumber << " " << replace.bookInventoryNumber << " " << replace.dateIssued << " " << replace.dateReturned<< "\n";
            }
        }
        else {
            break;
        }
    }
    tmp.close();
    bin_file.close();
    ifstream txt("tmp_rem.txt", ios::in);
    ofstream bin(bin_name, ios::binary);
    txt_to_bin(txt, bin);
    txt.close();
    bin.close();
}


void overdue_readers(ifstream& bin_file, ofstream& overdue_file, int current_date) { //6
    Record tt;
    while (true) {
        bin_file.read((char*)&tt, sizeof(tt));
        if (!bin_file.eof()) {
            if (tt.dateReturned < current_date) {
                overdue_file.write((char*)&tt, sizeof(Record));
            }
        }
        else {
            break;
        }
    }
}

// Функция для поиска записи по заданным критериям и возврата указателя на запись
Record* find_record_by_criteria(ifstream& bin_file, int readerTicketNumber, int bookInventoryNumber) {
    Record* foundRecord = nullptr;
    Record tt;

    while (bin_file.read((char*)&tt, sizeof(tt))) {
        if (tt.readerTicketNumber == readerTicketNumber && tt.bookInventoryNumber == bookInventoryNumber) {
            foundRecord = new Record(tt); // Выделяем память и создаем копию найденной записи
            break; // Заканчиваем поиск после нахождения первой подходящей записи
        }
    }

    return foundRecord; // Возвращаем указатель на запись или nullptr, если запись не найдена
}


// Функция для удаления записи о книге, которую читатель вернул в библиотеку
void remove_returned_book(const string& bin_file_name, int readerTicketNumber, int bookInventoryNumber) {
    ifstream bin_file(bin_file_name, ios::binary | ios::in);
    ofstream temp_file("temp.bin", ios::binary | ios::out);

    if (!bin_file.is_open() || !temp_file.is_open()) {
        cerr << "Ошибка при открытии файлов.\n";
        return;
    }

    Record tt;
    bool found = false;

    while (bin_file.read((char*)&tt, sizeof(tt))) {
        if (tt.readerTicketNumber == readerTicketNumber && tt.bookInventoryNumber == bookInventoryNumber) {
            found = true;
            cout << "Запись о книге, которую читатель вернул, удалена.\n";
            continue; // Пропустить запись, которую нужно удалить
        }
        temp_file.write((char*)&tt, sizeof(tt));
    }

    bin_file.close();
    temp_file.close();

    if (found) {
        if (remove(bin_file_name.c_str()) != 0) {
            cerr << "Ошибка при удалении исходного бинарного файла.\n";
            return;
        }

        if (rename("temp.bin", bin_file_name.c_str()) != 0) {
            cerr << "Ошибка при переименовании временного файла.\n";
        }
    }
    else {
        cerr << "Запись не найдена.\n";
        remove("temp.bin");
    }
}