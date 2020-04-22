/* Tretis - brick type 5
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "brick.h"

static const int SPRITE_LENGTH = 4;

static const char SPRITE[][5][6] = {
    /* sprite0 */ {
        "     ",
        "  11 ",
        "  1  ",
        "  1  ",
        "     "
    },
    /* sprite1 */ {
        "     ",
        "     ",
        " 111 ",
        "   1 ",
        "     "
    },
    /* sprite2 */ {
        "     ",
        "  1  ",
        "  1  ",
        " 11  ",
        "     "
    },
    /* sprite3 */ {
        "     ",
        " 1   ",
        " 111 ",
        "     ",
        "     "
    }
};

void tretis_brick5_init(TBrick *b5) {
    b5->sprite.SPRITE = (const char *)SPRITE;
    b5->sprite.LENGTH = SPRITE_LENGTH;
}