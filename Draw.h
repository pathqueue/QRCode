#pragma once

static class Draw {
private:
	void SearchPatterns(); // поисковые узоры
	void LevelingPatterns(); // выравнивающие узоры
	void SyncStrips(); // полосы синхронизации
	void VersionCode(); // код версии
	void MaskAndCorrectionLevelCode(); // код маски и уровня коррекции
public:
	void BaseElements(); // базовые элементы
};