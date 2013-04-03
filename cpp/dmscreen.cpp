#include <unistd.h>
#include <stdlib.h>
#include <cursesw.h>
#include <locale.h>

static const unsigned char c_on[] =
{ 0xe2, 0x96, 0xa0, 0x20, 0x00 };
static const unsigned char c_off[] =
{ 0xe2, 0x96, 0xa1, 0x20, 0x00 };

int main()
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();

	for (int r = 0; r < 16; r++) {
		for (int c = 0; c < 32; c++)
			printw("%s", c_on);
		printw("\n");		
	}
	refresh();

	while(getch() != 'q');
	endwin();
	exit(EXIT_SUCCESS);
}
