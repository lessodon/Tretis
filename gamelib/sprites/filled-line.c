#include "sprite.h"


static const int SPRITE_LENGTH = 12;
static const int SPRITE_HEIGHT = 1;
static const int SPRITE_WIDTH = 11;


static const char SPRITE[][1][11] = {
  {
    "0123456789"
  },
  {
    "----------"
  },
  {
    "    •    "
  },
  {
    "   -=-    "
  },
  {
    "  --==--  "
  },
  {
    "--=====---"
  },
  {
    "=========="
  },
  {
    "=========="
  },
  {
    "====--===="
  },
  {
    "==--  ---="
  },
  {
    "--      -="
  },
  {
    "          "
  }
};



void tfilled_line_init(TSprite * sprite) {
  tsprite_init(sprite);
  sprite->SPRITE = SPRITE;
  sprite->LENGTH = SPRITE_LENGTH;
  sprite->HEIGHT = SPRITE_HEIGHT;
  sprite->WIDTH = SPRITE_WIDTH;
}
