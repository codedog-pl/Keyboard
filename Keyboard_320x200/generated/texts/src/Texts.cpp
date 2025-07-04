/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringLTR(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

// Default TypedTextDatabase
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x4b, 0x65, 0x79, 0x62, 0x6f, 0x61, 0x72, 0x64, 0x20, 0x28, 0x63, 0x29, 0x32, 0x30, 0x32, 0x35, 0x20, 0x62, 0x79, 0x20, 0x43, 0x6f, 0x64, 0x65, 0x44, 0x6f, 0x67, 0x0, // @0 "Keyboard (c)2025 by CodeDog"
    0x5b, 0x4e, 0x65, 0x77, 0x20, 0x54, 0x65, 0x78, 0x74, 0x5d, 0x0, // @28 "[New Text]"
    0x2, 0x0, // @39 "<>"
    0x45, 0x2d, 0x6d, 0x61, 0x69, 0x6c, 0x0, // @41 "E-mail"
    0x4e, 0x61, 0x6d, 0x65, 0x0, // @48 "Name"
    0x45, 0x73, 0x63, 0x0, // @53 "Esc"
    0x23, 0x0, // @57 "#"
    0x28, 0x0, // @59 "("
    0x29, 0x0, // @61 ")"
    0x2c, 0x0, // @63 ","
    0x2d, 0x0, // @65 "-"
    0x2e, 0x0, // @67 "."
    0x30, 0x0, // @69 "0"
    0x31, 0x0, // @71 "1"
    0x32, 0x0, // @73 "2"
    0x33, 0x0, // @75 "3"
    0x34, 0x0, // @77 "4"
    0x35, 0x0, // @79 "5"
    0x36, 0x0, // @81 "6"
    0x37, 0x0, // @83 "7"
    0x38, 0x0, // @85 "8"
    0x39, 0x0, // @87 "9"
    0x40, 0x0, // @89 "@"
    0x61, 0x0, // @91 "a"
    0x62, 0x0, // @93 "b"
    0x64, 0x0, // @95 "d"
    0x66, 0x0, // @97 "f"
    0x68, 0x0, // @99 "h"
    0x69, 0x0, // @101 "i"
    0x6a, 0x0, // @103 "j"
    0x6b, 0x0, // @105 "k"
    0x6d, 0x0, // @107 "m"
    0x6e, 0x0, // @109 "n"
    0x6f, 0x0, // @111 "o"
    0x70, 0x0, // @113 "p"
    0x71, 0x0, // @115 "q"
    0x72, 0x0, // @117 "r"
    0x73, 0x0, // @119 "s"
    0x74, 0x0, // @121 "t"
    0x75, 0x0, // @123 "u"
    0x76, 0x0, // @125 "v"
    0x77, 0x0, // @127 "w"
    0x78, 0x0, // @129 "x"
    0x79, 0x0, // @131 "y"
    0x7a, 0x0, // @133 "z"
    0x2190, 0x0, // @135 "?"
    0x21b5, 0x0, // @137 "?"
    0x21e7, 0x0 // @139 "?"
};

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const uint32_t indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

// Array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

// Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}
