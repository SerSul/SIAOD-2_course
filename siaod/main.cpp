#include <iostream>
#include <vector>

#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <chrono> 
using namespace std;


int Exercise1(int x)
{
	x = x | 0x128;
	return x;
}

int Exercise2(int x) {
	unsigned mask = 0xFF9F;

	x = x & mask; 

	return x;
}


int Exercise3(int x)
{
	x = x << 4;
	return x;
}

int Exercise4(int x)
{
	x = x >> 4;
	return x;
}

int Exercise5(int x, int n)
{
	unsigned mask = 0x01;
	mask = mask << n;
	x = x & ~mask;
	return x;
}


void toBin(int x)
{
	int n;
	n = sizeof(int) * 4;
	unsigned maska = (1 << (n - 1));
	for (int i = 1; i <= n; i++)
	{
		cout << ((x & maska) >> (n - i));
		maska = maska >> 1;
		if (i % 4 == 0 && i!=n)
			cout << ".";
	}
}

void printBitset(int b) {
	for (int i = 31; i >= 0; i--) {
		cout << ((b >> i) & 1);
	}
}


std::set<int> generateUniqueSevenDigitNumbers(int count) {
	std::set<int> generatedNumbers;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	while (generatedNumbers.size() < count) {
		int num = 1000000 + std::rand() % 9000000;
		generatedNumbers.insert(num);
	}

	return generatedNumbers;
}


const int NUM_BYTES = 9999999 / 8 + 1;

void setBit(std::vector<uint8_t>& byteArray, int num) {
	int byteIndex = (num - 1000000) / 8;
	int bitIndex = (num - 1000000) % 8;
	byteArray[byteIndex] |= (1 << bitIndex);
}

void printSetBits(const std::vector<uint8_t>& byteArray) {
	std::cout << "������������� ���� (������ �����):" << std::endl;
	for (int i = 1000000; i <= 9999999; ++i) {
		int byteIndex = (i - 1000000) / 8;
		int bitIndex = (i - 1000000) % 8;
		if ((byteArray[byteIndex] & (1 << bitIndex)) != 0) {
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}


int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int number;
cycle:
	cout << "������� ����� ���������:\n";
	cout << "1- ��������� �� 3, 5 � 8 ��� �������� ������� \n" << "2- ��������� c 4-�� 2 ���� �����\n"
		<< "3- ����� ����� ����� �� 16 ��������\n" << "4- ����� ����� ������ �� 16 ��������\n" << "5- ��������� n-��� ����\n" << "6- ��������� ����������\n" << "0- ��� ������\n";
	cin >> number;
	switch (number)
	{
	case 1:
	{
		int x = 0x0000;
		cout << "����� � 16-������ �������: " << hex << x << "\n";
		cout << "����� ����� � ���������� �������: " << dec << x << "\n";
		cout << "����� � 2-����� �������: ";
		toBin(x);
		x = Exercise1(x);
		cout << "\n����� �����:		 ";
		toBin(x);
		cout << "\n����� ����� � ���������� �������: " << dec << x;
		cout << "\n\n";
		goto cycle;
	}
	case 2:
	{ //65535
		int x;
		cout << "������� �����: ";
		cin >> x;
		cout << "����� � 2-����� �������: ";
		toBin(x);
		x = Exercise2(x);
		cout << "\n����� �����:		 ";
		toBin(x);
		cout << "\n����� ����� � ���������� �������: " << x;
		cout << "\n\n";
		goto cycle;
	}
	case 3:
	{
		int x;
		cout << "������� �����: ";
		cin >> x;
		cout << "����� � 2-����� �������: ";
		toBin(x);
		x = Exercise3(x);
		cout << "\n����� �����:		 ";
		toBin(x);
		cout << "\n����� ����� � ���������� �������: " << x;
		cout << "\n\n";
		goto cycle;
	}
	case 4:
	{
		int x;
		cout << "������� �����: ";
		cin >> x;
		cout << "����� � 2-����� �������: ";
		toBin(x);
		x = Exercise4(x);
		cout << "\n����� �����:		 ";
		toBin(x);
		cout << "\n����� ����� � ���������� �������: " << x;
		cout << "\n\n";
		goto cycle;
	}
	case 5:
	{
		int x, n;
		cout << "������� �����: ";
		cin >> x;
		cout << "\n������� ���, ������� ������ ����������: ";
		cin >> n;
		cout << "����� � 2-����� �������: ";
		toBin(x);
		x = Exercise5(x, n);
		cout << "\n����� �����:		 ";
		toBin(x);
		cout << "\n����� ����� � ���������� �������: " << x;
		cout << "\n\n";
		goto cycle;
	}
	case 6:
	{
		int arraySize;

		std::cout << "������� ������ ������� (������������ ������ " << NUM_BYTES << "): ";
		std::cin >> arraySize;
		int a = arraySize;
		if (arraySize <= 0 || arraySize > NUM_BYTES) {
			std::cerr << "������������ ������ �������." << std::endl;
			break; // ����� �� switch-case
		}

		std::vector<uint8_t> byteArray(NUM_BYTES, 0); // uint8_t ��� ������������� ������

		std::vector<int> numbers;
		int num;
		std::cout << "������� ����������� ����� (��� ���������� ������� 0):" << std::endl;

		while (arraySize > 0) {
			std::cin >> num;
			if (num == 0) {
				break;
			}
			if (num < 1000000 || num > 9999999) {
				std::cerr << "�������� �����. ������� ����������� �����." << std::endl;
				continue;
			}
			numbers.push_back(num);
			arraySize--;
		}

		// ���������� ��� ��������� ������� ����������
		auto start_time = std::chrono::high_resolution_clock::now();

		for (const auto& number : numbers) {
			setBit(byteArray, number);
		}

		// ���������� ��������� ������� ����������
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		std::cout << "���-�� ���������: " << a << "\n";
		std::cout << "����� ����������: " << duration.count() << " �����������." << std::endl;

		printSetBits(byteArray);
		goto cycle;
	}



	default:
	{
		break;
	}
	return 0;
	}

}