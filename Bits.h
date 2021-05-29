#pragma once
#include <bitset>
#include <list>
#include <iostream>
#include <exception>
using namespace std;

class Bits {
private:
	char const correctionLevel = 'M'; // уровень коррекции
	const int maxInfoAmount[40] = {
		128, 224, 352, 512, 688, 864, 992, 1232, 1456, 1728,
		2032, 2320, 2672, 2920, 3320, 3624, 4056, 4504, 5016, 5352,
		5712, 6256, 6880, 7312, 8000, 8496, 9024, 9544, 10136, 10984,
		11640, 12328, 13048, 13800, 14496, 15312, 15936, 16816, 17728, 18672 }; // массив для определения версии
	bitset<4> const codingType = 0100; // способ кодирования
	unsigned int byteLength = 0; // длина в байтах
	unsigned int filledByteLength = 0;
	bitset<8> infoAmountVer1to9 = 0; // длина в 8 битовой записи
	bitset<16> infoAmountVer10to40 = 0; // длина в 16 битовой записи
	list<bitset<8>> stringBits; // список 8 битовых записей символов строки
	list<bitset<8>> filledBits;
	bitset<8> fillingBits[2] = {11101100, 00010001};
	char* additionalZeros; // заполняющие нули

	void SetVersion(); // установить версию
	void SetInfoAmount(); // установить длину в 8 или 16 битовой записи
	int ServiseInfo(); // формирование служебной информации
	void Filling(); // заполнение
public:
	unsigned int version = 0;
	Bits(string);
	~Bits();
};