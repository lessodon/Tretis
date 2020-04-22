/* Tretis - that game of bricks (library main source)
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "tretis.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void tretis_init(Tretis * g, int player, WINDOW * win) {
	int l, c;

	g->win = win;

	for (l=0; l < TH; l++) {
		for (c=0; c < TW; c++)
			g->matrix[l][c] = T_MTX_TRANS;
	}

	g->status = TRETIS_ON;
	g->refresh = 1;

	if (player) g->score = 0;
}

void tretis_do(Tretis * g, int k) {
	if (!k || k == ERR)
		return;
	else if (g->status == TRETIS_OK) {
		g->ev_key = k;
		g->status = TRETIS_BP;
	}
}

/** Draw a box */
static void box_it(WINDOW *win, int y, int x, int Y, int X) {
	int l, c;
	wmove(win, y, x);
	waddch(win, ACS_ULCORNER);
	for (c=1; c <= X; c++)
		waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	for (l=1; l <= Y; l++) {
		wmove(win, y+l, x);
		waddch(win, ACS_VLINE);
		wmove(win, y+l, x+X+1);
		waddch(win, ACS_VLINE);
	}
	wmove(win, y+Y+1, x);
	waddch(win, ACS_LLCORNER);
	for (c=1; c <= X; c++)
		waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
}


/** Refresh game screen */
static void tretis_refresh(Tretis * g, TPlayable * p) {
	int l, c;

	const int SPR_WIDTH = p->brick.sprite.WIDTH;
	const int SPR_HEIGHT = p->brick.sprite.HEIGHT;
	const int REL_X = p->xy[0];
	const int REL_Y = p->xy[1];
	const int REL_WIDTH = SPR_WIDTH + REL_X;
	const int REL_HEIGHT = SPR_HEIGHT + REL_Y;

	const char *sline = NULL;
	
	WINDOW * win = g->win;

	if (g->refresh == 0)
		return;

	wclear(win);

	wmove(win, 0, 6);
	wprintw(win, TRETIS_NAME);
	wmove(win, 2, 1);
	if (g->status == TRETIS_GG)
		wprintw(win, "GAME OVER\n");
	else wprintw(win, "B%d(%d, %d) | (A-D) (X)\n",
		p->brick.B, REL_X, REL_Y);
	wprintw(win, " SCORE: %d\n", g->score);

	box_it(win, 5, 1, TH, TW);
	for (l=0; l < TH; l++) {
		wmove(win, 6+l, 2);
		for (c=0; c < TW; c++) {
			if (tplayable_on(p, c, l)) {
				char b = tbrick_get_line(&(p->brick),
					l - REL_Y)[c - REL_X];
				if (b != T_SPRITE_TRANS)
					wprintw(win, "%lc", T_BRICK_WC(p->brick));
				else wprintw(win, "%lc", g->matrix[l][c]);
			}
			else wprintw(win, "%lc", g->matrix[l][c]);
			// waddch(win, ' ');
		}
	}

	box_it(win, 5, TW+3, 5, 5);
	for (l=0; l < p->brick.sprite.HEIGHT; l++) {
		sline = tbrick_get_frame_line(&(p->brick), 0, l);
		for (c=0; c < p->brick.sprite.WIDTH; c++)
			if (sline[c] != T_SPRITE_TRANS) {
				wmove(win, 6+l, TW+4+c);
				wprintw(win, "%lc", T_BRICK_WC(p->brick));
			}
	}
	wrefresh(win);
	g->refresh = 0;
}

void tretis_update(Tretis * g, TPlayable * p) {
	int success = 1;
	switch (g->status) {
		case TRETIS_ON:
			tplayable_throw(p, g);
			break;

		case TRETIS_GG:
			break;

		case TRETIS_BP:
			if (char_icmp(g->ev_key, 'A')
				|| g->ev_key == KEY_LEFT)
				success = tplayable_move_left(p, g);
			else if (char_icmp(g->ev_key, 'D')
				|| g->ev_key == KEY_RIGHT)
				success = tplayable_move_right(p, g);
			else if (char_icmp(g->ev_key, 'X')
				|| g->ev_key == ' ') {
				success = tplayable_rotate(p, g);
			}
			else if (!tplayable_move_down(p, g)) {
				tplayable_put(p, g);
				// _put() change game status and need a break in this context
				break;
			}

			g->status = TRETIS_OK;
			break;

		default:
			success = 0;
			break;
	}

	if (!success) if (!tplayable_fall_down(p, g))
		tplayable_put(p, g);

	tretis_refresh(g, p);
}

