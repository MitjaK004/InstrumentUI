#include <fstream>
#include <stdlib.h>
#include "window.h"
using namespace UI;

int main()
{
	WINDOW okno("baje");

	TEXT t1("BAJE");

	okno << t1;

	SHAPE a1("wall.png");

	a1.squareXY(0.1, 0.1, 0.3);

	okno << a1;

	okno.createWindow();
	return 0;
}