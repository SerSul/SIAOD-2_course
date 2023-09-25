#ifndef SIAOD_HEAD_2_2_H
#define SIAOD_HEAD_2_2_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Структура записи
struct Record {
    int readerTicketNumber;
    int bookInventoryNumber;
    int dateIssued;
    int dateReturned;
};

void txt_to_bin(ifstream& txt_file, ofstream& bin_file);
void bin_to_txt(ifstream& bin_file, ofstream& txt_file);
void print_bin(ifstream& bin_file);
int line_counter(ifstream& file);
Record get_struct(string filename, int position);
void remove_struct(string bin_name, int key);

//Перс.вар
void overdue_readers(ifstream& bin_file, ofstream& overdue_file, int current_date);
Record* find_record_by_criteria(ifstream& bin_file, int readerTicketNumber, int bookInventoryNumber);
void remove_returned_book(const string& bin_file_name, int readerTicketNumber, int bookInventoryNumber);
#endif //SIAOD_HEAD_2_2_H