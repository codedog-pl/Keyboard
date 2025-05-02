/**
 * @file        KeyboardKey.hpp
 * @author      Adam Łyskawa
 *
 * @brief       Contains on-screen keyboard color scheme. Header only class.
 *
 * @copyright   (c)2024 CodeDog, All rights reserved.
 */

#pragma once

#include "gui/common/FrontendApplication.hpp"
#include "touchgfx/containers/Container.hpp"
#include "touchgfx/widgets/Box.hpp"
#include "touchgfx/containers/buttons/Buttons.hpp"
#include "touchgfx/mixins/ClickListener.hpp"
#include "touchgfx/widgets/TextAreaWithWildcard.hpp"
#include "gui/common/Editable.hpp"
#include "gui/common/KeyboardColors.hpp"

namespace keyboard
{

/// @brief Defines a on-screen keyboard key.
struct Key
{

    /// @brief A key that can be mapped.
    using Mapped = WildcardTextButtonStyle<BoxWithBorderButtonStyle<ClickButtonTrigger>>;

    /// @brief A key with the static text.
    using Static = TextButtonStyle<BoxWithBorderButtonStyle<ClickButtonTrigger>>;

    /// @brief A blank key type.
    using Blank = BoxWithBorderButtonStyle<ClickButtonTrigger>;

    /// @brief A toggle key type.
    using Toggle = TextButtonStyle<BoxWithBorderButtonStyle<ToggleButtonTrigger>>;

    /// @brief Key type enumeration.
    enum class Type { Unset, Mapped, Static, Blank, Toggle };

    /// @brief Static initialization of the KeyboardKey class, defines keyboard geometry for the drawable scaling.
    /// @param textOffset Horizontal keyboard key text position in pixels.
    /// @param fontHeight Keyboard key text font height in pixels.
    static void initialize(uint16_t textOffset, uint16_t fontHeight)
    {
        m_textOffset= textOffset;
        m_fontHeight = fontHeight;
    }

    /// @brief Creates an empty key definition.
    Key() : m_drawable(), m_type(Type::Unset), m_keyCode(0) { }

