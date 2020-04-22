/* Tretis - TSprite library
 * by Tales Upper (github.com/lessodon) © 2020
 */

#ifndef _TRETIS_SPRITE_H_
#define _TRETIS_SPRITE_H_

// Transparent elements are always blank spaces
#define T_SPRITE_TRANS ' '

typedef struct tretis_sprite TSprite;

struct tretis_sprite {
    /** Sprite action before frame change. [OPTIONAL]
     * data - see tsprite_next()
     * @return int - frame change is cancelled if value is not 0 */
    int (* on_change)(TSprite * sprite, int s, void * data);
    
    /** Pointer to static matrix. */
    const char * SPRITE;
    

    // LENGTH refers to array3d[LENGTH][][]
    int LENGTH;
     // HEIGHT refers to array3d[][HEIGHT][]
    int HEIGHT;
    // WIDTH refers to array3d[][][WIDTH]
    int WIDTH;

    // current frame step
    int step;
};

/** Prepare sprite.
 * sprite{ SPRITE and LENGTH } should be set manually after calling this. */
void tsprite_init(TSprite * sprite);

/** Skip current frame step.
 *
 * cb_data - params for on_change() */
void tsprite_next(TSprite * sprite, void * cb_data);

/** Roll back to previous frame step. */
void tsprite_prev(TSprite * sprite, void * cb_data);

/** Get character array relative to sprite 'line' and 'frame'. */
const char * tsprite_get_frame_line(TSprite * sprite, int frame, int line);

/** Get character array relative to sprite 'line' and its current frame. */
const char * tsprite_get_line(TSprite * sprite, int line);

#endif