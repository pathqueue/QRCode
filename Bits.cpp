#include "Bits.h"

Bits::Bits(string _string) {
	for (int i = 0; i < _string.length(); i++) {
		this->stringBits.push_back(bitset<8>(_string[i]));
		this->byteLength++;
	}
	this->Filling();
}

Bits::~Bits() {

}

void Bits::SetVersion() {
	unsigned int bitLength = this->byteLength * 8;
	for (int i = 0; i < 40; i++) {
		if (maxInfoAmount[i] > bitLength) {
			this->version = i + 1;
			break;
		}
	}
	if (version == 0) ;
}

void Bits::SetInfoAmount() {
	if (this->version < 10) this->infoAmountVer1to9 = bitset<8>(this->byteLength);
	else {
		this->infoAmountVer10to40 = bitset<16>(this->byteLength);
		this->infoAmountVer1to9 = 0;
	}
}

int Bits::ServiseInfo() {
	this->SetVersion();
	this->SetInfoAmount();
	int generalLength = 4 + 8 * this->byteLength;
	if (this->infoAmountVer10to40 == 0) generalLength += this->infoAmountVer1to9.to_string().length();
	else  generalLength += this->infoAmountVer10to40.to_string().length();
	if (generalLength > this->maxInfoAmount[this->version-1]) {
		this->version++;
		this->SetInfoAmount();
	}
	return generalLength;
}

void Bits::Filling() {
	int generalLength = this->ServiseInfo();
	int additionalNulls = 8 - (generalLength % 8);
	bitset<8> temp, tempList;
	for (int i = 7; i > 3; i--) {
		temp[i] = this->codingType[7 - i];
	}
	if (this->infoAmountVer10to40 == 0) {
		for (int i = 7; i > 3; i--) {
			temp[i - 4] = this->infoAmountVer1to9[i];
		}
		cout << temp;
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 7; i > 3; i--) {
			temp[i] = this->infoAmountVer1to9[i - 4];
		}
	}
	else {
		for (int i = 7; i > 3; i--) {
			temp[i - 4] = this->infoAmountVer10to40[i];
		}
		cout << temp;
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 7; i > -1; i--) {
			temp[i] = this->infoAmountVer10to40[i - 4];
		}
		cout << temp;
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 7; i > 3; i--) {
			temp[i] = this->infoAmountVer10to40[i - 12];
		}
	}
	tempList = this->stringBits.front();
	this->stringBits.pop_front();
	for (int i = 0; i < this->byteLength; i++) {
		for (int j = 7; j > 3; j--) {
			temp[j - 4] = tempList[j];
		}
		cout << temp;
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int j = 7; j > 3; j--) {
			temp[j] = tempList[j - 4];
		}
		if (!this->stringBits.empty())
		{
			tempList = this->stringBits.front();
			this->stringBits.pop_front();
		}
	}
	for (int i = 3; i >= 0; i--) {
		temp[i] = 0;
	}
	cout << temp << ' ';
	this->filledBits.push_back(temp);
	this->filledByteLength++;
	if (this->filledByteLength < this->maxInfoAmount[this->version - 1] / 8) {
		int n = this->maxInfoAmount[this->version - 1] / 8 - this->filledByteLength;
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				cout << this->fillingBytes[0] << ' ';
				this->filledBits.push_back(this->fillingBytes[0]);
				this->filledByteLength++;
			}
			else {
				cout << this->fillingBytes[1] << ' ';
				this->filledBits.push_back(this->fillingBytes[1]);
				this->filledByteLength++;
			}
		}
	}
}

void Bits::Division()
{
	int blocksCount = this->blocksCount[this->version - 1];
	int blockSize = this->byteLength / blocksCount;
	int blocksWithRemainder = this->byteLength % blocksCount;
	list<bitset<8>> temp;
	for (int i = 0; i < blocksCount - blocksWithRemainder; i++) {
		for (int j = 0; j < blockSize; j++) {
			temp.push_back(this->filledBits.front());
			this->filledBits.pop_front();
		}
		this->infoBlocks.push_back(temp);
		temp.clear();
	}

	for (int i = 0; i < blocksWithRemainder; i++) {
		for (int j = 0; j < blockSize + 1; j++) {
			temp.push_back(this->filledBits.front());
			this->filledBits.pop_front();
		}
		this->infoBlocks.push_back(temp);
		temp.clear();
	}
}

void Bits::createCorrectionBytes() // создание байтов коррекции
{
	int A, B;
	int correctionBytesCount = this->correctionBytesCount[this->version - 1];
	list <int> correctionBytes = this->generatingPolynoms[correctionBytesCount];
	list<list<bitset<8>>> :: iterator infoBlocksIterator = this->infoBlocks.begin();
	list<bitset<8>> :: iterator blockIterator;
	list<int> temp;
	list<int> :: iterator tempIterator;
	list<int> blockArray;
	list<int> :: iterator blockArrayIterator;
	list<bitset<8>> bitsetTemp;
	while (infoBlocksIterator != this->infoBlocks.end()) {
		temp = correctionBytes;
		blockIterator = (*infoBlocksIterator).begin();
		int blockArraySize = max((*infoBlocksIterator).size(), correctionBytes.size());
		for (int i = 0; i < blockArraySize; i++) {
			if (blockIterator == (*infoBlocksIterator).end())
			{
				blockArray.push_back(0);
			}
			else 
			{
				blockArray.push_back((*blockIterator).to_ulong());
				blockIterator++;
			}
		}

		for (int i = 0; i < (*infoBlocksIterator).size(); i++) {
			A = blockArray.front();
			blockArray.pop_front();
			blockArray.push_back(0);
			if (A == 0) continue;
			B = reverseGalois[A];
			tempIterator = temp.begin();
			while (tempIterator != temp.end()) {
				*tempIterator = (*tempIterator + B) % 255;
				tempIterator++;
			}
			tempIterator = temp.begin();
			while (tempIterator != temp.end()) {
				*tempIterator = galois[*tempIterator];
				tempIterator++;
			}
			tempIterator = temp.begin();
			blockArrayIterator = blockArray.begin();
			while (tempIterator != temp.end()) {
				*tempIterator = *tempIterator ^ *blockArrayIterator;
				tempIterator++;
				blockArrayIterator++;
			}
		}
		tempIterator = temp.begin();
		while (tempIterator != temp.end()) {
			bitsetTemp.push_back(bitset<8>(*tempIterator));
			tempIterator++;
		}
		this->correctionBytesBlock.push_back(bitsetTemp);
		infoBlocksIterator++;
	}
}
