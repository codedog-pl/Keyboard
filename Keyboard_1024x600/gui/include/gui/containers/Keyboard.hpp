/**
 * @file        Keyboard.hpp
 * @author      Adam Łyskawa
 *
 * @brief       A modern, customizable and scaleable on-screen keyboard control. Header file.
 *
 * @copyright   (c)2024 CodeDog, All rights reserved.
 */

#pragma once

#include "gui_generated/containers/KeyboardBase.hpp"
#include "gui/common/Editable.hpp"
#include "gui/common/KeyboardColors.hpp"
#include "gui/common/KeyboardLayout.hpp"
#include "gui/common/KeyboardKey.hpp"

using namespace keyboard;

/// @brief A modern, customizable and scaleable on-screen keyboard control.
class Keyboard final : public KeyboardBase, KeyboardLayout
{

public:

    using EventType = ClickEvent::ClickEventType;

    static constexpr uint16_t margin = 0;       // Widget margin in pixels.
    static constexpr uint16_t padding = 4;      // Widget padding in pixels.
    static constexpr uint16_t spacing = 0;      // Key spacing in pixels.
    static constexpr double blinkTime = 0.25;   // Blink time in seconds.
    static constexpr double bsHoldTime = 1.00;  // Backspace hold time in seconds to clear entire line.
    static constexpr double FPS = 60.0;         // Frames per second constant.

    /// @brief Constructs the keyboard element and scales the layout.
    Keyboard();

    /// @brief Places the element on the screen properly after the container is placed anywhere.
    /// @param size Buffer size (default 40).
    void initialize() override;

    /// @brief Shows the keyboard for the specified editable target and copies its text into the control.
    /// @param target Editable element reference.
    void edit(Editable& target);

    /// @brief Cancels changes, hides the keyboard.
    void cancel();

    /// @brief Applies changes, hides the keyboard.
    void apply();

    /// @brief Receives tick events from the application.
    void handleTickEvent() override;

    /// @returns True if the keyboard currently targets the `Editable`.
    inline bool targets(Editable& target) { return m_target == &target; }

private:

    /// @brief Handles cancellation of a key event.
    /// @param keyCode The code of the key that generated the event.
    /// @param e Event type.
    /// @returns 1: The event is already handled, exit. 0: Event is ready to be finally handled.
    bool handleCancellation(uint8_t keyCode, EventType e);

    /// @brief Handles mapped keys.
    /// @param sender Mapped key reference.
    /// @param event Click event.
    void handleMappedKey(const Key::Mapped& sender, const ClickEvent& event);

    /// @brief Handles static keys.
    /// @param sender Static key reference.
    /// @param event Click event.
    void handleStaticKey(const Key::Static& sender, const ClickEvent& event);

    /// @brief Handles blank keys.
    /// @param sender Blank key reference.
    /// @param event Click event.
    void handleBlankKey(const Key::Blank& sender, const ClickEvent& event);

    /// @brief Handles toggle keys.
    /// @param sender Toggle key reference.
    /// @param event Click event.
    void handleToggleKey(const Key::Toggle& sender, const ClickEvent& event);

    /// @brief Handles BACKSPACE key events.
    /// @param e Event type.
    void handleBackspace(EventType e);

    /// @brief Handles SHIFT key events.
    /// @param source Shift key that caused the event.
    /// @param target Shift key affected.
    /// @param e Event type.
    void handleShift(const Key& source, const Key& target, const EventType e);

    /// @brief Handles the ESCAPE key released event.
    void handleEscape();

    /// @brief Types a SPACE character on space bar released.
    void handleSpace();

    /// @brief Handles the ENTER key released event.
    void handleEnter();

    /// @brief Applies the key labels according to the caps lock state.
    void applyKeyLabels();

    /// @brief Gets the internal code of the key (1 based key number in the keys container).
    /// @param key Key reference.
    /// @return Key code. 0 if the key is not found in the keys container.
    uint8_t getKeyCode(const Drawable& key);

    /// @brief Types a specified character at the current caret position.
    /// @param value Character to type.
    void typeCharacter(Unicode::UnicodeChar character);

    /// @brief Removes the last character from the text.
    void removeCharacter();

    /// @brief Removes all characters from the text.
    void removeAll();

    /// @brief Blinks the caret.
    void caretBlink();

    /// @brief Sets / updates the caret position.
    void caretUpdatePosition();

    Key m_keys[50];                 // Key definitions.
    KeyboardColors m_colorScheme;   // Color scheme.
    Callback<Keyboard, const Key::Mapped&, const ClickEvent&> m_mappedKeyCallback;  // Mapped key callback.
    Callback<Keyboard, const Key::Static&, const ClickEvent&> m_staticKeyCallback;  // Static key callback.
    Callback<Keyboard, const Key::Blank&, const ClickEvent&> m_blankKeyCallback;    // Blank key callback.
    Callback<Keyboard, const Key::Toggle&, const ClickEvent&> m_toggleKeyCallback;  // Toggle key callback.
    uint8_t m_cancelKey;    // Release event from this key will be canceled.
    const Font* m_font;     // Keyboard font pointer.
    uint16_t m_fontHeight;  // Keyboard font height (as the text line height).
    uint16_t m_textOffset;  // Key text vertical offset to center the text vertically.
    uint16_t m_caretX;      // Caret position in characters from beginning of the edited string.
    uint16_t m_blFrames;    // Blink frames left to toggle caret blink state.
    uint16_t m_bsFrames;    // Backspace frames left to activate line clear.
    bool m_isCapsLock;      // True if the keyboard is switched to caps lock mode.
    Editable m_input;       // Internal text line control.
    Editable* m_target;     // Target element to update when the editing is done.

};
