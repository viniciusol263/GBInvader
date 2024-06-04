#ifndef JOYCON_H_
#define JOYCON_H_

#include <gb/gb.h>

enum joycon_keys_enum 
{
    LEFT = 0,
    RIGHT,
    UP,
    DOWN,
    A
};

typedef struct 
{
    uint8_t key;
    uint8_t state;
} joycon_state;

const void UpdateJoyconState(void);
joycon_state* GetJoyconKeys(void);

#endif