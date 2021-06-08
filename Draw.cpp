#include "Draw.h"

map<int, list<int>> levelingNodes = { // выравнивающие узлы
	{1, { 0 } },
	{2, { 18 } },
	{3, { 22 } },
	{4, { 26 } },
	{5, { 30 } },
	{6, { 34 } },
	{7, { 6, 22, 38 } },
	{8, { 6, 24, 42 } },
	{9, { 6, 26, 46 } },
	{10, { 6, 28, 50 } },
	{11, { 6, 30, 54 } },
	{12, { 6, 32, 58 } },
	{13, { 6, 34, 62 } },
	{14, { 6, 26, 46, 66 } },
	{15, { 6, 26, 48, 70 } },
	{16, { 6, 26, 50, 74 } },
	{17, { 6, 30, 54, 78 } },
	{18, { 6, 30, 56, 82 } },
	{19, { 6, 30, 58, 86 } },
	{20, { 6, 34, 62, 90 } },
	{21, { 6, 28, 50, 72, 94 } },
	{22, { 6, 26, 50, 74, 98 } },
	{23, { 6, 30, 54, 78, 102 } },
	{24, { 6, 28, 54, 80, 106 } },
	{25, { 6, 32, 58, 84, 110 } },
	{26, { 6, 30, 58, 86, 114 } },
	{27, { 6, 34, 62, 90, 118 } },
	{28, { 6, 26, 50, 74, 98, 122 } },
	{29, { 6, 30, 54, 78, 102, 126 } },
	{30, { 6, 26, 52, 78, 104, 130 } },
	{31, { 6, 30, 56, 82, 108, 134 } },
	{32, { 6, 34, 60, 86, 112, 138 } },
	{33, { 6, 30, 58, 86, 114, 142 } },
	{34, { 6, 34, 62, 90, 118, 146 } },
	{35, { 6, 30, 54, 78, 102, 126, 150 } },
	{36, { 6, 24, 50, 76, 102, 128, 154 } },
	{37, { 6, 28, 54, 80, 106, 132, 158 } },
	{38, { 6, 32, 58, 84, 110, 136, 162 } },
	{39, { 6, 26, 54, 82, 110, 138, 166 } },
	{40, { 6, 30, 58, 86, 114, 142, 170 } }
};
map<int, list<string>> versionCode = {
	{ 7,  { "000010", "011110", "100110" } },
	{ 8,  { "010001", "011100", "111000" } },
	{ 9,  { "110111", "011000", "000100" } },
	{ 10, { "101001", "111110", "000000" } },
	{ 11, { "001111", "111010", "111100" } },
	{ 12, { "001101", "100100", "011010" } },
	{ 13, { "101011", "100000", "100110" } },
	{ 14, { "110101", "000110", "100010" } },
	{ 15, { "010011", "000010", "011110" } },
	{ 16, { "011100", "010001", "011100" } },
	{ 17, { "111010", "010101", "100000" } },
	{ 18, { "100100", "110011", "100100" } },
	{ 19, { "000010", "110111", "011000" } },
	{ 20, { "000000", "101001", "111110" } },
	{ 21, { "100110", "101101", "000010" } },
	{ 22, { "111000", "001011", "000110" } },
	{ 23, { "011110", "001111", "111010" } },
	{ 24, { "001101", "001101", "100100" } },
	{ 25, { "101011", "001001", "011000" } },
	{ 26, { "110101", "101111", "011100" } },
	{ 27, { "010011", "101011", "100000" } },
	{ 28, { "010001", "110101", "000110" } },
	{ 29, { "110111", "110001", "111010" } },
	{ 30, { "101001", "010111", "111110" } },
	{ 31, { "001111", "010011", "000010" } },
	{ 32, { "101000", "011000", "101101" } },
	{ 33, { "001110", "011100", "010001" } },
	{ 34, { "010000", "111010", "010101" } },
	{ 35, { "110110", "111110", "101001" } },
	{ 36, { "110100", "100000", "001111" } },
	{ 37, { "010010", "100100", "110011" } },
	{ 38, { "001100", "000010", "110111" } },
	{ 39, { "101010", "000110", "001011" } },
	{ 40, { "111001", "000100", "010101" } }
};
map<int, string> maskCode = {
	{ 0, "101010000010010" },
	{ 1, "101000100100101" },
	{ 2, "101111001111100" },
	{ 3, "101101101001011" },
	{ 4, "100010111111001" },
	{ 5, "100000011001110" },
	{ 6, "100111110010111" },
	{ 7, "100101010100000" },
};

