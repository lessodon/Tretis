/* Tretis - that game of bricks (menu source)
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include <locale.h>
#include <stdio.h>

#include "gamelib/tretis.h"

#define WIN_MIN_WIDTH (TW+10)
#define WIN_MIN_HEIGHT (TH+7)
#define HALFDELAY_OK 2

static int on_game();
static void about();

int main() {
	int re, is_a_horse;
	setlocale(LC_ALL, "C.UTF-8");

	do {
		is_a_horse = 0;
		printf("\n%s v%s by %s\n", TRETIS_NAME, TRETIS_VERSION, AUTHOR);

		puts("\n\n\t MAIN MENU\n");
		puts(" (1) Start");
		puts(" (2) About");
		puts(" (3) Quit");
		scanf("%d", &re);
		getchar();

		switch (re) {
			case 1:
				break;
			case 2:
				about();
				puts("\nPress ENTER to continue...");
				getchar();
				is_a_horse = 1;
				break;
			case 3:
				return 0;
			default:
				puts("You horse, mah?!!");
				is_a_horse = 1;
		}

	} while (is_a_horse);

	return on_game();
}

static int on_game() {
	Tretis       game;
	TPlayable    playable;
	TretisStatus last;
	int          key = 0;

	initscr();
	do {
		int l, c;
		getmaxyx(stdscr, l, c);
		if (WIN_MIN_HEIGHT > l || WIN_MIN_WIDTH > c) {
			endwin();
			fprintf(stderr, "Your terminal window's less than %dx%d size.\n",
				WIN_MIN_WIDTH, WIN_MIN_HEIGHT);
			return -1;
		}
	} while(0);
	halfdelay(2);
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);

	tretis_init(&game, 1, stdscr);
	tplayable_init(&playable);
	last = game.status;

	while (!char_icmp(key, 'Q')) {
		tretis_do(&game, key);
		tretis_update(&game, &playable);

		if (game.status != last) {
			if (game.status == TRETIS_GG)
				cbreak();
			else if (game.status == TRETIS_OK)
				halfdelay(HALFDELAY_OK);
		}

		key = getch();

		if (game.status == TRETIS_GG)
			tretis_init(&game, 0, stdscr);
	}

	endwin();
	return 0;
}

static void about() {
	puts("\n");
	printf("%s v%s by %s %lc %s\n",
			TRETIS_NAME, TRETIS_VERSION, AUTHOR,
			(wchar_t) 0x00A9, TRETIS_YEAR);
	puts("\"that game of bricks\"\n");

	puts("\nGREETINGS!!!\n");
	puts("\"Tretis\" name is Arthur C. (@arthurware@mastodon.com.br) idea.\n");

	printf("\nACTUAL ABOUT SECTION %lc\n\n", 0x1F914);
	puts("The idea to develop this came after watching a video from Tropia (brazilian \"youtuber\") talking about \"Por que empilhar blocos é tão bom?\".");
	puts("This game is also a challenge to prove myself I CAN develop a more complex program than just simple maths and analysis tools.");
	puts("That's because it was thought days after giving up a great opportunity for my developer career, because I was exhausted and very discouraged.\n");

	puts("Tretis can run fine on Termux if it's installed on your Android device.");
	puts("Make sure \"ncurses\" library, \"make\" and a good C compiler are installed, and you can compile the game there! ;)\n");

	puts("\nCONTACT ME!\n");
	puts("My bricks are destroying your computer's head? Please contact me!");
	printf("%lc GitHub: /lessodon\n", 0x1F4BB);
	printf("%lc instagram.com/lonelyagboy\n", 0x1F4F8);
	printf("%lc mstdn.social/@lonelyagboy\n", 0x1F418);
}
