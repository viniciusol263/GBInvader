#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <gb/gb.h>

#include "sprites/SpritePlayerShip.h"
#include "sprites/SpritePlayerShipProjectile.h"
#include "sprites/BkgNormalTile.h"
#include "sprites/BkgNormalData.h"

#define PLAYER_ANIM_SPEED 1000 // animation frametime in ms

typedef struct 
{
    uint8_t key;
    uint8_t state;
} joycon_state;

typedef struct 
{
    uint8_t x;
    uint8_t y;
    uint8_t hidden;
} sprite_position;


enum joycon_keys_enum 
{
    LEFT = 0,
    RIGHT,
    UP,
    DOWN,
    A
};

joycon_state joycon_keys[5] = 
{
    {J_LEFT,0},
    {J_RIGHT,0},
    {J_UP,0},
    {J_DOWN,0},
    {J_A,0}
};

void update_joycon_state();
sprite_position get_sprite_pos(uint8_t nb);
void play_sound();

void main()
{
    int current_sprite_anim = 0;
    int current_sprite_anim_cycle = 0;
    // uint8_t* bkg_tiles = (uint8_t*)malloc(sizeof(uint8_t)*16);
    // memset(bkg_tiles, 0x00, 16);
    // uint8_t* bkg_data = (uint8_t*)malloc(sizeof(uint8_t)*32*32);
    // memset(bkg_data, 0, 32*32);

    int player_vel_x = 0;
    int player_vel_y = 0;
    uint8_t player_action = 0;
    uint8_t player_bullet_debounce = 0;

    int player_projectile_vel_x = 0;
    int player_projectile_vel_y = 0;

    set_sprite_data(0x1A,3,PlayerShip);
    set_sprite_tile(0,0x1A);

    set_sprite_data(0x1D,1,PlayerShipProjectile);
    set_sprite_tile(1,0x1D);

    move_sprite(0,88, 78);

    set_bkg_data(0, BackgroundTile_Tiles, BackgroundTile);
    set_bkg_tiles(0, 0, 20, 36, BkgNormal);
    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    NR52_REG = 0x80; // Turns on sound
    NR50_REG = 0x77; // Sets the volume to max 0x77
    NR51_REG = 0xFF; // Use all channels

    while(1)
    {
        update_joycon_state();
        
        
        player_vel_x = (5) * (joycon_keys[RIGHT].state - joycon_keys[LEFT].state);
        player_vel_y = (5) * (joycon_keys[DOWN].state - joycon_keys[UP].state);
        player_action = joycon_keys[A].state;

        scroll_sprite(0, player_vel_x, player_vel_y);  
        scroll_bkg(0,-1);

        if(current_sprite_anim_cycle++ == PLAYER_ANIM_SPEED/16)
        {
            current_sprite_anim_cycle = 0;
            current_sprite_anim = ((current_sprite_anim + 1) % PlayerShip_Tiles);
            set_sprite_tile(0, current_sprite_anim + 0x1A);
        }
        
        if(!player_bullet_debounce && player_action)
        {
            player_bullet_debounce = 1;
            move_sprite(1,get_sprite_pos(0).x, get_sprite_pos(0).y - 8);
            play_sound();
        }

        if(!get_sprite_pos(1).hidden)
        {
            scroll_sprite(1, 0, -7);
        }
        else
        {
            player_bullet_debounce = 0;
        }

        wait_vbl_done();
    
    }
}

void update_joycon_state()
{     
    uint8_t current_joypad_state = joypad();

    for(int index = 0; index < sizeof(joycon_keys); ++index)
    {
        if(current_joypad_state & joycon_keys[index].key) joycon_keys[index].state = 1; 
        else joycon_keys[index].state = 0;
    }
}

sprite_position get_sprite_pos(uint8_t nb)
{
    OAM_item_t * itm = &shadow_OAM[nb];
    if(itm->tile == 0)
    {
        sprite_position empty;
        return empty;
    } 
       
    uint8_t is_hidden = 0;

    if(itm->x >= 164 || itm->x <= 0) is_hidden = 1;
    if(itm->y >= 154 || itm->y <= 0) is_hidden = 1;

    sprite_position pos = {
        .x = itm->x,
        .y = itm->y,
        .hidden = is_hidden
    };
    return pos;
}

void play_sound()
{
    NR10_REG = 0x00;
    NR11_REG = 0x81;
    NR12_REG = 0x43;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}