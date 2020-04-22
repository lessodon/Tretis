/* Tretis - that game of bricks (library)
 * by Tales Upper (github.com/lessodon) © 2020
 */

#ifndef _TRETIS_H_
#define _TRETIS_H_

#include <wchar.h>
#include <curses.h>

#include "sprites/brick.h"

#define AUTHOR "Tales Upper"
#define AUTHOR_REPOS "github.com/lessodon"
#define TRETIS_VERSION "1.0 beta"
#define TRETIS_NAME "Tretis"
#define TRETIS_YEAR "2020"

#define TH 15
#define TW 20

// UTF-8 symbol for ▢ (square with rounded corners)
// but UTF-8 actually has plenty beautiful squares after this codepoint :)
// ▣, ▤, ▥, ▦, ▧, ▨, ▩
#define T_MTX_BRICK 0x25A2
#define T_MTX_TRANS L' '

#define T_PLAYABLE_LAG 5

#define T_BRICK_WC(BRICK) (T_MTX_BRICK + (BRICK).B)

typedef enum tretis_status TretisStatus;

enum tretis_status {
	// First brick will be thrown
	TRETIS_ON,
	// Bricks falling
	TRETIS_OK,
	// Button pressed
	TRETIS_BP,
	// Game over
	TRETIS_GG
};

typedef struct tretis_game Tretis;

struct tretis_game {
	WINDOW * win;

	wchar_t      matrix[TH][TW];
	int          ev_key;
	int          refresh;

	TretisStatus status;
	int          score;
};

typedef struct tretis_playable TPlayable;

struct tretis_playable {
	TBrick brick;
	// Brick at B(X, Y)
	int xy[2];

	int lag;
};

static int char_icmp(char k, char w) {
	if (k >= 'a')
		k -= 32;
	if (w >= 'a')
		w -= 32;
	return k == w;
}

/** Prepare game
 * player - reset score */
void tretis_init(Tretis * g, int player, WINDOW * win);

/** Event register */
void tretis_do(Tretis * g, int key);

/** Event processor and screen drawer */
void tretis_update(Tretis * g, TPlayable * p);

/** Prepare playable object (actual brick) */
void tplayable_init(TPlayable * p);

/** Throw new playable object */
void tplayable_throw(TPlayable * p, Tretis * g);


/** Fall playable on normal speed */
int tplayable_fall_down(TPlayable * p, Tretis * g);

/** Move playable down when possible */
int tplayable_move_down(TPlayable * p, Tretis * g);

/** Move playable left when possible */
int tplayable_move_left(TPlayable * p, Tretis * g);

/** Move playable right when possible */
int tplayable_move_right(TPlayable * p, Tretis * g);

/** Try to rotate playable */
int tplayable_rotate(TPlayable * p, Tretis * g);

/** Playable overlapping? */
int tplayable_overlap(TPlayable * p, Tretis * g);

/* Playable touching on the top? */
//int tplayable_touch_top(TPlayable * p, Tretis * g);

/** Playable touching on the right? */
int tplayable_touch_right(TPlayable * p, Tretis * g);

/** Playable touching on the bottom? */
int tplayable_touch_bottom(TPlayable * p, Tretis * g);

/** Playable touching on the left? */
int tplayable_touch_left(TPlayable * p, Tretis * g);


/** Write sprite in the game matrix */
void tplayable_put(TPlayable * p, Tretis * g);

/** Is playable on (x, y)? */
int tplayable_on(TPlayable * p, int x, int y);

#endif