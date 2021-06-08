#include "Bits.h"
#include "Draw.h"

void main(int argc, char** argv) {
	try {
		InitializeMagick(*argv);
		setlocale(LC_ALL, "Russian");
		string _string = "Хабррррррррррррббббббббррр";
		Bits* _bits = new Bits(_string);
		Image image = Draw::BaseElements(_bits);
		image.write("ebat.png");
		system("pause");
	}
	catch (Exception& error) {
		cerr << "Caught Magick++ exception: " << error.what() << endl;
	}
}