void Draw::Offset(Image* image, int** matrix)
{
	int width = image->size().width();
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < width; i++) {
			image->pixelColor(i, k, "white");
			matrix[i][k] = 1;
			image->pixelColor(i, width - k - 1, "white");
			matrix[i][width - k - 1] = 1;
			if (i > 3 && i < width - 4) { 
				image->pixelColor(k, i, "white");
				matrix[k][i] = 1;
				image->pixelColor(width - k - 1, i, "white");
				matrix[width - k - 1][i] = 1;
			}
		}
	}
}

void Draw::DrawSearchPattern(Image* image, int x, int y)
{
	for (int i = 0; i < 7; i++) {
		image->pixelColor(x + i, y, "black");
		image->pixelColor(x + i, y + 6, "black");
		if (i > 0 && i < 6) {
			image->pixelColor(x, y + i, "black");
			image->pixelColor(x + 6, y + i, "black");
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			image->pixelColor(x + i + 2, y + j + 2, "black");
		}
	}
}

void Draw::SearchPatterns(Image* image, int** matrix)
{
	DrawSearchPattern(image, 4, 4);
	DrawSearchPattern(image, 4, image->size().height() - 11);
	DrawSearchPattern(image, image->size().width() - 11, 4);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			matrix[i + 4][j + 4] = 2;
			matrix[i + 4][image->size().height() - 5 - j] = 2;
			matrix[image->size().width() - 5 - i][j + 4] = 2;
		}
	}
}

void Draw::DrawLevelingPattern(Image* image, int x, int y, int** matrix)
{
	image->pixelColor(x, y, "black");
	for (int i = 0; i < 5; i++) {
		image->pixelColor(x - 2 + i, y - 2, "black");
		matrix[x - 2 + i][y - 2] = 3;
		image->pixelColor(x - 2 + i, y + 2, "black");
		matrix[x - 2 + i][y + 2] = 3;
		if (i < 3) {
			image->pixelColor(x - 2, y - 1 + i, "black");
			matrix[x - 2][y - 1 + i] = 3;
			image->pixelColor(x + 2, y - 1 + i, "black");
			matrix[x + 2][y - 1 + i] = 3;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[x - 1 + i][y - 1 + j] = 3;
		}
	}
}

void Draw::LevelingPatterns(Image* image, list<int> centers, int** matrix)
{
	int N = centers.size();
	if (centers.front() != 0) {
		list<int> ::iterator iListIterator = centers.begin();
		list<int> ::iterator jListIterator = centers.begin();
		while (iListIterator != centers.end()) {
			while (jListIterator != centers.end()) {
				if (*centers.begin() == 6) {
					if ((*iListIterator == centers.front() && *jListIterator == centers.front())
						|| (*iListIterator == centers.back() && *jListIterator == centers.front())
						|| (*iListIterator == centers.front() && *jListIterator == centers.back())) { }
					else { DrawLevelingPattern(image, *iListIterator + 4, *jListIterator + 4, matrix); }
				}
				else DrawLevelingPattern(image, *iListIterator + 4, *jListIterator + 4, matrix);
				jListIterator++;
			}
			jListIterator = centers.begin();
			iListIterator++;
		}
	}
}

void Draw::DrawSyncStrips(Image* image, int x1, int y1, int x2, int y2, int** matrix)
{
	bool black = true;
	for (int i = x1 - 1; i < x2; i++) {
		for (int j = y1 - 1; j < y2; j++) {
			if (black) {
				image->pixelColor(i, j, "black");
				matrix[i][j] = 4;
				black = false;
			}
			else {
				image->pixelColor(i, j, "white");
				matrix[i][j] = 4;
				black = true;
			}
		}
	}
}

void Draw::SyncStrips(Image* image, int** matrix)
{
	DrawSyncStrips(image, 11, 11, image->size().width() - 11, 11, matrix);
	DrawSyncStrips(image, 11, 11, 11, image->size().height() - 11, matrix);
}

void Draw::DrawVersionCode(Image* image, list<string> code, int x, int y, int** matrix)
{
	list<string> ::iterator codeIterator = code.begin();
	int i = 0;
	while (codeIterator != code.end()) {
		for (int j = 0; j < 6; j++) {
			if ((*codeIterator)[j] == '1') {
				image->pixelColor(x + j, y + i, "black");
				image->pixelColor(y + i, x + j, "black");
			}
			else { 
				image->pixelColor(x + j, y + i, "white");
				image->pixelColor(y + i, x + j, "white");
			}
			matrix[x + j][y + i] = 5;
			matrix[y + i][x + j] = 5;
		}
		i++;
		codeIterator++;
	}
}

void Draw::VersionCode(Image* image, int version, int** matrix)
{
	if (version > 6) {
		list<string> code = versionCode[version];
		DrawVersionCode(image, code, 4, image->size().height() - 15, matrix);
	}
}

