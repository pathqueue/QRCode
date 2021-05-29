#pragma once
#include <bitset>
#include <list>
#include <iostream>
#include <exception>
using namespace std;

class Bits {
private:
	char const correctionLevel = 'M'; // ������� ���������
	const int maxInfoAmount[40] = {
		128, 224, 352, 512, 688, 864, 992, 1232, 1456, 1728,
		2032, 2320, 2672, 2920, 3320, 3624, 4056, 4504, 5016, 5352,
		5712, 6256, 6880, 7312, 8000, 8496, 9024, 9544, 10136, 10984,
		11640, 12328, 13048, 13800, 14496, 15312, 15936, 16816, 17728, 18672 }; // ������ ��� ����������� ������
	const bitset<4> codingType = bitset<4>(2); // ������ �����������
	unsigned int byteLength = 0; // ����� � ������
	unsigned int filledByteLength = 0; // ����� ����� � �����
	unsigned int version = 0; // ������
	bitset<8> infoAmountVer1to9 = 0; // ����� � 8 ������� ������
	bitset<16> infoAmountVer10to40 = 0; // ����� � 16 ������� ������
	list<bitset<8>> stringBits; // ������ 8 ������� ������� �������� ������
	const bitset<8> fillingBytes[2] = { bitset<8>(236), bitset<8>(17)}; //
	list<bitset<8>> filledBits;

	void SetVersion(); // ���������� ������
	void SetInfoAmount(); // ���������� ����� � 8 ��� 16 ������� ������
	int ServiseInfo(); // ������������ ��������� ����������
	void Filling(); // ����������
public:
	Bits(string);
	~Bits();
};