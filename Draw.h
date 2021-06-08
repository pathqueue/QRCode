#pragma once
#include <sstream>
#include "Bits.h"

struct Utils {
	bool done;
	string remainer;
};

class Draw {
private:
	static void Offset(Image*, int**);
	static void DrawSearchPattern(Image*, int, int); // ���������� ��������� ���� � �����, (x, y) - ���������� ������ �������� ����
	static void SearchPatterns(Image*, int**); // ��������� �����
	static void DrawLevelingPattern(Image*, int, int, int**); // ���������� ������������� ���� � �����, (x, y) - ���������� ������
	static void LevelingPatterns(Image*, list<int>, int**); // ������������� �����
	static void DrawSyncStrips(Image*, int, int, int, int, int**);
	static void SyncStrips(Image*, int**); // ������ �������������
	static void DrawVersionCode(Image*, list<string>, int, int, int**); // ��� ������
	static void VersionCode(Image*, int, int**); // ��� ������
	static void DrawMaskAndCorrectionLevelCodeOne(Image*, string, int**);
	static void DrawMaskAndCorrectionLevelCodeTwo(Image*, string, int**);
	static void MaskAndCorrectionLevelCode(Image*, int**); // ��� ����� � ������ ���������
	static Utils DrawData(Image*, bool, int, int, string, int**);
	static void DataAddition(Image*, Bits*, int, int**, int);
	static int** MakeMatrix(int);
	static void ShowMatrix(int**, int);
public:
	static Image BaseElements(Bits*); // ������� ��������
};