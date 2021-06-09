#include "Bits.h"
#include "Draw.h"

void main(int argc, char** argv) {
	try {
		InitializeMagick(*argv);
		setlocale(LC_ALL, "Russian");
		string _string = "vk.com/pskovsb";
		Bits* _bits = new Bits(_string);
		Image image = Draw::DrawQRCode(_bits);
		image.write("QRCode.png");
	}
	catch (Exception& error) {
		cerr << "Caught Magick++ exception: " << error.what() << endl;
	}
}