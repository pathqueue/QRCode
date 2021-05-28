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

void Bits::ServiseInfo() {
	this->SetVersion();
	this->SetInfoAmount();
	unsigned int generalLength = this->codingType.to_string().length() + 8 * this->byteLength;
	if (this->infoAmountVer10to40 == 0) generalLength += this->infoAmountVer1to9.to_string().length();
	else  generalLength += this->infoAmountVer10to40.to_string().length();
	if (generalLength > this->maxInfoAmount[this->version-1]) {
		this->version++;
		this->SetInfoAmount();
	}
}

void Bits::Filling() {
	this->ServiseInfo();
}