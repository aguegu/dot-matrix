#include <unistd.h>
#include <stdlib.h>
#include <cursesw.h>
#include <locale.h>

#include "dot-matrix.h"

static const unsigned char c_on[] =
{ 0xe2, 0x96, 0xa0, 0x20, 0x00 };
static const unsigned char c_off[] =
{ 0xe2, 0x96, 0xa1, 0x20, 0x00 };

int main()
{
	DotMatrix dm(32, 16);

	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();

	dm.setRect(1, 1, 30, 14);
	dm.setRect(2, 2, 29, 13, false);

	dm.setLine(2, 2, 29, 13);

	for (int r = 0; r < dm.countRow(); r++) {
		for (int c = 0; c < dm.countCol(); c++)
			printw("%s", dm.getDot(c, r)? c_on: c_off);
		printw("\n");		
	}
	refresh();

	while(getch() != 'q');
	endwin();
	exit(EXIT_SUCCESS);
}
