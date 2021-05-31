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
	const int blocksCount[40] = { 1, 1, 1, 2, 2, 4, 4, 4, 5, 5,
		5, 8, 9, 9, 10, 10, 11, 13, 14, 16, 17, 17, 18, 20, 21,
		23, 25, 26, 28, 29, 31, 33, 35, 37, 38, 40, 43, 45, 47, 49 };
	const bitset<4> codingType = bitset<4>(2); // способ кодирования
	unsigned int byteLength = 0; // длина в байтах
	unsigned int filledByteLength = 0; // новая длина в битах
	unsigned int version = 0; // версия
	bitset<8> infoAmountVer1to9 = 0; // длина в 8 битовой записи
	bitset<16> infoAmountVer10to40 = 0; // длина в 16 битовой записи
	list<bitset<8>> stringBits; // список 8 битовых записей символов строки
	const bitset<8> fillingBytes[2] = { bitset<8>(236), bitset<8>(17)}; //
	list<bitset<8>> filledBits;
	list<list<bitset<8>>> infoBlocks;

	void SetVersion(); // установить версию
	void SetInfoAmount(); // установить длину в 8 или 16 битовой записи
	int ServiseInfo(); // формирование служебной информации
	void Filling(); // заполнение
	void Division(); // разделение на блоки
public:
	Bits(string);
	~Bits();
};