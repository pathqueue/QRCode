#include "Bits.h"
#include "Draw.h"

map<int, list<int>> levelingNodes = { // выравнивающие узлы
		{1, { 0 }},
		{2, { 18 }},
		{3, { 22 }},
		{4, { 26 }},
		{5, { 30 }},
		{6, { 34 }},
		{7, { 6, 22, 38 }},
		{8, { 6, 24, 42 }},
		{9, { 6, 26, 46 }},
		{10, { 6, 28, 50 }},
		{11, { 6, 30, 54 }},
		{12, { 6, 32, 58 }},
		{13, { 6, 34, 62 }},
		{14, { 6, 26, 46, 66 }},
		{15, { 6, 26, 48, 70 }},
		{16, { 6, 26, 50, 74 }},
		{17, { 6, 30, 54, 78 }},
		{18, { 6, 30, 56, 82 }},
		{19, { 6, 30, 58, 86 }},
		{20, { 6, 34, 62, 90 }},
		{21, { 6, 28, 50, 72, 94 }},
		{22, { 6, 26, 50, 74, 98 }},
		{23, { 6, 30, 54, 78, 102 }},
		{24, { 6, 28, 54, 80, 106 }},
		{25, { 6, 32, 58, 84, 110 }},
		{26, { 6, 30, 58, 86, 114 }},
		{27, { 6, 34, 62, 90, 118 }},
		{28, { 6, 26, 50, 74, 98, 122 }},
		{29, { 6, 30, 54, 78, 102, 126 }},
		{30, { 6, 26, 52, 78, 104, 130 }},
		{31, { 6, 30, 56, 82, 108, 134 }},
		{32, { 6, 34, 60, 86, 112, 138 }},
		{33, { 6, 30, 58, 86, 114, 142 }},
		{34, { 6, 34, 62, 90, 118, 146 }},
		{35, { 6, 30, 54, 78, 102, 126, 150 }},
		{36, { 6, 24, 50, 76, 102, 128, 154 }},
		{37, { 6, 28, 54, 80, 106, 132, 158 }},
		{38, { 6, 32, 58, 84, 110, 136, 162 }},
		{39, { 6, 26, 54, 82, 110, 138, 166 }},
		{40, { 6, 30, 58, 86, 114, 142, 170 }} 
};
map<int, list<int>> versionCode = {
	{7, { 6, 22, 38 }},
	{ 8, { 6, 24, 42 } },
	{ 9, { 6, 26, 46 } },
	{ 10, { 6, 28, 50 } },
	{ 11, { 6, 30, 54 } },
	{ 12, { 6, 32, 58 } },
	{ 13, { 6, 34, 62 } },
	{ 14, { 6, 26, 46, 66 } },
	{ 15, { 6, 26, 48, 70 } },
	{ 16, { 6, 26, 50, 74 } },
	{ 17, { 6, 30, 54, 78 } },
	{ 18, { 6, 30, 56, 82 } },
	{ 19, { 6, 30, 58, 86 } },
	{ 20, { 6, 34, 62, 90 } },
	{ 21, { 6, 28, 50, 72, 94 } },
	{ 22, { 6, 26, 50, 74, 98 } },
	{ 23, { 6, 30, 54, 78, 102 } },
	{ 24, { 6, 28, 54, 80, 106 } },
	{ 25, { 6, 32, 58, 84, 110 } },
	{ 26, { 6, 30, 58, 86, 114 } },
	{ 27, { 6, 34, 62, 90, 118 } },
	{ 28, { 6, 26, 50, 74, 98, 122 } },
	{ 29, { 6, 30, 54, 78, 102, 126 } },
	{ 30, { 6, 26, 52, 78, 104, 130 } },
	{ 31, { 6, 30, 56, 82, 108, 134 } },
	{ 32, { 6, 34, 60, 86, 112, 138 } },
	{ 33, { 6, 30, 58, 86, 114, 142 } },
	{ 34, { 6, 34, 62, 90, 118, 146 } },
	{ 35, { 6, 30, 54, 78, 102, 126, 150 } },
	{ 36, { 6, 24, 50, 76, 102, 128, 154 } },
	{ 37, { 6, 28, 54, 80, 106, 132, 158 } },
	{ 38, { 6, 32, 58, 84, 110, 136, 162 } },
	{ 39, { 6, 26, 54, 82, 110, 138, 166 } },
	{ 40, { 6, 30, 58, 86, 114, 142, 170 } }
};

void Draw::Offset(Image* image)
{
	int width = image->size().width();
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < width; i++)
		{
			image->pixelColor(i, k, "white");
			image->pixelColor(i, width - k - 1, "white");
			if (i > 3 && i < width - 4)
			{ 
				image->pixelColor(k, i, "white");
				image->pixelColor(width - k - 1, i, "white");
			}
		}
	}
}

void Draw::DrawSearchPattern(Image* image, int x, int y)
{
	for (int i = 0; i < 7; i++)
	{
		image->pixelColor(x + i, y, "black");
		image->pixelColor(x + i, y + 6, "black");
		if (i > 0 && i < 6)
		{
			image->pixelColor(x, y + i, "black");
			image->pixelColor(x + 6, y + i, "black");
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			image->pixelColor(x + i + 2, y + j + 2, "black");
		}
	}
}

void Draw::SearchPatterns(Image* image)
{
	DrawSearchPattern(image, 4, 4);
	DrawSearchPattern(image, 4, image->size().height() - 11);
	DrawSearchPattern(image, image->size().width() - 11, 4);
}

void Draw::DrawLevelingPattern(Image* image, int x, int y)
{
	image->pixelColor(x, y, "black");
	for (int i = 0; i < 5; i++)
	{
		image->pixelColor(x - 2 + i, y - 2, "black");
		image->pixelColor(x - 2 + i, y + 2, "black");
		if (i < 3)
		{
			image->pixelColor(x - 2, y - 1 + i, "black");
			image->pixelColor(x + 2, y - 1 + i, "black");
		}
	}
}

void Draw::LevelingPatterns(Image* image)
{

}

Image Draw::BaseElements(Bits* bits)
{
	int sideSize;
	int version = bits->getVersion();
	stringstream ss;
	string size;
	if (version == 1)
	{ 
		sideSize = 21 + 8;
	}
	else 
	{
		sideSize = levelingNodes[version].back() + 7 + 8;
	}
	ss << sideSize << "x" << sideSize;
	ss >> size;
	Geometry size_geom(size);
	Image image(size_geom, "white");
	
	Offset(&image);
	SearchPatterns(&image);
	LevelingPatterns(&image);
	return image;
}