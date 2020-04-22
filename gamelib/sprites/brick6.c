/* Tretis - brick type 6
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "brick.h"

static const int SPRITE_LENGTH = 1;

static const char SPRITE[5][6] = {
    "     ",
    " 11  ",
    " 11  ",
    "     ",
    "     "
};

void tretis_brick6_init(TBrick *b6) {
    b6->sprite.SPRITE = (const char *)SPRITE;
    b6->sprite.LENGTH = SPRITE_LENGTH;
}