void tretis_filled_line(Tretis * g) {
	int l, c, score, trans;
	for (l=TH-1; l >= 0; l--) {
		// verificação de pontuação
		score = 0;
		trans = 0; // contagem de espaços vazios
		for (c=0; c < TW; c++) {
			if (g->matrix[l][c] == T_MTX_TRANS)
				trans++;
			else
				score += g->matrix[l][c] - T_MTX_BRICK;
		}
		// se a está linha vazia, então não há o que procurar acima
		if (trans == TW)
			break;

		// mas se essa linha está cheia, destrói e incrementa os pontos
		if (c == TW) {
			// TODO: fazer animação de destruição (não essencial)

			g->score += score;
			int subl;
			for (subl=l; subl > 0; subl--) {
				for (c=0; c < TW; c++)
					g->matrix[subl][c] = g->matrix[subl-1][c];
			}

			g->refresh = 1;
			l++;
		}
	}
}


/* Métodos TPlayable */

void tplayable_init(TPlayable * p) {
	srand(time(0));
	memset(p, 0, sizeof(TPlayable));
	p->lag = T_PLAYABLE_LAG;
}

void tplayable_throw(TPlayable * p, Tretis * g) {
	int r = rand()%7 + 1;
	tbrick_init(&(p->brick), r);

	p->xy[0] = (TW - p->brick.sprite.WIDTH)/2;
	p->xy[1] = -(p->brick.sprite.HEIGHT)/2;

	g->status = tplayable_touch_bottom(p, g) ? TRETIS_GG : TRETIS_OK;
	g->refresh = 1;
}

static inline void tplayable_set(TPlayable * p, Tretis * g, int x, int y) {
	p->xy[0] = x;
	p->xy[1] = y;

	g->refresh = 1;
}

int tplayable_on(TPlayable * p, int x, int y) {
	int horz = (x >= p->xy[0]) && x < (p->xy[0] + p->brick.sprite.WIDTH);
	int vert = (y >= p->xy[1]) && y < (p->xy[1] + p->brick.sprite.HEIGHT);

	return vert && horz;
}

int tplayable_fall_down(TPlayable * p, Tretis * g) {
	if (--(p->lag) > 0)
		return 1;
	p->lag = T_PLAYABLE_LAG;

	if (!tplayable_touch_bottom(p, g)) {
		tplayable_set(p, g, p->xy[0], p->xy[1] + 1);
		return 1;
	}
	return 0;
}

int tplayable_move_down(TPlayable * p, Tretis * g) {
	if (!tplayable_touch_bottom(p, g)) {
		tplayable_set(p, g, p->xy[0], p->xy[1] + 1);
		return 1;
	}
	return 0;
}

int tplayable_move_left(TPlayable * p, Tretis * g) {
	if (!tplayable_touch_left(p, g)) {
		tplayable_set(p, g, p->xy[0] - 1, p->xy[1]);
		return 1;
	}
	return 0;
}

int tplayable_move_right(TPlayable * p, Tretis * g) {
	if (!tplayable_touch_right(p, g)) {
		tplayable_set(p, g, p->xy[0] + 1, p->xy[1]);
		return 1;
	}
	return 0;
}

int tplayable_rotate(TPlayable * p, Tretis * g) {
	tbrick_next(&(p->brick));
	if (tplayable_overlap(p, g)) {
		tbrick_prev(&(p->brick));
		return 0;
	}
	g->refresh = 1;
	return 1;
}

void tplayable_put(TPlayable * p, Tretis * g) {
	int l, c;

	const int SPR_WIDTH = p->brick.sprite.WIDTH;
	const int SPR_HEIGHT = p->brick.sprite.HEIGHT;
	const int REL_X = p->xy[0];
	const int REL_Y = p->xy[1];
	const int REL_WIDTH = SPR_WIDTH + REL_X;
	const int REL_HEIGHT = SPR_HEIGHT + REL_Y;

	for (l = REL_Y;
		l < REL_HEIGHT && l < TH;
		l++) {
		if (l >= 0) {
			const char *sline = tbrick_get_line(&(p->brick), l - REL_Y);

			for (c = REL_X; c < REL_WIDTH && c < TW; c++)
				if (c >= 0) if (sline[c - REL_X] != T_SPRITE_TRANS)
					g->matrix[l][c] = T_BRICK_WC(p->brick);
		}
	}

	tretis_filled_line(g);
	g->status = TRETIS_ON;
}

/*int tplayable_touch_top(TPlayable * p, Tretis * g) {
	TODO: implement
	return 0;
}*/

int tplayable_overlap(TPlayable * p, Tretis * g) {
	const int SPR_WIDTH = p->brick.sprite.WIDTH;
	const int SPR_HEIGHT = p->brick.sprite.HEIGHT;
	const int REL_X = p->xy[0];
	const int REL_Y = p->xy[1];
	const int REL_WIDTH = SPR_WIDTH + REL_X;
	const int REL_HEIGHT = SPR_HEIGHT + REL_Y;

	int l, c;
	const char *sline = NULL;
	for (l = REL_Y; l < REL_HEIGHT; l++) {
		sline = tbrick_get_line(&(p->brick), l - REL_Y);
		for (c = REL_X; c < REL_WIDTH; c++)
			if (sline[c - REL_X] != T_SPRITE_TRANS) {
				if ((l < 0 || c < 0) || (l >= TH || c >= TW))
					return 1;
				else if (g->matrix[l][c] != T_MTX_TRANS)
					return 2;
			}
	}

	return 0;
}


