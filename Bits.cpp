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
}

void Bits::Filling() {
	int generalLength = this->ServiseInfo();
	int additionalNulls = 8 - (generalLength % 8);
	bitset<8> temp, tempList;
	for (int i = 0; i < 4; i++) {
		temp[i] = this->codingType[i];
	}
	if (this->infoAmountVer10to40 == 0) {
		for (int i = 0; i < 4; i++) {
			temp[4 + i] = this->infoAmountVer1to9[i];
		}
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 0; i < 4; i++) {
			temp[i] = this->infoAmountVer1to9[4 + i];
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			temp[4 + i] = this->infoAmountVer10to40[i];
		}
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 0; i < 8; i++) {
			temp[i] = this->infoAmountVer10to40[4 + i];
		}
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 0; i < 4; i++) {
			temp[i] = this->infoAmountVer10to40[12 + i];
		}
	}
	tempList = this->stringBits.front();
	this->stringBits.pop_front();
	for (int i = 0; i < this->byteLength; i++) {
		for (int i = 0; i < 4; i++) {
			temp[4 + i] = tempList[i];
		}
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 0; i < 4; i++) {
			temp[i] = tempList[4 + i];
		}
		if (!this->stringBits.empty())
		{ 
			tempList = this->stringBits.front();
			this->stringBits.pop_front();
		}
	}
	for (int i = 8 - additionalNulls; i < 8; i++) {
		temp[i] = 0;
	}
	this->filledBits.push_back(temp);
	this->filledByteLength++;
	if (this->filledByteLength < this->maxInfoAmount[this->version - 1]/8) {
		int n = this->maxInfoAmount[this->version - 1] / 8 - this->filledByteLength;
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				this->filledBits.push_back(this->fillingBits[0]);
				this->filledByteLength++;
			}
			else {
				this->filledBits.push_back(this->fillingBits[1]);
				this->filledByteLength++;
			}
		}
	}
}