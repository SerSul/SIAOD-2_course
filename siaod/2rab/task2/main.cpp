#include "siaod_2_head.h"


void menu() {
    setlocale(LC_ALL, "Russian");
    cout << "Список команд для выполнения: \n"
        "1. Преобразование тестовых данных из текстового файла в двоичный файл. \n"
        "2. Преобразование данных из двоичного файла в текстовый. \n"
        "3. Вывод всех записей двоичного файла. \n"
        "4. Доступ к записи по ее порядковому номеру в файле, используя механизм прямого доступа к записи в двоичном файле. \n"
        "5. Удаление записи с заданным значением ключа, выполнить путем замены на последнюю запись \n"
        "6. Сформировать список читателей, которые не вернули книги в срок. \n"
        "7. Найти запись по заданным критериям. \n"
        "8. Удалить запись о книге, которую читатель вернулв библиотеку. \n"
        "0. Выход из программы. \n";
}
int main() {
    string inp_file, outp_file;
    ifstream inp;
    ofstream outp;
    menu();
    int num;
    bool flag = true;
    while (flag) {
        cout << "\nВведите новую команду:\n";
        cin >> num;
        switch (num) {
        case 1: {
            inp_file = "";
            outp_file = "";
            cout << "Введите имя текстового файла: \n";
            cin >> inp_file;
            inp.open(inp_file, ios::in);
            if (inp.good()) {
                cout << "Введите имя бинарного файла: \n";
                cin >> outp_file;
                outp.open(outp_file, ios::binary);
                if (outp.good()) {
                    txt_to_bin(inp, outp);
                }
                else cout << "Файл не найден или не создан.";

                outp.close();
                inp.close();
            }
            else {
                cout << "Файла с таким именем не существует.";
            }
            break;
        }
        case 2: {
            inp_file = "";
            outp_file = "";
            cout << "Введите имя бинарного файла:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::binary | ios::in);
            if (inp.good()) {
                cout << "Введите имя текстового файла:\n";
                cin >> outp_file;
                outp.open(outp_file, ios::out);
                if (outp.good()) {
                    bin_to_txt(inp, outp);
                }
                else cout << "Файл не найден или не создан.";

                outp.close();
                inp.close();
            }
            else {
                cout << " Файла с таким именем не существует.";
            }
            break;
        }
        case 3: {
            inp_file = "";
            cout << "Введите имя бинарного файла:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::in | ios::binary);
            if (inp.good()) {
                cout << "\nВывод содержимого бинарного файла:\n";
                print_bin(inp);
                inp.close();
            }
            else {
                cout << "Файла с таким именем не существует.";
            }
            break;
        }
        case 4: {
            inp_file = "";
            int pos_num;
            cout << "Введите имя бинарного файла: \n";
            cin >> inp_file;
            //inp.open(inp_file);
            ifstream check(inp_file);
            if (check.is_open()) {
                cout << "Введите номер нужной строки: \n";
                cin >> pos_num;
                ifstream tmp(inp_file, ios::binary | ios::in);
                int c = line_counter(tmp);
                if (pos_num < c) {
                    Record tt = get_struct(inp_file, pos_num);
                    cout << tt.readerTicketNumber << ' ' << tt.bookInventoryNumber << ' ' << tt.dateIssued << ' '
                        << tt.dateReturned << '\n';
                }
                else {
                    cout << "Введено слишком большое число.\n";
                }
            }
            else {
                cout << "Файла с таким именем не существует. ";
            }
            break;
        }
        case 5: {
            inp_file = "";
            int key_val;
            cout << "Введите имя бинарного файла: \n";
            cin >> inp_file;

            ifstream check(inp_file);
            if (check.is_open()) {
                cout << "Введите ключевой параметр:\n";
                cin >> key_val;

                remove_struct(inp_file, key_val);
            }
            else {
                cout << "Файла с таким именем не существует. ";
            }
            break;
        }
        case 6: {
            inp_file = "";
            outp_file = "";
            cout << "Введите имя бинарного файла для списка читателей:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::binary | ios::in);

            if (inp.good()) {
                int current_date;
                cout << "Введите текущую дату (в формате YYYYMMDD):\n";
                cin >> current_date;

                cout << "Введите имя бинарного файла для записи читателей, не вернувших книги в срок:\n";
                cin >> outp_file;
                outp.open(outp_file, ios::binary | ios::out);

                if (outp.good()) {
                    overdue_readers(inp, outp, current_date);
                    cout << "Список читателей, не вернувших книги в срок, создан.\n";
                }
                else {
                    cout << "Ошибка при открытии/создании бинарного файла для записи.\n";
                }

                outp.close();
                inp.close();
            }
            else {
                cout << "Файла с таким именем не существует.\n";
            }
            break;
        }
        case 7: {
            inp_file = "";
            int readerTicketNumber, bookInventoryNumber;
            cout << "Введите имя бинарного файла для поиска записи:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::binary | ios::in);

            if (inp.good()) {
                cout << "Введите номер читательского билета:\n";
                cin >> readerTicketNumber;

                cout << "Введите инвентарный номер книги:\n";
                cin >> bookInventoryNumber;

                Record* result = find_record_by_criteria(inp, readerTicketNumber, bookInventoryNumber);
                if (result != nullptr) {
                    cout << "Найденная запись: " << result->readerTicketNumber << ' ' << result->bookInventoryNumber << ' '
                        << result->dateIssued << ' ' << result->dateReturned << '\n';
                    delete result; // Освобождаем память после использования
                }
                else {
                    cout << "Запись не найдена.\n";
                }

                inp.close();
            }
            else {
                cout << "Файла с таким именем не существует.\n";
            }
            break;
        }

        case 8: {
            inp_file = "";
            int readerTicketNumber, bookInventoryNumber;
            cout << "Введите имя бинарного файла:\n";
            cin >> inp_file;

            cout << "Введите номер читательского билета:\n";
            cin >> readerTicketNumber;

            cout << "Введите инвентарный номер книги:\n";
            cin >> bookInventoryNumber;

            remove_returned_book(inp_file, readerTicketNumber, bookInventoryNumber);
            break;
        }
        default:
            flag = false;
            break;
            break;
        }
    }

    return 0;
}

/*
// Структура записи
struct Record {
    int readerTicketNumber;
    int bookInventoryNumber;
    int dateIssued;
    int dateReturned;
};
*/