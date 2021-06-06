#pragma once
#include <bitset>
#include <list>
#include <iostream>
#include <exception>
#include <map>
#include <vector>
#include <iterator>
#include <Magick++.h>
using namespace std;
using namespace Magick;

class Bits {
private:
	char const correctionLevel = 'M'; // ������� ���������
	const bitset<4> codingType = bitset<4>(2); // ������ �����������
	unsigned int byteLength = 0; // ����� � ������
	unsigned int filledByteLength = 0; // ����� ����� � �����
	unsigned int version = 0; // ������
	bitset<8> infoAmountVer1to9 = 0; // ����� � 8 ������� ������
	bitset<16> infoAmountVer10to40 = 0; // ����� � 16 ������� ������
	list<bitset<8>> stringBits; // ������ 8 ������� ������� �������� ������
	const bitset<8> fillingBytes[2] = { bitset<8>(236), bitset<8>(17)}; // ������������ �����
	list<bitset<8>> filledBits; // ����� ������ - ��������� ���������� + ��������� + ����������� �����
	list<list<bitset<8>>> infoBlocks; // ����� ���������� (������ � ������)
	list<list<bitset<8>>> correctionBytesBlocks; // ����� ������ ���������, ������������� ������ ����������
	list<bitset<8>> mergedBlocks; // ����������� ������

	void SetVersion(); // ���������� ������
	void SetInfoAmount(); // ���������� ����� � 8 ��� 16 ������� ������
	int ServiseInfo(); // ������������ ��������� ����������
	void Filling(); // ����������
	void Division(); // ���������� �� �����
	void CreateCorrectionBytes(); // �������� ������ ���������
	void BlockMerging(); // ����������� ������
public:
	Bits(string);
	~Bits();
};