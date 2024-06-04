#include "Joycon.h"

joycon_state joycon_keys[5] = 
{
    {J_LEFT,0},
    {J_RIGHT,0},
    {J_UP,0},
    {J_DOWN,0},
    {J_A,0}
};

const void UpdateJoyconState(void)
{
    uint8_t current_joypad_state = joypad();

    for(int index = 0; index < sizeof(joycon_keys); ++index)
    {
        if(current_joypad_state & joycon_keys[index].key) joycon_keys[index].state = 1; 
        else joycon_keys[index].state = 0;
    }
}

joycon_state* GetJoyconKeys(void)
{
    return joycon_keys;
}