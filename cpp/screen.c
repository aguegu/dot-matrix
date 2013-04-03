#include <unistd.h>
#include <stdlib.h>
#include <cursesw.h>
#include <locale.h>

static const unsigned char c_on[] =
{ 0xe2, 0x96, 0xa0, 0x20, 0x00 };
static const unsigned char c_off[] = "官" ;

int main()
{
	setlocale(LC_ALL, "");
	initscr();

	move(5, 15);
	printw("hello, world, %s|%s", c_on, c_off);
	refresh();

	sleep(2);
	endwin();
	exit(EXIT_SUCCESS);
}
