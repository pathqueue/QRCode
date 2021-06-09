#pragma once
#include <sstream>
#include "Bits.h"

struct Utils {
	bool done;
	string remainer;
};

class Draw {
private:
	static void Offset(Image*, int**); // нарисовать отступ - 4 пикселя со всех сторон
	static void DrawSearchPattern(Image*, int, int); // нарисовать поисковый узор в точке, (x, y) - координаты левого верхнего угла
	static void SearchPatterns(Image*, int**); // поисковые узоры
	static void DrawLevelingPattern(Image*, int, int, int**); // нарисовать выравнивающий узор в точке, (x, y) - координаты центра
	static void LevelingPatterns(Image*, list<int>, int**); // выравнивающие узоры
	static void DrawSyncStrips(Image*, int, int, int, int, int**); // нарисовать полосы синхронизации
	static void SyncStrips(Image*, int**); // полосы синхронизации
	static void DrawVersionCode(Image*, list<string>, int, int, int**); // нарисовать код версии
	static void VersionCode(Image*, int, int**); // код версии
	static void DrawMaskAndCorrectionLevelCodeOne(Image*, string, int**); // нарисовать код маски и уровень коррекции в левом верхнем углу
	static void DrawMaskAndCorrectionLevelCodeTwo(Image*, string, int**); // нарисовать код маски и уровень коррекции в левом нижнем + правом верхнем углу
	static void MaskAndCorrectionLevelCode(Image*, int**); // код маски и уровня коррекции
	static Utils DrawData(Image*, bool, int, int, string, int**); // нарисовать информацию
	static void DataAddition(Image*, Bits*, int, int**); // заполнить все оставшееся пространство информацией
	static int** MakeMatrix(int); // создать матрицу QR-кода
	static void ShowMatrix(int**, int); // вывести матрицу на экран
public:
	static Image DrawQRCode(Bits*); // создать QR-код
};