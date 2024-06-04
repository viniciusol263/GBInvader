#include "MainLogic.h"
#include "Objects/ObjectsFunc.h"

const void InitLogic(void)
{
    InitGraphics();
    InitSound();

    objectStruct* player = createObject(OS_PLAYER, MAX_SCREEN_WIDTH/2, MAX_SCREEN_HEIGTH/2, &PlayerInitFunc, &PlayerLoopFunc);
}

const void LoopLogic(void)
{
    scroll_bkg(0,-1);
    UpdateJoyconState();
    ExecuteLogicFunctionAllObjects();
    KillObjectWatcher();
}