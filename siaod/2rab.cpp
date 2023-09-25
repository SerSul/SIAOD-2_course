#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



/*
1. ���������� �����-������ �� ������ �������� ������� �++: ofstream, ifstrim. ++
2. ��� ����������� ����� �������� ������������� � ���������� � �������
��������� ����� ��������. ++
3. ��� �������� ����� ��������� �������� ��� ������������� � ��������.
����������. ��� ������� ��������� ������ ��� ����������� �����
���������� ����� ���������. ++
4. ����������� ������� ��� ���������� �������� ��� ��������� ������.
1) �������� ���������� ����� ���������� ���������� ��������� ���������
ASCII, ����������� ���������� ����� �� ��������� ����� �� ������;
2) ����� ����������� ���������� �����;
3) ���������� ����� ������ � ����� �����;
4) ��������� �������� �����, ������ ��� ���������� ����� � �����, � �������
��� ��������;
5) ���������� ���������� ����� � �����.
5. ����������� ���������� � ��������� ������������ ���� �������.
���������� ������ ��������� ���������� ��������� �� ������ ����������
����.
6. �������� �������� � ������������� ����� ��������� � �������� ���������
����� ������� �������. ����� ��������� �����, ��������� ����������
������ ����� � ������ (����� good)
//

7. ������� ������ � ��������� � ���� ��� ���������� �������. ���������
������� �� ����������. �������� ����������, ��������� � ���� ������ �
���������.


8. ����������� ������� ��� ���������� �������������� ��������,
������������ ��������� � ��������� �� � ������ � ���������� ���������.
9. ��������� ������������ ���������� � ������ ������.
*/


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



// ����-� ��� �������� ������ ����� �� ���������
void createNewFileWithThreeNumbersPerLine(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "������ �������� ��������� ����� ��� ������: " << inputFileName << endl;
        return;
    }

    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cerr << "������ �������� ������ ����� ��� ������: " << outputFileName << endl;
        inputFile.close();
        return;
    }

    int num;
    int count = 0;

    while (inputFile >> num) {
        if (count == 3) {
            outputFile << endl; // ������� �� ����� ������ ����� ���� �����
            count = 0;
        }
        outputFile << num << " ";
        count++;
    }

    inputFile.close();
    outputFile.close();

    cout << "������ ����� ���� '" << outputFileName << "' � �� ��� ����� �� ������." << endl;
}


int main() {
    setlocale(LC_ALL, "ru");
    string fileName;

    cout << "������� ��� �����: ";
    cin >> fileName;
    int value = -1;
    int count = -1;
    int choice = -1;
    string newFileName;
    // �������� ������������� ����� ����� ����������� ��������




    do {
        ifstream checkFileExistence(fileName);
        bool fileExists;
        fileExists = checkFileExistence.good(); // ��������� ��������� �����
        checkFileExistence.close();
        cout << "�������� ��������:" << endl;
        cout << "1. ������� ��������� ���� � ����������� �������" << endl;
        cout << "2. ������� ���������� ���������� �����" << endl;
        cout << "3. �������� ����� ������ � ����� �����" << endl;
        cout << "4. ��������� �������� ����� �� ����������� ������" << endl;
        cout << "5. ���������� ���������� ����� � �����" << endl;
        cout << "6. ������� ����� ���� �� �������� ���������, �������� �� ��� ����� �� ������" << endl;
        cout << "0. �����" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            createTextFile(fileName);
            break;
        case 2:
            if (!fileExists) {
                cerr << "���� '" << fileName << "' �� ���������� ��� �� ����� ���� ������." << endl;
                break;
            }
            displayTextFile(fileName);

            break;
        case 3:
            if (!fileExists) {
                cerr << "���� '" << fileName << "' �� ���������� ��� �� ����� ���� ������." << endl;
                break;
            }
            int numToAdd;
            cout << "������� ����� ��� ����������: ";
            cin >> numToAdd;
            appendToTextFile(fileName, numToAdd);
            break;
        case 4:
            if (!fileExists) {
                cerr << "���� '" << fileName << "' �� ���������� ��� �� ����� ���� ������." << endl;
                break;
            }
            int indexToRead;
            cout << "������� ���������� ����� ����� ��� ������: ";
            cin >> indexToRead;
            value = readNumberByIndex(fileName, indexToRead); // ���������� ������������ ���������� value
            if (value != -1) {
                cout << "�������� ����� � ���������� ������� " << indexToRead << ": " << value << endl;
            }
            break;
        case 5:

            if (!fileExists) {
                cerr << "���� '" << fileName << "' �� ���������� ��� �� ����� ���� ������." << endl;
                break;
            }
            count = countNumbersInFile(fileName); // ���������� ������������ ���������� count
            if (count != -1) {
                cout << "���������� ����� � �����: " << count << endl;
            }
            break;
        case 6:
            if (!fileExists) {
                cerr << "���� '" << fileName << "' �� ���������� ��� �� ����� ���� ������." << endl;
                break;
            }
            cout << "������� ��� ������ �����: ";
            cin >> newFileName;
            createNewFileWithThreeNumbersPerLine(fileName, newFileName);
            break;

        case 0:
            break;
        }
    } while (choice != 0);

    return 0;
}
