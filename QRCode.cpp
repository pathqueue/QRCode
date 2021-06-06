#include "Bits.h"

void main(int argc, char** argv) {
	try {
		InitializeMagick(*argv);
		setlocale(LC_ALL, "Russian");
		string _string = "Хабр";
		Bits* _bits = new Bits(_string);
		system("pause");
	}
	catch (Exception& error) {
		cerr << "Caught Magick++ exception: " << error.what() << endl;
	}
}