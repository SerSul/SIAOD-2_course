#include "siaod_2_head.h"


void menu() {
    setlocale(LC_ALL, "Russian");
    cout << "������ ������ ��� ����������: \n"
        "1. �������������� �������� ������ �� ���������� ����� � �������� ����. \n"
        "2. �������������� ������ �� ��������� ����� � ���������. \n"
        "3. ����� ���� ������� ��������� �����. \n"
        "4. ������ � ������ �� �� ����������� ������ � �����, ��������� �������� ������� ������� � ������ � �������� �����. \n"
        "5. �������� ������ � �������� ��������� �����, ��������� ����� ������ �� ��������� ������ \n"
        "6. ������������ ������ ���������, ������� �� ������� ����� � ����. \n"
        "7. ����� ������ �� �������� ���������. \n"
        "8. ������� ������ � �����, ������� �������� ������� ����������. \n"
        "0. ����� �� ���������. \n";
}
int main() {
    string inp_file, outp_file;
    ifstream inp;
    ofstream outp;
    menu();
    int num;
    bool flag = true;
    while (flag) {
        cout << "\n������� ����� �������:\n";
        cin >> num;
        switch (num) {
        case 1: {
            inp_file = "";
            outp_file = "";
            cout << "������� ��� ���������� �����: \n";
            cin >> inp_file;
            inp.open(inp_file, ios::in);
            if (inp.good()) {
                cout << "������� ��� ��������� �����: \n";
                cin >> outp_file;
                outp.open(outp_file, ios::binary);
                if (outp.good()) {
                    txt_to_bin(inp, outp);
                }
                else cout << "���� �� ������ ��� �� ������.";

                outp.close();
                inp.close();
            }
            else {
                cout << "����� � ����� ������ �� ����������.";
            }
            break;
        }
        case 2: {
            inp_file = "";
            outp_file = "";
            cout << "������� ��� ��������� �����:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::binary | ios::in);
            if (inp.good()) {
                cout << "������� ��� ���������� �����:\n";
                cin >> outp_file;
                outp.open(outp_file, ios::out);
                if (outp.good()) {
                    bin_to_txt(inp, outp);
                }
                else cout << "���� �� ������ ��� �� ������.";

                outp.close();
                inp.close();
            }
            else {
                cout << " ����� � ����� ������ �� ����������.";
            }
            break;
        }
        case 3: {
            inp_file = "";
            cout << "������� ��� ��������� �����:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::in | ios::binary);
            if (inp.good()) {
                cout << "\n����� ����������� ��������� �����:\n";
                print_bin(inp);
                inp.close();
            }
            else {
                cout << "����� � ����� ������ �� ����������.";
            }
            break;
        }
        case 4: {
            inp_file = "";
            int pos_num;
            cout << "������� ��� ��������� �����: \n";
            cin >> inp_file;
            //inp.open(inp_file);
            ifstream check(inp_file);
            if (check.is_open()) {
                cout << "������� ����� ������ ������: \n";
                cin >> pos_num;
                ifstream tmp(inp_file, ios::binary | ios::in);
                int c = line_counter(tmp);
                if (pos_num < c) {
                    Record tt = get_struct(inp_file, pos_num);
                    cout << tt.readerTicketNumber << ' ' << tt.bookInventoryNumber << ' ' << tt.dateIssued << ' '
                        << tt.dateReturned << '\n';
                }
                else {
                    cout << "������� ������� ������� �����.\n";
                }
            }
            else {
                cout << "����� � ����� ������ �� ����������. ";
            }
            break;
        }
        case 5: {
            inp_file = "";
            int key_val;
            cout << "������� ��� ��������� �����: \n";
            cin >> inp_file;

            ifstream check(inp_file);
            if (check.is_open()) {
                cout << "������� �������� ��������:\n";
                cin >> key_val;

                remove_struct(inp_file, key_val);
            }
            else {
                cout << "����� � ����� ������ �� ����������. ";
            }
            break;
        }
        case 6: {
            inp_file = "";
            outp_file = "";
            cout << "������� ��� ��������� ����� ��� ������ ���������:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::binary | ios::in);

            if (inp.good()) {
                int current_date;
                cout << "������� ������� ���� (� ������� YYYYMMDD):\n";
                cin >> current_date;

                cout << "������� ��� ��������� ����� ��� ������ ���������, �� ��������� ����� � ����:\n";
                cin >> outp_file;
                outp.open(outp_file, ios::binary | ios::out);

                if (outp.good()) {
                    overdue_readers(inp, outp, current_date);
                    cout << "������ ���������, �� ��������� ����� � ����, ������.\n";
                }
                else {
                    cout << "������ ��� ��������/�������� ��������� ����� ��� ������.\n";
                }

                outp.close();
                inp.close();
            }
            else {
                cout << "����� � ����� ������ �� ����������.\n";
            }
            break;
        }
        case 7: {
            inp_file = "";
            int readerTicketNumber, bookInventoryNumber;
            cout << "������� ��� ��������� ����� ��� ������ ������:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::binary | ios::in);

            if (inp.good()) {
                cout << "������� ����� ������������� ������:\n";
                cin >> readerTicketNumber;

                cout << "������� ����������� ����� �����:\n";
                cin >> bookInventoryNumber;

                Record* result = find_record_by_criteria(inp, readerTicketNumber, bookInventoryNumber);
                if (result != nullptr) {
                    cout << "��������� ������: " << result->readerTicketNumber << ' ' << result->bookInventoryNumber << ' '
                        << result->dateIssued << ' ' << result->dateReturned << '\n';
                    delete result; // ����������� ������ ����� �������������
                }
                else {
                    cout << "������ �� �������.\n";
                }

                inp.close();
            }
            else {
                cout << "����� � ����� ������ �� ����������.\n";
            }
            break;
        }

        case 8: {
            inp_file = "";
            int readerTicketNumber, bookInventoryNumber;
            cout << "������� ��� ��������� �����:\n";
            cin >> inp_file;

            cout << "������� ����� ������������� ������:\n";
            cin >> readerTicketNumber;

            cout << "������� ����������� ����� �����:\n";
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
// ��������� ������
struct Record {
    int readerTicketNumber;
    int bookInventoryNumber;
    int dateIssued;
    int dateReturned;
};
*/