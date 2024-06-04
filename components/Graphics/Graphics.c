#include "Graphics.h"

const void InitGraphics(void)
{
    set_sprite_data(0x1A,3,PlayerShip);
    set_sprite_tile(0,0x1A);

    set_sprite_data(0x1D,1,PlayerShipProjectile);
    set_sprite_tile(1,0x1D);

    set_bkg_data(0, BackgroundTile_Tiles, BackgroundTile);
    set_bkg_tiles(0, 0, 20, 36, BkgNormal);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
}