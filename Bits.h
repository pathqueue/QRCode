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
	char const correctionLevel = 'M'; // уровень коррекции
	const bitset<4> codingType = bitset<4>(2); // способ кодировани€
	unsigned int byteLength = 0; // длина в байтах
	unsigned int filledByteLength = 0; // нова€ длина в битах
	unsigned int version = 0; // верси€
	bitset<8> infoAmountVer1to9 = 0; // длина в 8 битовой записи
	bitset<16> infoAmountVer10to40 = 0; // длина в 16 битовой записи
	list<bitset<8>> stringBits; // список 8 битовых записей символов строки
	const bitset<8> fillingBytes[2] = { bitset<8>(236), bitset<8>(17)}; // заполн€ющийе байты
	list<bitset<8>> filledBits; // новый список - служебна€ информаци€ + сообщение + заполн€ющие байты
	list<list<bitset<8>>> infoBlocks; // блоки информации (список в списке)
	list<list<bitset<8>>> correctionBytesBlocks; // блоки байтов коррекции, соответвующие блокам информации
	list<bitset<8>> mergedBlocks; // объединение блоков

	void SetVersion(); // установить версию
	void SetInfoAmount(); // установить длину в 8 или 16 битовой записи
	int ServiseInfo(); // формирование служебной информации
	void Filling(); // заполнение
	void Division(); // разделение на блоки
	void CreateCorrectionBytes(); // создание блоков коррекции
	void BlockMerging(); // объединение блоков
public:
	Bits(string);
	~Bits();
};