int tplayable_touch_left(TPlayable * p, Tretis * g) {
	const int SPR_WIDTH = p->brick.sprite.WIDTH;
	const int SPR_HEIGHT = p->brick.sprite.HEIGHT;
	const int REL_X = p->xy[0];
	const int REL_Y = p->xy[1];
	const int REL_WIDTH = SPR_WIDTH + REL_X;
	const int REL_HEIGHT = SPR_HEIGHT + REL_Y;

	int left, l, c, mc;
	const char *sline = NULL;
	for (left = 0; left < SPR_WIDTH; left++) {
		for (l=0; l < SPR_HEIGHT; l++) {
			sline = tbrick_get_line(&(p->brick), l);
			if (sline[left] != T_SPRITE_TRANS)
				break;
		}
		if (l < SPR_HEIGHT)
			break;
	}
	if (left >= SPR_WIDTH)
		return 0;

	// 1. Dada a coluna do lado esquerdo do TBrick, checar se toca um espaço ocupado na matriz
	for (c = left; c < SPR_WIDTH; c++) {
		for (l = REL_Y; l < REL_HEIGHT && l < TH; l++) {
			mc = REL_X + c - 1;
			if ((l >= 0 && l < TH) && (mc >= 0 && mc < TW)) {
				sline = tbrick_get_line(&(p->brick), l - REL_Y);
				if (sline[c] != T_SPRITE_TRANS
					&& g->matrix[l][mc] != T_MTX_TRANS)
					return 1;
			}
		}
	}

	// 2. Ou se toca a lateral
	if (left + REL_X <= 0)
		return 2;

	return 0;
}

int tplayable_touch_right(TPlayable * p, Tretis * g) {
	const int SPR_WIDTH = p->brick.sprite.WIDTH;
	const int SPR_HEIGHT = p->brick.sprite.HEIGHT;
	const int REL_X = p->xy[0];
	const int REL_Y = p->xy[1];
	const int REL_WIDTH = SPR_WIDTH + REL_X;
	const int REL_HEIGHT = SPR_HEIGHT + REL_Y;

	int right, l, c, mc;
	const char *sline = NULL;
	for (right = SPR_WIDTH-1; right >= 0; right--) {
		for (l=0; l < SPR_HEIGHT; l++) {
			sline = tbrick_get_line(&(p->brick), l);
			if (sline[right] != T_SPRITE_TRANS)
				break;
		}
		if (l < SPR_HEIGHT)
			break;
	}
	if (right < 0)
		return 0;

	// 1. Dada a coluna do lado esquerdo do TBrick, checar se toca um espaço ocupado na matriz
	for (c = right; c >= 0; c--) {
		for (l = REL_Y; l < REL_HEIGHT && l < TH; l++) {
			mc = REL_X + c + 1;
			if ((l >= 0 && l < TH) && (mc >= 0 && mc < TW)) {
				sline = tbrick_get_line(&(p->brick), l - REL_Y);
				if (sline[c] != T_SPRITE_TRANS
					&& g->matrix[l][mc] != T_MTX_TRANS)
					return 1;
			}
		}
	}

	// 2. Ou se toca a lateral
	if (right + REL_X >= TW-1)
		return 2;

	return 0;
}

int tplayable_touch_bottom(TPlayable * p, Tretis * g) {
	const int SPR_WIDTH = p->brick.sprite.WIDTH;
	const int SPR_HEIGHT = p->brick.sprite.HEIGHT;
	const int REL_X = p->xy[0];
	const int REL_Y = p->xy[1];
	const int REL_WIDTH = SPR_WIDTH + REL_X;
	const int REL_HEIGHT = SPR_HEIGHT + REL_Y;

	int foots, l, c, ml;
	const char *sline = NULL;
	for (foots = SPR_HEIGHT-1; foots >= 0; foots--) {
		sline = tbrick_get_line(&(p->brick), foots);
		for (c=0; c < SPR_WIDTH; c++) {
			if (sline[c] != T_SPRITE_TRANS)
				break;
		}
		if (c < SPR_WIDTH)
			break;
	}
	if (foots < 0)
		return 0;

	// 1. Dado a linha dos pés do TBrick, checar se toca um espaço ocupado na matriz
	for (l = foots; l >= 0; l--) { 
		for (c = REL_X; c < REL_WIDTH && c < TW; c++) {
			ml = REL_Y + l + 1;
			if ((ml >= 0 && ml < TH) && (c >= 0 && c < TW)) {
				sline = tbrick_get_line(&(p->brick), l);
				if (sline[c - REL_X] != T_SPRITE_TRANS
					&& g->matrix[ml][c] != T_MTX_TRANS)
					return 1;
			}
		}
	}

	// 2. Ou checar se eles tocam o chão
	if (foots + REL_Y >= TH-1)
		return 2;

	return 0;
}
