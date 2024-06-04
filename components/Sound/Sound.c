#include "Sound.h"

const void InitSound(void)
{
    NR52_REG = 0x80; // Turns on sound
    NR50_REG = 0x77; // Sets the volume to max 0x77
    NR51_REG = 0xFF; // Use all channels
}
const void PlaySound(void)
{
    NR10_REG = 0x00;
    NR11_REG = 0x81;
    NR12_REG = 0x43;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}