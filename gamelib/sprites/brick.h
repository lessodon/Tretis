/* Tretis - brick model
 * by Tales Upper (github.com/lessodon) © 2020
 */

#ifndef _TRETIS_BRICK_H_
#define _TRETIS_BRICK_H_

#include "sprite.h"

typedef struct tretis_brick TBrick;

struct tretis_brick {
    TSprite sprite;
    int B;
};

static inline void
tbrick_next(TBrick * brick) {
    return tsprite_next(&(brick->sprite), 0);
}

static inline void
tbrick_prev(TBrick * brick) {
    return tsprite_prev(&(brick->sprite), 0);
}

static inline const char *
tbrick_get_frame_line(TBrick * brick, int frame, int line) {
    return tsprite_get_frame_line(&(brick->sprite), frame, line);
}

static inline const char *
tbrick_get_line(TBrick * brick, int line) {
    return tsprite_get_line(&(brick->sprite), line);
}

void tbrick_init(TBrick * brick, int which);


void tretis_brick1_init(TBrick *b1);
void tretis_brick2_init(TBrick *b2);
void tretis_brick3_init(TBrick *b3);
void tretis_brick4_init(TBrick *b4);
void tretis_brick5_init(TBrick *b5);
void tretis_brick6_init(TBrick *b6);
void tretis_brick7_init(TBrick *b7);




/*
==== PEÇAS DO TRETIS ====

1:
   X X X X   X
             X
             X
             X


2:
   X X        X
     X X    X X
            X


3:
     X      X     X X X     X
   X X X    X X     X     X X
            X               X


4:
     X X    X
   X X      X X
              X


5:
   X X   X X X X     X   X
   X           X     X   X X X X
   X                 X
   X               X X


6:
   X X
   X X


7:
  X X         X   X     X X X X
    X   X X X X   X     X
    X             X
    X             X X

_ _ _ _ _ _
| 0 0 0 0 0
| 0 0 0 0 0
| 0 0 0 0 0
| 0 0 0 0 0
| 0 0 0 0 0
*/

#endif