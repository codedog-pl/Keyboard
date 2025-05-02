/**
 * @file        KeyboardColors.hpp
 * @author      Adam Łyskawa
 *
 * @brief       Contains on-screen keyboard color scheme. Header only class.
 *
 * @copyright   (c)2024 CodeDog, All rights reserved.
 */

#pragma once

#include "touchgfx/hal/Types.hpp"

using namespace touchgfx;

/// @brief Contains on-screen keyboard color scheme.
struct KeyboardColors
{
    colortype frameBackground         =   0xE7E7E7;
    colortype textBackground          =   0xFFFFFF;
    colortype textColor               =   0x444444;
    colortype keyBackground           =   0xFFFFFF;
    colortype keySpecialBackground    =   0xF0F0F0;
    colortype keyEdge                 =   0xE0E0E0;
    colortype keyPressedBackground    =   0xE0FFFF;
    colortype keyPressedEdge          =   0xD0EEEE;
    colortype keyLabel                =   0x444444;
    colortype accent                  =   0x0099CC;
};
