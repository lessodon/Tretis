/* Tretis - brick type 3
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "brick.h"

static const int SPRITE_LENGTH = 4;

static const char SPRITE[][5][6] = {
    /* sprite0 */ {
        "     ",
        "     ",
        "  1  ",
        " 111 ",
        "     "
    },
    /* sprite1 */ {
        "     ",
        " 1   ",
        " 11  ",
        " 1   ",
        "     "
    },
    /* sprite2 */ {
        "     ",
        " 111 ",
        "  1  ",
        "     ",
        "     "
    },
    /* sprite3 */ {
        "     ",
        "   1 ",
        "  11 ",
        "   1 ",
        "     "
    }
};

void tretis_brick3_init(TBrick *b3) {
    b3->sprite.SPRITE = (const char *)SPRITE;
    b3->sprite.LENGTH = SPRITE_LENGTH;
}