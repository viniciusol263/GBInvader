#include <stdlib.h>
#include <stdio.h>

#include "ObjectsFunc.h"
#include "Graphics/Graphics.h"


objectStruct* g_objs;
int g_objsSize;

void InitObjects(void)
{
    g_objsSize = 0;
    g_objs = calloc(1, sizeof(objectStruct));
}

objectStruct* createObject(int spriteIndex, int x, int y, InitObjectFunc initFunc, LogicObjectFunc loopFunc)
{
    objState objSt = {0};

    objSt.spriteIndex = spriteIndex;
    objSt.velocityX = 0;
    objSt.velocityY = 0;
    objSt.action = 0;
    objSt.debounce = 0;
    objSt.kill = 0;

    spritePosition spritePos = {0};
    spritePos.x = x;
    spritePos.y = y;

    hitBox hitBox = {0};

    objAnimation objAnim = {0};
    objAnim.animCounter = 0;
    objAnim.animTileIndex = 0;

    objectStruct obj = {0};
    obj.index = ++g_objsSize - 1;
    obj.m_hitBox = hitBox;
    obj.m_objPos = spritePos;
    obj.m_objState = objSt;
    obj.m_objAnim = objAnim;
    obj.m_initFunc = initFunc;
    obj.m_logicFunc = loopFunc;

    g_objs = realloc(g_objs, g_objsSize);
    g_objs[g_objsSize - 1] = obj;
    obj.m_initFunc();

    return &obj;
}

spritePosition getSpritePosition(uint8_t nb)
{
    OAM_item_t * itm = &shadow_OAM[nb];
    if(itm->tile == 0)
    {
        spritePosition empty;
        return empty;
    } 
       
    uint8_t is_hidden = 0;

    if(itm->x >= MAX_SCREEN_WIDTH || itm->x <= 0) is_hidden = 1;
    if(itm->y >= MAX_SCREEN_HEIGTH || itm->y <= 0) is_hidden = 1;

    spritePosition pos = {
        .x = itm->x,
        .y = itm->y,
        .hidden = is_hidden
    };
    return pos;
}

objectStruct* getObject(int index)
{
    return &g_objs[index];
}

void ExecuteLogicFunctionAllObjects(void)
{
    for(int index = 0; index < g_objsSize; ++index)
    {
        g_objs[index].m_logicFunc();
    }
}

void KillObjectWatcher(void)
{
    for(int index = g_objsSize; index >= 0; --index)
    {
        if(g_objs[index].m_objState.kill == 1) 
        {
            objectStruct tmpObj = {0};
            move_sprite(g_objs[index].m_objState.spriteIndex, 0, 0);
            g_objs[index] = tmpObj;
            g_objsSize--;
        }
    }
}