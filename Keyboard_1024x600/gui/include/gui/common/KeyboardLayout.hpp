/**
 * @file        KeyboardLayout.hpp
 * @author      Adam Łyskawa
 *
 * @brief       Contains on-screen keyboard character layout. Header only class.
 *
 * @copyright   (c)2024 CodeDog, All rights reserved.
 */

#pragma once

#include "touchgfx/Unicode.hpp"

using namespace touchgfx;

/// @brief Contains on-screen keyboard character layout.
class KeyboardLayout
{

public:

    /// @brief Defines the character map for key codes from 0 to 49.
    static constexpr Unicode::UnicodeChar layout[2][50] =
    {
        { // REGULAR
            0,
            '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0,
            'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '-',
            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '(', ')', 0,
            'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 0, 0, 0,
            '@', '/', 0

        },
        { // CAPS LOCK
            0,
            '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0,
            'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '+',
            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '[', ']', 0,
            'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', 0, 0, 0,
            '#', '"', 0
        }
    };

};
