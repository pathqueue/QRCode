#include "Bits.h"

const int maxInfoAmount[40] = { // массив для определения версии
	128, 224, 352, 512, 688, 864, 992, 1232, 1456, 1728,
	2032, 2320, 2672, 2920, 3320, 3624, 4056, 4504, 5016, 5352,
	5712, 6256, 6880, 7312, 8000, 8496, 9024, 9544, 10136, 10984,
	11640, 12328, 13048, 13800, 14496, 15312, 15936, 16816, 17728, 18672 
}; 
const int numberOfBlocks[40] = { // количество блоков при разбиении
	1, 1, 1, 2, 2, 4, 4, 4, 5, 5,
	5, 8, 9, 9, 10, 10, 11, 13, 14, 16, 
	17, 17, 18, 20, 21, 23, 25, 26, 28, 29, 
	31, 33, 35, 37, 38, 40, 43, 45, 47, 49 
};
const int numberofCorrectionBytes[40] = {  // количество блоков коррекции на один блок
	10, 16, 26, 18, 24, 16, 18, 22, 22, 26, 
	30, 22, 22, 24, 24, 28, 28, 26, 26, 26, 
	26, 28, 28, 28, 28, 28, 28, 28, 28, 28, 
	28, 28, 28, 28, 28, 28, 28, 28, 28, 28 
};
map<int, list<int>> generatingPolynoms = { // генерируюище многочлены
	{10, { 251, 67, 46, 61, 118, 70, 64, 94, 32, 45 }},
	{16, { 120, 104, 107, 109, 102, 161, 76, 3, 91, 191, 147, 169, 182, 194, 225, 120 }} ,
	{18, { 215, 234, 158, 94, 184, 97, 118, 170, 79, 187, 152, 148, 252, 179, 5, 98, 96, 153 }},
	{22, { 210, 171, 247, 242, 93, 230, 14, 109, 221, 53, 200, 74, 8, 172, 98, 80, 219, 134, 160, 105, 165, 231 }},
	{24, { 229, 121, 135, 48, 211, 117, 251, 126, 159, 180, 169, 152, 192, 226, 228, 218, 111, 0, 117, 232, 87, 96, 227, 21 }},
	{26, { 173, 125, 158, 2, 103, 182, 118, 17, 145, 201, 111, 28, 165, 53, 161, 21, 245, 142, 13, 102, 48, 227, 153, 145, 218, 70 }},
	{28, { 168, 223, 200, 104, 224, 234, 108, 180, 110, 190, 195, 147, 205, 27, 232, 201, 21, 43, 245, 87, 42, 195, 212, 119, 242, 37, 9, 123 }},
	{30, { 41, 173, 145, 152, 216, 31, 179, 182, 50, 48, 110, 86, 239, 96, 222, 125, 42, 173, 226, 193, 224, 130, 156, 37, 251, 216, 238, 40, 192, 180 }} 
};
const int galois[256] = { // Поле Галуа
	1, 2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38,
	76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192,
	157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35,
	70, 140, 5, 10, 20, 40, 80, 160, 93, 186, 105, 210, 185, 111, 222, 161,
	95, 190, 97, 194, 153, 47, 94, 188, 101, 202, 137, 15, 30, 60, 120, 240,
	253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163, 91, 182, 113, 226,
	217, 175, 67, 134, 17, 34, 68, 136, 13, 26, 52, 104, 208, 189, 103, 206,
	129, 31, 62, 124, 248, 237, 199, 147, 59, 118, 236, 197, 151, 51, 102, 204,
	133, 23, 46, 92, 184, 109, 218, 169, 79, 158, 33, 66, 132, 21, 42, 84,
	168, 77, 154, 41, 82, 164, 85, 170, 73, 146, 57, 114, 228, 213, 183, 115,
	230, 209, 191, 99, 198, 145, 63, 126, 252, 229, 215, 179, 123, 246, 241, 255,
	227, 219, 171, 75, 150, 49, 98, 196, 149, 55, 110, 220, 165, 87, 174, 65,
	130, 25, 50, 100, 200, 141, 7, 14, 28, 56, 112, 224, 221, 167, 83, 166,
	81, 162, 89, 178, 121, 242, 249, 239, 195, 155, 43, 86, 172, 69, 138, 9,
	18, 36, 72, 144, 61, 122, 244, 245, 247, 243, 251, 235, 203, 139, 11, 22,
	44, 88, 176, 125, 250, 233, 207, 131, 27, 54, 108, 216, 173, 71, 142, 1
};
const int reverseGalois[256] = { // Обратное поле Галуа
	-1, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75,
	4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113,
	5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69,
	29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166,
	6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136,
	54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131, 56, 70, 64,
	30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61,
	202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87,
	7, 112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24,
	227, 165, 153, 119, 38, 184, 180, 124, 17, 68, 146, 217, 35, 32, 137, 46,
	55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190, 97,
	242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162,
	31, 45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246,
	108, 161, 59, 82, 41, 157, 85, 170, 251, 96, 134, 177, 187, 204, 62, 90,
	203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235, 122, 117, 44, 215,
	79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175
};

Bits::Bits(string _string) {
	for (int i = 0; i < _string.length(); i++) {
		this->stringBits.push_back(bitset<8>(_string[i]));
		this->byteLength++;
	}
	this->Filling();
	this->Division();
	this->CreateCorrectionBytes();
	this->BlockMerging();
}

int Bits::getVersion()
{
	return this->version;
}

