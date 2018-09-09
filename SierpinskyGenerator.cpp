#include <iostream>
#include <time.h>
#include "Screen.h"
using namespace std;
using namespace omarkahol;

int main() {

	srand(time(NULL));

	Screen screen;

	screen.generateBaseTriangle();

	int counter = 0;
	while (true) {

		int elapsed = SDL_GetTicks();
		unsigned char green = ((1 + sin(elapsed * 0.0001)) * 128);
		unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);

		screen.fractalDraw(red, green, blue);

		if (counter > 2000)
			screen.boxBlur();

		screen.update();
		counter ++;
		if (screen.processEvents()==false || counter>2050 ) {
			break;
		}
	}


	return 0;
}
