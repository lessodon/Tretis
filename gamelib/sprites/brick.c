/* Tretis - brick model (main source)
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include <stdlib.h>
#include <stdio.h>

#include "brick.h"

void tbrick_init(TBrick * brick, int which) {
    tsprite_init((TSprite*)brick);
    brick->sprite.WIDTH = 5;
    brick->sprite.HEIGHT = 5;

    brick->B = which;

    switch (which) {
        case 1:
            tretis_brick1_init(brick);
            break;
        case 2:
            tretis_brick2_init(brick);
            break;
        case 3:
            tretis_brick3_init(brick);
            break;
        case 4:
            tretis_brick4_init(brick);
            break;
        case 5:
            tretis_brick5_init(brick);
            break;
        case 6:
            tretis_brick6_init(brick);
            break;
        case 7:
            tretis_brick7_init(brick);
            break;
        default:
            fprintf(stderr, "FATAL: unknown brick (%d) being initialized!\n", which);
            abort();
    }
}