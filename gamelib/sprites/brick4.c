/* Tretis - brick type 4
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "brick.h"

static const int SPRITE_LENGTH = 2;

static const char SPRITE[][5][6] = {
    /* sprite0 */ {
        "     ",
        "  11 ",
        " 11  ",
        "     ",
        "     "
    },
    /* sprite1 */ {
        "     ",
        "  1  ",
        "  11 ",
        "   1 ",
        "     "
    }
};

void tretis_brick4_init(TBrick *b4) {
    b4->sprite.SPRITE = (const char *)SPRITE;
    b4->sprite.LENGTH = SPRITE_LENGTH;
}