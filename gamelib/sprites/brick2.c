/* Tretis - brick type 2
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "brick.h"

static const int SPRITE_LENGTH = 2;

static const char SPRITE[][5][6] = {
    /* sprite0 */ {
        "     ",
        " 11  ",
        "  11 ",
        "     ",
        "     "
    },
    /* sprite1 */ {
        "     ",
        "   1 ",
        "  11 ",
        "  1  ",
        "     "
    }
};

void tretis_brick2_init(TBrick *b2) {
    b2->sprite.SPRITE = (const char *)SPRITE;
    b2->sprite.LENGTH = SPRITE_LENGTH;
}