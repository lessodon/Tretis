/* Tretis - brick type 7
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "brick.h"

static const int SPRITE_LENGTH = 4;

static const char SPRITE[][5][6] = {
    /* sprite0 */ {
        "     ",
        " 11  ",
        "  1  ",
        "  1  ",
        "     "
    },
    /* sprite1 */ {
        "     ",
        "   1 ",
        " 111 ",
        "     ",
        "     "
    },
    /* sprite2 */ {
        "     ",
        "  1  ",
        "  1  ",
        "  11 ",
        "     "
    },
    /* sprite3 */ {
        "     ",
        "     ",
        " 111 ",
        " 1   ",
        "     "
    }
};

void tretis_brick7_init(TBrick *b7) {
    b7->sprite.SPRITE = (const char *)SPRITE;
    b7->sprite.LENGTH = SPRITE_LENGTH;
}