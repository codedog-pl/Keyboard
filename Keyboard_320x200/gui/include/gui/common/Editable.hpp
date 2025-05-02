/**
 * @file        Editable.hpp
 * @author      Adam Łyskawa
 *
 * @brief       An editable text control abstraction wrapper. Header only class.
 *
 * @copyright   (c)2024 CodeDog, All rights reserved.
 */

#pragma once

#include "gui/common/FrontendApplication.hpp"
#include "touchgfx/containers/Container.hpp"
#include "touchgfx/widgets/Box.hpp"
#include "touchgfx/containers/buttons/Buttons.hpp"
#include "touchgfx/widgets/TextAreaWithWildcard.hpp"

/// @brief An editable text control abstraction wrapper.
class Editable
{

public:

    /// @brief A `Flex Button` with a text label mapped to a wildcard buffer.
    using Btn = WildcardTextButtonStyle<BoxWithBorderButtonStyle<ClickButtonTrigger>>;

    /// @brief A `Text Area` with 1 wildcard buffer.
    using Box = TextAreaWithOneWildcard;

    /// @brief Creates an editable control from a drawable element with a wildcard text buffer.
    /// @param drawable Drawable element reference.
    /// @param buffer Unicode text buffer address.
    /// @param size Text buffer size.
    Editable(Drawable& drawable, Unicode::UnicodeChar* buffer, size_t size)
        : m_drawable(drawable), m_buffer(buffer), m_size(size) { }

    /// @returns The base drawable element's reference.
    Drawable& drawable() { return m_drawable; }

    /// @returns The Unicode text buffer address.
    Unicode::UnicodeChar* buffer() const { return m_buffer; }

    /// @brief Clears the Unicode text buffer.
    void clear() { m_buffer[0] = 0; }

    /// @returns The text buffer size.
    size_t size() const { return m_size; }

    /// @brief Limits the editable size.
    /// @param size A size in characters that can only be lower from the initial size.
    void limitSize(size_t size) { if (size < m_size) m_size = size; }

    /// @brief Unconditionally resets the buffer size for the editable. User is responsible for the range checking.
    /// @param size New buffer size to set. Be sure not to exceed the actual size of the buffer!
    void resetSize(size_t size) { m_size = size; }

    /// @brief Marks the base element's rectangle as to redraw with the next frame.
    void invalidate() const { m_drawable.invalidate(); }

    /// @brief Gets the text from the other editable element and copies it to this element, this element gets invalidated.
    /// @param other Other editable element reference.
    void getText(Editable& other) const
    {
        Unicode::strncpy(m_buffer, other.buffer(), static_cast<uint16_t>(m_size));
        invalidate();
    }

    /// @brief Sets the text of the other editable element with this element's text, other element gets invalidated.
    /// @param other Other editable element reference.
    void setText(Editable& other) const
    {
        Unicode::strncpy(other.buffer(), m_buffer, static_cast<uint16_t>(other.size()));
        other.invalidate();
    }

    /// @brief Sets this element's buffer with the UTF-8 text buffer content.
    /// @param buffer UTF-8 buffer pointer.
    /// @param size UTF-8 buffer size.
    void fromUTF8(void* buffer, size_t size) const
    {
        Unicode::fromUTF8(reinterpret_cast<uint8_t*>(buffer), m_buffer, static_cast<uint16_t>(size));
    }

    /// @brief Fills the given UTF-8 text buffer with this element's text.
    /// @param buffer UTF-8 buffer pointer.
    /// @param size UTF-8 buffer size.
    void toUTF8(void* buffer, size_t size) const
    {
        Unicode::toUTF8(m_buffer, reinterpret_cast<uint8_t*>(buffer), static_cast<uint16_t>(size));
    }

    /// @brief Gets the wildcard Unicode text buffer for a Flex Button with text.
    /// @param btn Flex Button reference.
    /// @return Unicode text buffer pointer.
    inline static Unicode::UnicodeChar* getUnicodeBuffer(Btn& btn)
    {
        auto t = reinterpret_cast<TextAreaWithOneWildcard*>(btn.getFirstChild()->getNextSibling());
        return const_cast<Unicode::UnicodeChar*>(t->getWildcard1());
    }

    /// @brief Gets the wildcard Unicode text buffer for a Text Area with 1 wildcard.
    /// @param btn Text Area reference.
    /// @return Unicode text buffer pointer.
    inline static Unicode::UnicodeChar* getUnicodeBuffer(Box& box)
    {
        return const_cast<Unicode::UnicodeChar*>(box.getWildcard1());
    }

    /// @brief The reference to the element that should be redrawn when its text changes.
    Drawable& m_drawable;

    /// @brief The pointer to the target element's Unicode text buffer.
    Unicode::UnicodeChar* m_buffer;

    /// @brief The size of the target element's Unicode text buffer.
    size_t m_size;

};
