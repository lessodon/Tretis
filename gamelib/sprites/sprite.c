/* Tretis - TSprite library (main source)
 * by Tales Upper (github.com/lessodon) © 2020
 */

#include "sprite.h"

#include <stdio.h>
#include <stdbool.h>

static const int SPRITE_LENGTH = 5;
static const int SPRITE_HEIGHT = 7;
static const int SPRITE_WIDTH = 9;

static const char SPRITE[][7][10] = {
    {
        "         ",
        " /sSSs   ",
        " sS      ",
        "  sSSs   ",
        "     S|  ",
        " sSSS/   ",
        "         "
    },
    {
        "         ",
        "  ,ss,   ",
        " ,s      ",
        "  ,ss,   ",
        "     s   ",
        " ,sss    ",
        "         "
    },
    {
        "         ",
        "   ..    ",
        "  .      ",
        "  /p/,   ",
        "     /   ",
        " p///    ",
        "         "
    },
    {
        "         ",
        "         ",
        "         ",
        " /PPPp   ",
        "pp   P   ",
        "PPPP/    ",
        "         "
    },
    {
        "         ",
        "  ,-pPPp ",
        " /p/  /P|",
        "/PPPPP/  ",
        "P/       ",
        "         ",
        "         "
    }
};

static const char* tsprite_get_frame_line_intern(TSprite * sprite, int step, int line) {
  const char * on_step = 0;
  const int length = sprite->LENGTH;
  const int height = sprite->HEIGHT;
  const int width = sprite->WIDTH+1;

  if (!sprite->SPRITE) {
    fprintf(stderr, "%s(): NULL SPRITE!\n", __func__);
    return on_step;
  }
  if (line >= height || line < 0) {
    fprintf(stderr, "%s(): line (%d) overflows height (%d)!\n", __func__, line, height);
    return on_step;
  }

  if (step >= length || step < 0) {
    fprintf(stderr, "%s(): step frame (%d) overflows length (%d)!\n",  __func__, step, length);
    return on_step;
  }

  on_step = sprite->SPRITE + step*(height*width);
  return on_step + line*width;
}

void tsprite_next(TSprite * sprite, void * cb_data) {
    if (sprite->on_change)
        if (sprite->on_change(sprite, 1, cb_data)) return;

    int next = sprite->step+1;
    sprite->step = next == sprite->LENGTH ? 0 : next;
}

void tsprite_prev(TSprite * sprite, void * cb_data) {
    if (sprite->on_change)
      if (sprite->on_change(sprite, -1, cb_data)) return;
    
    int prev = sprite->step-1;
    sprite->step = prev < 0 ? sprite->LENGTH-1 : prev;
}

const char * tsprite_get_frame_line(TSprite * sprite, int step, int line) {
    return tsprite_get_frame_line_intern(sprite, step, line);
}

const char * tsprite_get_line(TSprite * sprite, int line) {
    return tsprite_get_frame_line_intern(sprite, sprite->step, line);
}

void tsprite_init(TSprite * sprite) {
    sprite->on_change = 0;
    sprite->step = 0;

    sprite->SPRITE = (const char *) SPRITE;
    sprite->LENGTH = SPRITE_LENGTH;
    sprite->HEIGHT = SPRITE_HEIGHT;
    sprite->WIDTH = SPRITE_WIDTH;
}