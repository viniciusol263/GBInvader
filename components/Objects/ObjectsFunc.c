#include <gb/isr.h>
#include "ObjectsFunc.h"

void PlayerInitFunc(void)
{
    objectStruct* player = getObject(OS_PLAYER);

    move_sprite(player->m_objState.spriteIndex, player->m_objPos.x, player->m_objPos.y); 
}

void PlayerLoopFunc(void)
{
    objectStruct* obj = getObject(OS_PLAYER);
    objectStruct* projObj = getObject(OS_PLAYER_PROJECTILE);
    joycon_state* joycons = GetJoyconKeys();

    obj->m_objState.velocityX = (5) * (joycons[RIGHT].state - joycons[LEFT].state);
    obj->m_objState.velocityY = (5) * (joycons[DOWN].state - joycons[UP].state);
    obj->m_objState.action = joycons[A].state;

    obj->m_objPos.x += obj->m_objState.velocityX;
    obj->m_objPos.y += obj->m_objState.velocityY;
    scroll_sprite(obj->m_objState.spriteIndex, obj->m_objState.velocityX, obj->m_objState.velocityY);  

    if(obj->m_objAnim.animCounter++ == PLAYER_ANIM_SPEED/16)
    {
        obj->m_objAnim.animCounter = 0;
        obj->m_objAnim.animTileIndex = ((obj->m_objAnim.animTileIndex + 1) % PlayerShip_Tiles);
        set_sprite_tile(obj->m_objState.spriteIndex, obj->m_objAnim.animTileIndex + 0x1A);
    }
    
    if(!obj->m_objState.debounce && obj->m_objState.action)
    {
        obj->m_objState.debounce = 1;
        createObject(OS_PLAYER_PROJECTILE, obj->m_objPos.x, obj->m_objPos.y, &PlayerProjectileInitFunc, &PlayerProjectileLoopFunc);

        move_sprite(projObj->m_objState.spriteIndex, obj->m_objPos.x, obj->m_objPos.y - 8);
        PlaySound();
    }
}

void PlayerProjectileInitFunc(void)
{
    objectStruct* projectile = getObject(OS_PLAYER_PROJECTILE);
    projectile->m_objState.velocityX = 0;
    projectile->m_objState.velocityY = -7;
    move_sprite(OS_PLAYER_PROJECTILE, projectile->m_objPos.x, projectile->m_objPos.y - 8); 
}

void PlayerProjectileLoopFunc(void)
{
    objectStruct* player = getObject(OS_PLAYER);
    objectStruct* projectile = getObject(OS_PLAYER_PROJECTILE);

    projectile->m_objPos.x += projectile->m_objState.velocityX;
    projectile->m_objPos.y += projectile->m_objState.velocityY;
    scroll_sprite(OS_PLAYER_PROJECTILE, projectile->m_objState.velocityX, projectile->m_objState.velocityY);
    if(projectile->m_objPos.x >= MAX_SCREEN_WIDTH || projectile->m_objPos.x <= 0) 
    {
        player->m_objState.debounce = 0;
        projectile->m_objState.kill = 1;
    }
    if(projectile->m_objPos.y >= MAX_SCREEN_HEIGTH || projectile->m_objPos.y <= 0)
    {
        player->m_objState.debounce = 0;
        projectile->m_objState.kill = 1;
    } 
        
}