    /// @brief Defines the key drawable, code and geometry.
    /// @param key A key that can be mapped drawable reference.
    /// @param keyCode Key code.
    /// @param colorScheme Color scheme reference for the key.
    /// @param x The horizontal distance from the left edge of the row.
    /// @param y The vertical distance from the top of the row.
    /// @param w Key width.
    /// @param h Key height.
    void define(Mapped& key, uint8_t keyCode, KeyboardColors& colorScheme, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
    {
        m_drawable = &key;
        m_type = Type::Mapped;
        m_keyCode = keyCode;
        setBounds(x, y, w, h);
        setColors(colorScheme);
    }

    /// @brief Defines the key drawable, code and geometry.
    /// @param key A key with the static text drawable reference.
    /// @param keyCode Key code.
    /// @param colorScheme Color scheme reference for the key.
    /// @param x The horizontal distance from the left edge of the row.
    /// @param y The vertical distance from the top of the row.
    /// @param w Key width.
    /// @param h Key height.
    void define(Static& key, uint8_t keyCode, KeyboardColors& colorScheme, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
    {
        m_drawable = &key;
        m_type = Type::Static;
        m_keyCode = keyCode;
        setBounds(x, y, w, h);
        setColors(colorScheme);
    }

    /// @brief Defines the key drawable, code and geometry.
    /// @param key A blank key drawable reference.
    /// @param keyCode Key code.
    /// @param colorScheme Color scheme reference for the key.
    /// @param x The horizontal distance from the left edge of the row.
    /// @param y The vertical distance from the top of the row.
    /// @param w Key width.
    /// @param h Key height.
    void define(Blank& key, uint8_t keyCode, KeyboardColors& colorScheme, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
    {
        m_drawable = &key;
        m_type = Type::Blank;
        m_keyCode = keyCode;
        setBounds(x, y, w, h);
        setColors(colorScheme);
    }

    /// @brief Defines the key drawable, code and geometry.
    /// @param key A toggle key drawable reference.
    /// @param keyCode Key code.
    /// @param colorScheme Color scheme reference for the key.
    /// @param x The horizontal distance from the left edge of the row.
    /// @param y The vertical distance from the top of the row.
    /// @param w Key width.
    /// @param h Key height.
    void define(Toggle& key, uint8_t keyCode, KeyboardColors& colorScheme, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
    {
        m_drawable = &key;
        m_type = Type::Toggle;
        m_keyCode = keyCode;
        setBounds(x, y, w, h);
        setColors(colorScheme);
    }

    /// @returns True if the key definition contains drawable.
    bool contains(const Drawable& d) const { return m_drawable == &d; }

    /// @returns The key type.
    Type type() const { return m_type; }

    /// @returns The key code.
    uint8_t code() const { return m_keyCode; }

    /// @returns True if the key is in the pressed state.
    bool getPressed() const
    {
        return (!m_drawable || m_type == Type::Unset)
            ? false
            : (*reinterpret_cast<AbstractButtonContainer*>(m_drawable)).getPressed();
    }

    /// @brief Sets the key pressed state.
    /// @param state True for pressed, false for not pressed.
    void setPressed(bool state) const
    {
        if (!m_drawable || m_type == Type::Unset) return;
        (*reinterpret_cast<AbstractButtonContainer*>(m_drawable)).setPressed(state);
        m_drawable->invalidate();
    }

    /// @brief Sets the key label.
    /// @param value The character to display on the key.
    void setLabel(Unicode::UnicodeChar value)
    {
        if (!m_drawable || m_type != Type::Mapped) return;
        Mapped& key = *reinterpret_cast<Mapped*>(m_drawable);
        Unicode::UnicodeChar* buffer = Editable::getUnicodeBuffer(key);
        if (!buffer) return;
        buffer[0] = value;
        key.invalidate();
    }

    /// @brief Sets the click action for a `Mapped` type key.
    /// @param callback Click action callback for a `Mapped` type key.
    void setClickAction(GenericCallback<const Mapped&, const ClickEvent&>& callback)
    {
        if (!m_drawable || m_type != Type::Mapped) return;
        ClickListener<Mapped>& key = *reinterpret_cast<ClickListener<Mapped>*>(m_drawable);
        key.setClickAction(callback);
    }

    /// @brief Sets the click action for a `Static` type key.
    /// @param callback Click action callback for a `Mapped` type key.
    void setClickAction(GenericCallback<const Static&, const ClickEvent&>& callback)
    {
        if (!m_drawable || m_type != Type::Static) return;
        ClickListener<Static>& key = *reinterpret_cast<ClickListener<Static>*>(m_drawable);
        key.setClickAction(callback);
    }

    /// @brief Sets the click action for a `Blank` type key.
    /// @param callback Click action callback for a `Blank` type key.
    void setClickAction(GenericCallback<const Blank&, const ClickEvent&>& callback)
    {
        if (!m_drawable || m_type != Type::Blank) return;
        ClickListener<Blank>& key = *reinterpret_cast<ClickListener<Blank>*>(m_drawable);
        key.setClickAction(callback);
    }

    /// @brief Sets the click action for a `Toggle` type key.
    /// @param callback Click action callback for a `Toggle` type key.
    void setClickAction(GenericCallback<const Toggle&, const ClickEvent&>& callback)
    {
        if (!m_drawable || m_type != Type::Toggle) return;
        ClickListener<Toggle>& key = *reinterpret_cast<ClickListener<Toggle>*>(m_drawable);
        key.setClickAction(callback);
    }

private:

    /// @brief Sets the key position, width and height.
    /// @param x The horizontal distance from the left edge of the row.
    /// @param y The vertical distance from the top of the row.
    /// @param w Key width.
    /// @param h Key height.
    void setBounds(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
    {
        if (!m_drawable || m_type == Type::Unset) return;
        m_drawable->setPosition(x, y, w, h);
        switch (m_type)
        {
        case Type::Mapped:
            reinterpret_cast<Mapped*>(m_drawable)->setBoxWithBorderPosition(0, 0, w, h);
            reinterpret_cast<Mapped*>(m_drawable)->setWildcardTextPosition(0, m_textOffset, w, m_fontHeight);
            break;
        case Type::Static:
            reinterpret_cast<Static*>(m_drawable)->setBoxWithBorderPosition(0, 0, w, h);
            reinterpret_cast<Static*>(m_drawable)->setTextPosition(0, m_textOffset, w, m_fontHeight);
            break;

        case Type::Blank:
            reinterpret_cast<Blank*>(m_drawable)->setBoxWithBorderPosition(0, 0, w, h);
            break;
        case Type::Toggle:
            reinterpret_cast<Toggle*>(m_drawable)->setBoxWithBorderPosition(0, 0, w, h);
            reinterpret_cast<Toggle*>(m_drawable)->setTextPosition(0, m_textOffset, w, m_fontHeight);
            break;
        default:
            break;
        }
    }

    void setColors(KeyboardColors& colors)
    {
        if (!m_drawable || m_type == Type::Unset) return;
        switch (m_type)
        {
        case Type::Mapped:
            reinterpret_cast<Mapped*>(m_drawable)->setBoxWithBorderColors(
                colors.keyBackground, colors.keyPressedBackground, colors.keyEdge, colors.keyPressedEdge
            );
            reinterpret_cast<Mapped*>(m_drawable)->setWildcardTextColors(
                colors.keyLabel, colors.keyLabel
            );
            break;
        case Type::Static:
            switch (m_keyCode)
            {
            case 49: // ENTER
                reinterpret_cast<Static*>(m_drawable)->setBoxWithBorderColors(
                    colors.accent, colors.keyPressedBackground, colors.keyEdge, colors.keyPressedEdge
                );
                break;
            default:
                reinterpret_cast<Static*>(m_drawable)->setBoxWithBorderColors(
                    colors.keySpecialBackground, colors.keyPressedBackground, colors.keyEdge, colors.keyPressedEdge
                );
                break;
            }
            reinterpret_cast<Static*>(m_drawable)->setTextColors(
                colors.keyLabel, colors.keyLabel
            );
            break;
        case Type::Blank:
            reinterpret_cast<Blank*>(m_drawable)->setBoxWithBorderColors(
                colors.keyBackground, colors.keyPressedBackground, colors.keyEdge, colors.keyPressedEdge
            );
            break;
        case Type::Toggle:
            reinterpret_cast<Toggle*>(m_drawable)->setBoxWithBorderColors(
                colors.keySpecialBackground, colors.accent, colors.keyEdge, colors.keyPressedEdge
            );
            reinterpret_cast<Toggle*>(m_drawable)->setTextColors(
                colors.keyLabel, colors.keyLabel
            );
            break;
        default:
            break;
        }
    }

    /// @brief Contains drawable reference.
    Drawable* m_drawable;

    /// @brief Contains information about specific key type.
    Type m_type;

    /// @brief Contains the key code (the 1 based number of the key within the keys container).
    uint8_t m_keyCode;

    /// @brief In order to scale the keys properly, the horizontal position of the key text must be set.
    static uint16_t m_textOffset;

    /// @brief In order to scale the keys properly, the key text font height must be set.
    static uint16_t m_fontHeight;

};

}