void Draw::DrawMaskAndCorrectionLevelCodeOne(Image* image, string maskStr, int** matrix)
{
	for (int i = 0; i < 6; i++) {
		if (maskStr[i] == '1') image->pixelColor(4 + i, 12, "black");
		else image->pixelColor(4 + i, 12, "white");
		matrix[12][4 + i] = 6;
	}
	if (maskStr[6] == '1') image->pixelColor(11, 12, "black");
	else image->pixelColor(11, 12, "white");
	matrix[12][11] = 6;
	if (maskStr[7] == '1') image->pixelColor(12, 12, "black");
	else image->pixelColor(12, 12, "white");
	matrix[12][12] = 6;
	if (maskStr[8] == '1') image->pixelColor(12, 11, "black");
	else image->pixelColor(12, 11, "white");
	matrix[11][12] = 6;
	for (int i = 9; i < 15; i++) {
		if (maskStr[i] == '1') image->pixelColor(12, 9 + 9 - i, "black");
		else image->pixelColor(12, 9 + 9 - i, "white");
		matrix[9 + 9 - i][12] = 6;
	}
}

void Draw::DrawMaskAndCorrectionLevelCodeTwo(Image* image, string maskStr, int** matrix)
{
	int i = 0;
	for (i = 0; i < 7; i++) {
		if (maskStr[i] == '1') image->pixelColor(12, image->size().height() - 5 - i, "black");
		else image->pixelColor(12, image->size().height() - 5 - i, "white");
		matrix[image->size().height() - 5 - i][12] = 6;
	}
	image->pixelColor(12, image->size().height() - 12, "black");
	matrix[image->size().height() - 12][12] = 7;
	for (i = 0; i < 8; i++) {
		if (maskStr[14 - i] == '1') image->pixelColor(image->size().width() - 5 - i, 12, "black");
		else image->pixelColor(image->size().width() - 5 - i, 12, "white");
		matrix[12][image->size().width() - 5 - i] = 6;
	}
}

void Draw::MaskAndCorrectionLevelCode(Image* image, int** matrix)
{
	/*srand(time(0));
	int maskN = rand() % 8;*/
	int maskN = 0;
	string maskStr = maskCode[maskN];
	DrawMaskAndCorrectionLevelCodeOne(image, maskStr, matrix);
	DrawMaskAndCorrectionLevelCodeTwo(image, maskStr, matrix);
}

Utils Draw::DrawData(Image* image, bool up, int x, int y, string data, int** matrix)
{
	Utils utils;
	utils.done = false;
	utils.remainer = "";
	if (up) {
		int j = 0, k = 0;
		while (true) {
			for (int i = 0; i < 2; i++) {
				if (matrix[y - j][x - i] == 3 || matrix[y - j][x - i] == 4 || matrix[y - j][x - i] == 5 || matrix[y - j][x - i] == 9) continue;
				else if (data[k] == '1') {
					image->pixelColor(x - i, y - j, "black");
					k++;
					if ((x - 4 - i + y - 4 - j) % 2 == 0) image->pixelColor(x - i, y - j, "white");
				}
				else if(k != data.size() + 1) {
					image->pixelColor(x - i, y - j, "white");
					k++;
					if ((x - 4 - i + y - 4 - j) % 2 == 0) image->pixelColor(x - i, y - j, "black");
				}
				if (k != data.size() + 1) matrix[y - j][x - i] = 9;
			}
			j++;
			if ((k == data.size()) && (matrix[y - j][x] == 1 || matrix[y - j][x] == 6)) {
				utils.done = true;
				return utils;
			}
			if(k == data.size() || k == data.size() + 1) {
				return utils;
			}
			else if (matrix[y - j][x] == 1 || matrix[y - j][x] == 6) {
				utils.done = true;
				for (int i = k; i < data.size(); i++) utils.remainer += data[i];
				return utils;
			}
		}	
	}
	else {
		int j = 0, k = 0;
		while (true) {
			for (int i = 0; i < 2; i++) {
				if (matrix[y + j][x - i] == 3 || matrix[y + j][x - i] == 4 || matrix[y + j][x - i] == 5 || matrix[y + j][x - i] == 9) continue;
				else if (data[k] == '1') {
					image->pixelColor(x - i, y + j, "black");
					k++;
					if ((x - 4 - i + y - 4 + j) % 2 == 0) image->pixelColor(x - i, y + j, "white");
				}
				else if (k != data.size() + 1) {
					image->pixelColor(x - i, y + j, "white");
					k++;
					if ((x - 4 - i + y - 4 + j) % 2 == 0) image->pixelColor(x - i, y + j, "black");
				}
				if (k != data.size() + 1) matrix[y + j][x - i] = 9;
			}
			j++;
			if ((k == data.size()) && (matrix[y + j][x] == 1 || matrix[y + j][x] == 2 || matrix[y + j][x] == 6)) {
				utils.done = true;
				return utils;
			}
			if (k == data.size() || k == data.size() + 1) {
				return utils;
			}
			else if (matrix[y + j][x] == 1 || matrix[y + j][x] == 2 || matrix[y + j][x] == 6) {
				utils.done = true;
				for (int i = k; i < data.size(); i++) utils.remainer += data[i];
				return utils;
			}
		}
	}
}

