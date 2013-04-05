#include <unistd.h>
#include <stdlib.h>
#include <cursesw.h>
#include <locale.h>

#include "dot-matrix.h"
#include "dot-font.h"
#include "dot-string.h"
#include "vfont_6x3.h"

static const unsigned char c_on[] =
{ 0xe2, 0x96, 0xa0, 0x20, 0x00 };
static const unsigned char c_off[] =
{ 0xe2, 0x96, 0xa1, 0x20, 0x00 };

int main()
{
	DotMatrix dm(40, 8);
	DotFont df(dm);
	DotString ds(df, 16);
	df.setPattern(VFONT_6X3, VFONT_6X3_STATE);

	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();

	timeout(20);

//	dm.setRect(1, 1, 30, 14);
//	dm.setRect(2, 2, 29, 13, false);
//	dm.setLine(2, 2, 29, 13);

	ds.printf("0123456789");
	ds.postAt(0, 1);	

	dm.setMoveDirection(DotMatrix::BIT_IN_COL_POSI);

	while (getch() != 'q') {
//		clear();
		for (int r = 0; r < dm.countRow(); r++) {
			move(r, 0);
			for (int c = 0; c < dm.countCol(); c++)
				printw("%s", dm.getDot(c, r)? c_on: c_off);
		}
		refresh();
		//dm.move(true);
	}

	endwin();
	exit(EXIT_SUCCESS);
}
