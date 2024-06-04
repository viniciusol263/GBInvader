#include "GBInvader.h"
#include "MainLogic/MainLogic.h"

const void RunGame(void)
{
    InitLogic();
    while(1)
    {
        LoopLogic();
        vsync();   
    }
}