/* Tretis - brick type 1
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "brick.h"

static const int SPRITE_LENGTH = 2;

static const char SPRITE[][5][6] = {
    /* sprite0 */ {
        "  1  ",
        "  1  ",
        "  1  ",
        "  1  ",
        "     "
    },
    /* sprite1 */ {
        "     ",
        "     ",
        " 1111",
        "     ",
        "     "
    }
};

void tretis_brick1_init(TBrick *b1) {
    b1->sprite.SPRITE = (const char *)SPRITE;
    b1->sprite.LENGTH = SPRITE_LENGTH;
}