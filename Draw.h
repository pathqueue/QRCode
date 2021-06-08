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
	static void DrawSearchPattern(Image*, int, int); // нарисовать поисковый узор в точке, (x, y) - координаты левого верхнего угла
	static void SearchPatterns(Image*, int**); // поисковые узоры
	static void DrawLevelingPattern(Image*, int, int, int**); // нарисовать выравнивающий узор в точке, (x, y) - координаты центра
	static void LevelingPatterns(Image*, list<int>, int**); // выравнивающие узоры
	static void DrawSyncStrips(Image*, int, int, int, int, int**);
	static void SyncStrips(Image*, int**); // полосы синхронизации
	static void DrawVersionCode(Image*, list<string>, int, int, int**); // код версии
	static void VersionCode(Image*, int, int**); // код версии
	static void DrawMaskAndCorrectionLevelCodeOne(Image*, string, int**);
	static void DrawMaskAndCorrectionLevelCodeTwo(Image*, string, int**);
	static void MaskAndCorrectionLevelCode(Image*, int**); // код маски и уровня коррекции
	static Utils DrawData(Image*, bool, int, int, string, int**);
	static void DataAddition(Image*, Bits*, int, int**, int);
	static int** MakeMatrix(int);
	static void ShowMatrix(int**, int);
public:
	static Image BaseElements(Bits*); // базовые элементы
};