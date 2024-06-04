#ifndef OBJECTS_H_
#define OBJECTS_H_

#include <gb/gb.h>

typedef struct 
{
    uint8_t x;
    uint8_t y;
    uint8_t hidden;
} spritePosition;

typedef struct 
{
    int x;
    int width;
    int y;
    int heigth;
} hitBox;

typedef struct 
{
    int spriteIndex;
    int velocityX;
    int velocityY;
    int action;
    int debounce;
    int kill;
} objState;

typedef struct 
{
    int animCounter;
    int animTileIndex;

} objAnimation;

enum ObjectSprite 
{
    OS_PLAYER = 0,
    OS_PLAYER_PROJECTILE
};

typedef void (*InitObjectFunc)(void);
typedef void (*LogicObjectFunc)(void);

typedef struct
{
    int index;
    objState m_objState;
    spritePosition m_objPos;
    hitBox m_hitBox;
    objAnimation m_objAnim;
    InitObjectFunc m_initFunc;
    LogicObjectFunc m_logicFunc;
} objectStruct;

objectStruct* createObject(int spriteIndex, int x, int y, InitObjectFunc initFunc, LogicObjectFunc loopFunc);
spritePosition getSpritePosition(uint8_t nb);
objectStruct* getObject(int index);
void ExecuteLogicFunctionAllObjects(void);

#endif