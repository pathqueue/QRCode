#pragma once
#include <sstream>

static class Draw {
private:
	static void Offset(Image*);
	static void DrawSearchPattern(Image*, int, int); // нарисовать поисковый узор в точке, (x, y) - координаты левого верхнего угла
	static void SearchPatterns(Image*); // поисковые узоры
	static void DrawLevelingPattern(Image*, int, int); // нарисовать выравнивающий узор в точке, (x, y) - координаты центра
	static void LevelingPatterns(Image*); // выравнивающие узоры
	void SyncStrips(); // полосы синхронизации
	void VersionCode(); // код версии
	void MaskAndCorrectionLevelCode(); // код маски и уровня коррекции
public:
	static Image BaseElements(Bits*); // базовые элементы
};