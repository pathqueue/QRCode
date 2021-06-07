#pragma once
#include <sstream>

static class Draw {
private:
	static void Offset(Image*);
	static void DrawSearchPattern(Image*, int, int); // ���������� ��������� ���� � �����, (x, y) - ���������� ������ �������� ����
	static void SearchPatterns(Image*); // ��������� �����
	static void DrawLevelingPattern(Image*, int, int); // ���������� ������������� ���� � �����, (x, y) - ���������� ������
	static void LevelingPatterns(Image*); // ������������� �����
	void SyncStrips(); // ������ �������������
	void VersionCode(); // ��� ������
	void MaskAndCorrectionLevelCode(); // ��� ����� � ������ ���������
public:
	static Image BaseElements(Bits*); // ������� ��������
};