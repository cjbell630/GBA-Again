//
// obj_demo.c
// testing various sprite related things
//
// (20031003 - 20060924, Cearn)

#include <string.h>
#include <stdio.h>
#include "../include/toolbox.h"
#include "../images/metr.h"
#include "../include/debug.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *) obj_buffer;


// testing a few sprite things
// D-pad: move 
// SELECT: switch palette
// START: toggle mapping mode
// A: horizontal flip
// B: vertical flip
// L & R shift starting tile
void obj_test() {
    int x = 96, y = 32;
    u32 tid = 0, pb = 0;        // tile id, pal-bank

    OBJ_ATTR *metr = &obj_buffer[0];
    obj_set_attr(metr,
                 ATTR0_SQUARE,                // Square, regular sprite
                 ATTR1_SIZE_64,                    // 64x64p,
                 ATTR2_PALBANK(pb) | tid);        // palbank 0, tile 0

    // position sprite (redundant here; the _real_ position
    // is set further down
    obj_set_pos(metr, x, y);

    int velocity = 0;
    int acceleration = 0;
    const int GRAVITY = 1; //positive bc up is down
    const int GROUND_Y = 32;
    const int JUMP_INIT_ACCEL = -10; //negative because up is down

    vbaprint("hello world");

    while (1) {
        vid_vsync();
        key_poll();

        // move left/right
        x += 2 * key_tri_horz();

        // move up/down
        y += velocity;
        if (y > GROUND_Y) { // if object is at or below ground level
            //TODO: stupid code bc allows the object to fall slightly below the "floor" before resetting
            y = GROUND_Y; //move it back up
            velocity = 0;
            acceleration = 0; //stop movement
        } else if (y != GROUND_Y) { // if object is in the air
            //apply gravity
            acceleration += GRAVITY;
        }

        //accelerate
        velocity += acceleration;

        // increment/decrement starting tile with R/L
        tid += bit_tribool(key_hit(-1), KI_R, KI_L);

        // flip or jump
        if (key_hit(KEY_A))    // horizontally
            // metr->attr1 ^= ATTR1_HFLIP;
            if (y == GROUND_Y) {
                acceleration = JUMP_INIT_ACCEL;
                velocity += acceleration;
            }
        if (key_hit(KEY_B))    // vertically
            metr->attr1 ^= ATTR1_VFLIP;

        // make it glow (via palette swapping)
        pb = key_is_down(KEY_SELECT) ? 1 : 0;

        // toggle mapping mode
        if (key_hit(KEY_START))
            REG_DISPCNT ^= DCNT_OBJ_1D;

        // Hey look, it's one of them build macros!
        metr->attr2 = ATTR2_BUILD(tid, pb, 0);
        obj_set_pos(metr, x, y);

        oam_copy(oam_mem, obj_buffer, 1);    // only need to update one
    }
}

int main() {
    // Places the glyphs of a 4bpp boxed metroid sprite
    //   into LOW obj memory (cbb == 4)
    memcpy(&tile_mem[4][0], metrTiles, metrTilesLen);
    memcpy(pal_obj_mem, metrPal, metrPalLen);

    // inits the oam with 128 objects
    oam_init(obj_buffer, 128);
    REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D; //sets display info

    obj_test();

    while (1);

    return 0;
}