list<bitset<8>> Bits::getMergedBlocks()
{
	return this->mergedBlocks;
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
	if (generalLength > maxInfoAmount[this->version-1]) {
		this->version++;
		this->SetInfoAmount();
		generalLength = 4 + 8 * this->byteLength;
		if (this->infoAmountVer10to40 == 0) generalLength += this->infoAmountVer1to9.to_string().length();
		else  generalLength += this->infoAmountVer10to40.to_string().length();
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
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 7; i > 3; i--) {
			temp[i] = this->infoAmountVer1to9[i - 4];
		}
	}
	else {
		for (int i = 7; i > 3; i--) {
			temp[i - 4] = this->infoAmountVer10to40[8 + i];
		}
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 7; i > -1; i--) {
			temp[i] = this->infoAmountVer10to40[4 + i];
		}
		this->filledBits.push_back(temp);
		this->filledByteLength++;
		for (int i = 7; i > 3; i--) {
			temp[i] = this->infoAmountVer10to40[i - 4];
		}
	}
	tempList = this->stringBits.front();
	this->stringBits.pop_front();
	for (int i = 0; i < this->byteLength; i++) {
		for (int j = 7; j > 3; j--) {
			temp[j - 4] = tempList[j];
		}
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
	this->filledBits.push_back(temp);
	this->filledByteLength++;
	if (this->filledByteLength < maxInfoAmount[this->version - 1] / 8) {
		int n = maxInfoAmount[this->version - 1] / 8 - this->filledByteLength;
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				this->filledBits.push_back(this->fillingBytes[0]);
				this->filledByteLength++;
			}
			else {
				this->filledBits.push_back(this->fillingBytes[1]);
				this->filledByteLength++;
			}
		}
	}
}

void Bits::Division()
{
	int blocksCount = numberOfBlocks[this->version - 1];
	int blockSize = this->filledByteLength / blocksCount;
	int blocksWithRemainder = this->filledByteLength % blocksCount;
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

void Bits::CreateCorrectionBytes()
{
	int A, B, C, D;
	int correctionBytesCount = numberofCorrectionBytes[this->version - 1];
	list <int> generatedPolynom = generatingPolynoms[correctionBytesCount];
	list <int> ::iterator generatedPolynomIterator;
	list<list<bitset<8>>> ::iterator infoBlocksIterator = this->infoBlocks.begin();
	list<bitset<8>> ::iterator blockIterator;
	list<int> blockArray;
	list<int> ::iterator blockArrayIterator;
	list<bitset<8>> bitsetTemp;
	while (infoBlocksIterator != this->infoBlocks.end()) {
		blockIterator = (*infoBlocksIterator).begin();
		blockArray.clear();
		int blockArraySize = max((*infoBlocksIterator).size(), generatedPolynom.size());
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
			generatedPolynomIterator = generatedPolynom.begin();
			blockArrayIterator = blockArray.begin();
			while (generatedPolynomIterator != generatedPolynom.end()) {
				C = (*generatedPolynomIterator + B) % 255;
				D = galois[C];
				*blockArrayIterator = D ^ *blockArrayIterator;
				blockArrayIterator++;
				generatedPolynomIterator++;
			}
		}
		blockArrayIterator = blockArray.begin();
		for (int i = 0; i < numberofCorrectionBytes[this->version - 1]; i++) {
			bitsetTemp.push_back(bitset<8>(*blockArrayIterator));
			blockArrayIterator++;
		}
		this->correctionBytesBlocks.push_back(bitsetTemp);
		bitsetTemp.clear();
		infoBlocksIterator++;
	}
}

void Bits::BlockMerging()
{
	int correctionBytesSize = numberofCorrectionBytes[this->version-1];
	int blocksCount = numberOfBlocks[this->version - 1];
	int infoBlocksSize = this->filledByteLength / blocksCount;
	int blocksWithRemainder = this->filledByteLength % blocksCount;
	list<list<bitset<8>>> ::iterator infoBlocksIterator = this->infoBlocks.begin();
	list<list<bitset<8>>> ::iterator correctionBytesBlocksIterator = this->correctionBytesBlocks.begin();
	list<bitset<8>> ::iterator blockIterator;
	for (int i = 0; i < infoBlocksSize; i++) {
		while (infoBlocksIterator != this->infoBlocks.end()) {
			blockIterator = (*infoBlocksIterator).begin();
			for (int j = 0; j < i; j++) blockIterator++;
			this->mergedBlocks.push_back(*blockIterator);
			infoBlocksIterator++;
		}
		infoBlocksIterator = this->infoBlocks.begin();
	}
	while (blocksWithRemainder > 0) {
		infoBlocksIterator = this->infoBlocks.end()--;
		infoBlocksIterator--;
		for (int j = 0; j < blocksWithRemainder - 1; j++) infoBlocksIterator--;
		blockIterator = (*infoBlocksIterator).end();
		blockIterator--;
		this->mergedBlocks.push_back(*blockIterator);
		blocksWithRemainder--;
	}
	for (int i = 0; i < correctionBytesSize; i++) {
		while (correctionBytesBlocksIterator != this->correctionBytesBlocks.end())
		{
			blockIterator = (*correctionBytesBlocksIterator).begin();
			for (int j = 0; j < i; j++) blockIterator++;
			this->mergedBlocks.push_back(*blockIterator);
			correctionBytesBlocksIterator++;
		}
		correctionBytesBlocksIterator = this->correctionBytesBlocks.begin();
	}
}