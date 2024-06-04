#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <gb/gb.h>

#include "SpritePlayerShip.h"
#include "SpritePlayerShipProjectile.h"
#include "BkgNormalTile.h"
#include "BkgNormalData.h"

#define MAX_SCREEN_WIDTH 164
#define MAX_SCREEN_HEIGTH 154
#define PLAYER_ANIM_SPEED 1000 // animation frametime in ms

const void InitGraphics(void);

#endif