void Draw::DataAddition(Image* image, Bits* bits, int version, int** matrix, int sideSize)
{
	Utils utils;
	utils.done = false;
	utils.remainer = "";
	string byteStr;
	bool flag = true;
	string zeros = "00000000";
	string temp = "11111111";
	int x, y;
	int numberOfColumns = (image->size().width() - 9) / 2;
	int currentNumberOfColumns = numberOfColumns;
	list<bitset<8>> bitsMergedBlocks = bits->getMergedBlocks();
	list<bitset<8>> ::iterator bitsIterator = bitsMergedBlocks.begin();
	while (currentNumberOfColumns > 0) {
		if (flag && bitsIterator == bitsMergedBlocks.end()) {
			byteStr = zeros;
			temp = zeros;
			flag = false;
		}
		if (flag) byteStr = (*bitsIterator).to_string();
		if (utils.remainer != "") {
			byteStr = utils.remainer + byteStr;
			utils.remainer = "";
		}
		if (currentNumberOfColumns > 4)
		{
			if (currentNumberOfColumns % 2 == 0) {
				x = image->size().width() - 5 - (numberOfColumns - currentNumberOfColumns) * 2;
				y = image->size().height() - 5;
			}
			else {
				x = image->size().width() - 5 - (numberOfColumns - currentNumberOfColumns) * 2;
				if (numberOfColumns - currentNumberOfColumns > 3) y = 4;
				else y = 13;
			}
		}
		else if (currentNumberOfColumns == 4) {
			x = image->size().width() - 5 - (numberOfColumns - currentNumberOfColumns) * 2;
			y = image->size().height() - 13;
		}
		else if (currentNumberOfColumns % 2 == 0) {
			x = image->size().width() - 6 - (numberOfColumns - currentNumberOfColumns) * 2;
			if (version < 6) y = image->size().height() - 13;
			else y = image->size().height() - 16;
		}
		else {
			x = image->size().width() - 6 - (numberOfColumns - currentNumberOfColumns) * 2;
			y = 13;
		}

		if (currentNumberOfColumns % 2 == 0) {
			utils = DrawData(image, true, x, y, byteStr, matrix);
			if (utils.done)	currentNumberOfColumns--;
		}
		else {
			utils = DrawData(image, false, x, y, byteStr, matrix);
			if (utils.done) currentNumberOfColumns--;
		}
		bitsIterator++;
		ShowMatrix(matrix, sideSize);
	}
}

int** Draw::MakeMatrix(int sideSize)
{
	int** matrix = new int* [sideSize];
	for (int i = 0; i < sideSize; i++) {
		matrix[i] = new int[sideSize];
	}
	for (int i = 0; i < sideSize; i++) {
		for (int j = 0; j < sideSize; j++) {
			matrix[i][j] = 0;
		}
	}
	return matrix;
}
void Draw::ShowMatrix(int** matrix, int sideSize)
{
	cout << endl << endl;
	int count = 0;
	for (int i = 0; i < sideSize; i++) {
		for (int j = 0; j < sideSize; j++) {
			if (matrix[i][j] != 1) if (matrix[i][j] == 0) { cout << '.' << ' '; count++; }
			else cout << matrix[i][j] << ' ';
		}
		if (matrix[i][4] != 1) cout << endl;
	}
	cout << count << endl;
}

Image Draw::BaseElements(Bits* bits)
{
	int sideSize;
	int version = bits->getVersion();
	stringstream ss;
	string size;
	if (version == 1) { 
		sideSize = 21 + 8;
	}
	else {
		sideSize = levelingNodes[version].back() + 7 + 8;
	}
	
	ss << sideSize << "x" << sideSize;
	ss >> size;
	Geometry size_geom(size);
	Image image(size_geom, "white");
	int** matrix = MakeMatrix(sideSize);
	Offset(&image, matrix);
	SearchPatterns(&image, matrix);
	LevelingPatterns(&image, levelingNodes[version], matrix);
	SyncStrips(&image, matrix);
	VersionCode(&image, version, matrix);
	MaskAndCorrectionLevelCode(&image, matrix);	
	DataAddition(&image, bits, version, matrix, sideSize);
	return image;
}