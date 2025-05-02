/**
 * @file        Keyboard.cpp
 * @author      Adam Łyskawa
 *
 * @brief       A modern, customizable and scaleable on-screen keyboard control. Implementation.
 *
 * @copyright   (c)2024 CodeDog, All rights reserved.
 */

#include "gui/containers/Keyboard.hpp"
#include "texts/TextKeysAndLanguages.hpp"

Keyboard::Keyboard()
:   m_keys(), m_colorScheme(),
    m_mappedKeyCallback(this, &Keyboard::handleMappedKey),
    m_staticKeyCallback(this, &Keyboard::handleStaticKey),
    m_blankKeyCallback(this, &Keyboard::handleBlankKey),
    m_toggleKeyCallback(this, &Keyboard::handleToggleKey),
    m_cancelKey(0),
    m_font(), m_fontHeight(20), m_textOffset(5), // For the default "Segoe UI" 16 font, 320x200.
    m_caretX(0), m_blFrames(static_cast<uint16_t>(blinkTime * FPS)), m_bsFrames(0),
    m_isCapsLock(false),
    m_input(Editable(text, textBuffer, TEXT_SIZE)), m_target()
{
    // Calculate font geometry:
    const TypedText measure(T_KEY41); // "m" key.
    m_font = measure.getFont();
    m_fontHeight = m_font->getHeight();
    // Calculate widget geometry:
    const uint16_t w = HAL::DISPLAY_WIDTH;      // Screen width.
    const uint16_t h = HAL::DISPLAY_HEIGHT;     // Screen height.
    const uint16_t ch = m_fontHeight;           // Caret height.
    const uint16_t tm = ch / 4;                 // Text margin.
    const uint16_t m = margin;                  // Margin.
    const uint16_t p = padding;                 // Padding.
    const uint16_t s = spacing;                 // Spacing.
    const uint16_t w0 = w - 2*m - 2*p;          // Internal width.
    const uint16_t h0 = h - 2*m - 2*p;          // Internal height.
    const uint16_t h1 = (h0 - 5*s) / 6;         // Row height.
    const uint16_t w1 = (w0 - 11*s) / 12;       // Small key width.
    m_textOffset = (h1 - m_fontHeight) / 2;     // Vertical offset for a key label.
    const uint16_t x1 = w1 / 2;                 // 2nd row horizontal offset.
    const uint16_t x2 = x1 + w1 / 2;            // 3rd row horizontal offset.
    const uint16_t x3 = x2 + w1 / 2;            // 4th row horizontal offset.
    const uint16_t w2 = w0 - 10*s - 10*w1;      // Backspace, Enter, Esc width.
    const uint16_t w3 = x3 - s;                 // Left shift width.
    const uint16_t w4 = w0 - (x3 + 9*s + 9*w1); // Right shift width.
    const uint16_t w5 = w0 - 4*s - 2*w1 - 2*w2; // Space bar width.
    const uint16_t y1 = 1*h1 + s;               // 1st row offset.
    const uint16_t y2 = 2*h1 + 2*s;             // 2nd row offset.
    const uint16_t y3 = 3*h1 + 3*s;             // 3rd row offset.
    const uint16_t y4 = 4*h1 + 4*s;             // 4th row offset.
    const uint16_t ew = w0 - 2 * tm;            // Edit line width.
    // Apply geometry to everything but keys:
    setWidthHeight(w, h);
    outerContainer.setPosition(m, m, w - 2*m, h - 2*m);
    background.setPosition(0, 0, w - 2*m, h - 2*m);
    background.setColor(m_colorScheme.frameBackground);
    innerContainer.setPosition(p, p, w0, h0);
    textBackground.setPosition(0, 0, w0, h1);
    textBackground.setColor(m_colorScheme.textBackground);
    textContainer.setPosition(tm, m_textOffset, ew, ch);
    text.setPosition(0, 0, ew, ch);
    text.setVisible(true);
    caret.setPosition(0, 0, 2, ch);
    caret.setColor(m_colorScheme.accent);
    keysContainer.setPosition(0, y1, w0, h0 - h1 - s);
    row1.setPosition(0, 0, w0, h1);
    row2.setPosition(0, y1, w0, h1);
    row3.setPosition(0, y2, w0, h1);
    row4.setPosition(0, y3, w0, h1);
    row5.setPosition(0, y4, w0, h1);
    // Define keys:
    Key::initialize(m_textOffset, m_fontHeight);
    m_keys[ 1].define(key01,  1, m_colorScheme, 0, 0, w1, h1);
    m_keys[ 2].define(key02,  2, m_colorScheme, 1*w1 + 1*s, 0, w1, h1);
    m_keys[ 3].define(key03,  3, m_colorScheme, 2*w1 + 2*s, 0, w1, h1);
    m_keys[ 4].define(key04,  4, m_colorScheme, 3*w1 + 3*s, 0, w1, h1);
    m_keys[ 5].define(key05,  5, m_colorScheme, 4*w1 + 4*s, 0, w1, h1);
    m_keys[ 6].define(key06,  6, m_colorScheme, 5*w1 + 5*s, 0, w1, h1);
    m_keys[ 7].define(key07,  7, m_colorScheme, 6*w1 + 6*s, 0, w1, h1);
    m_keys[ 8].define(key08,  8, m_colorScheme, 7*w1 + 7*s, 0, w1, h1);
    m_keys[ 9].define(key09,  9, m_colorScheme, 8*w1 + 8*s, 0, w1, h1);
    m_keys[10].define(key10, 10, m_colorScheme, 9*w1 + 9*s, 0, w1, h1);
    m_keys[11].define(key11, 11, m_colorScheme, 10*w1 + 10*s, 0, w2, h1);
    m_keys[12].define(key12, 12, m_colorScheme, x1, 0, w1, h1);
    m_keys[13].define(key13, 13, m_colorScheme, x1 + 1*w1 + 1*s, 0, w1, h1);
    m_keys[14].define(key14, 14, m_colorScheme, x1 + 2*w1 + 2*s, 0, w1, h1);
    m_keys[15].define(key15, 15, m_colorScheme, x1 + 3*w1 + 3*s, 0, w1, h1);
    m_keys[16].define(key16, 16, m_colorScheme, x1 + 4*w1 + 4*s, 0, w1, h1);
    m_keys[17].define(key17, 17, m_colorScheme, x1 + 5*w1 + 5*s, 0, w1, h1);
    m_keys[18].define(key18, 18, m_colorScheme, x1 + 6*w1 + 6*s, 0, w1, h1);
    m_keys[19].define(key19, 19, m_colorScheme, x1 + 7*w1 + 7*s, 0, w1, h1);
    m_keys[20].define(key20, 20, m_colorScheme, x1 + 8*w1 + 8*s, 0, w1, h1);
    m_keys[21].define(key21, 21, m_colorScheme, x1 + 9*w1 + 9*s, 0, w1, h1);
    m_keys[22].define(key22, 22, m_colorScheme, x1 + 10*w1 + 10*s, 0, w1, h1);
    m_keys[23].define(key23, 23, m_colorScheme, x2, 0, w1, h1);
    m_keys[24].define(key24, 24, m_colorScheme, x2 + 1*w1 + 1*s, 0, w1, h1);
    m_keys[25].define(key25, 25, m_colorScheme, x2 + 2*w1 + 2*s, 0, w1, h1);
    m_keys[26].define(key26, 26, m_colorScheme, x2 + 3*w1 + 3*s, 0, w1, h1);
    m_keys[27].define(key27, 27, m_colorScheme, x2 + 4*w1 + 4*s, 0, w1, h1);
    m_keys[28].define(key28, 28, m_colorScheme, x2 + 5*w1 + 5*s, 0, w1, h1);
    m_keys[29].define(key29, 29, m_colorScheme, x2 + 6*w1 + 6*s, 0, w1, h1);
    m_keys[30].define(key30, 30, m_colorScheme, x2 + 7*w1 + 7*s, 0, w1, h1);
    m_keys[31].define(key31, 31, m_colorScheme, x2 + 8*w1 + 8*s, 0, w1, h1);
    m_keys[32].define(key32, 32, m_colorScheme, x2 + 9*w1 + 9*s, 0, w1, h1);
    m_keys[33].define(key33, 33, m_colorScheme, x2 + 10*w1 + 10*s, 0, w1, h1);
    m_keys[34].define(key34, 34, m_colorScheme, 0, 0, w3, h1);
    m_keys[35].define(key35, 35, m_colorScheme, x3 + 0*w1 + 0*s, 0, w1, h1);
    m_keys[36].define(key36, 36, m_colorScheme, x3 + 1*w1 + 1*s, 0, w1, h1);
    m_keys[37].define(key37, 37, m_colorScheme, x3 + 2*w1 + 2*s, 0, w1, h1);
    m_keys[38].define(key38, 38, m_colorScheme, x3 + 3*w1 + 3*s, 0, w1, h1);
    m_keys[39].define(key39, 39, m_colorScheme, x3 + 4*w1 + 4*s, 0, w1, h1);
    m_keys[40].define(key40, 40, m_colorScheme, x3 + 5*w1 + 5*s, 0, w1, h1);
    m_keys[41].define(key41, 41, m_colorScheme, x3 + 6*w1 + 6*s, 0, w1, h1);
    m_keys[42].define(key42, 42, m_colorScheme, x3 + 7*w1 + 7*s, 0, w1, h1);
    m_keys[43].define(key43, 43, m_colorScheme, x3 + 8*w1 + 8*s, 0, w1, h1);
    m_keys[44].define(key44, 44, m_colorScheme, x3 + 9*w1 + 9*s, 0, w4, h1);
    m_keys[45].define(key45, 45, m_colorScheme, 0, 0, w2, h1);
    m_keys[46].define(key46, 46, m_colorScheme, w2 + s, 0, w5, h1);
    m_keys[47].define(key47, 47, m_colorScheme, w2 + w5 + 0*w1 + 2*s, 0, w1, h1);
    m_keys[48].define(key48, 48, m_colorScheme, w2 + w5 + 1*w1 + 3*s, 0, w1, h1);
    m_keys[49].define(key49, 49, m_colorScheme, w2 + w5 + 2*w1 + 4*s, 0, w2, h1);
    // Bind click actions for the mapped keys:
    for (Key& k : m_keys)
    {
        switch (k.type())
        {
        case Key::Type::Mapped:
            k.setClickAction(m_mappedKeyCallback);
            break;
        case Key::Type::Static:
            k.setClickAction(m_staticKeyCallback);
            break;
        case Key::Type::Blank:
            k.setClickAction(m_blankKeyCallback);
            break;
        case Key::Type::Toggle:
            k.setClickAction(m_toggleKeyCallback);
            break;
        default:
            break;
        }
    }
    // Initialize state:
    applyKeyLabels();
    Application::getInstance()->registerTimerWidget(this);
}

void Keyboard::initialize()
{
    setXY(0, 0);
    setVisible(false);
}

void Keyboard::edit(Editable& target)
{
    m_target = &target;
    m_input.resetSize(TEXT_SIZE);
    m_input.limitSize(target.size());
    m_input.getText(target);
    m_caretX = Unicode::strlen(textBuffer);
    caretUpdatePosition();
    setVisible(true);
    invalidate();
}

void Keyboard::cancel()
{
    setVisible(false);
    invalidate();
}

void Keyboard::apply()
{
    if (m_target) m_target->getText(m_input);
    setVisible(false);
    invalidate();
}

void Keyboard::handleTickEvent()
{
    if (m_bsFrames)
    {
        --m_bsFrames;
        if (!m_bsFrames) removeAll();
    }
    if (m_blFrames)
    {
        --m_blFrames;
        if (!m_blFrames)
        {
            caretBlink();
            m_blFrames = static_cast<uint16_t>(blinkTime * FPS);
        };
    }
}

bool Keyboard::handleCancellation(uint8_t keyCode, EventType e)
{
    switch (e)
    {
    case EventType::PRESSED:
        m_cancelKey = 0;
        return true;
    case EventType::CANCEL:
        m_cancelKey = keyCode;
        return true;
    case EventType::RELEASED:
        if (m_cancelKey == keyCode)
        {
            m_cancelKey = 0;
            return true;
        }
        return false;
    }
    return false;
}

void Keyboard::handleMappedKey(const Key::Mapped& sender, const ClickEvent& event)
{
    uint8_t keyCode = getKeyCode(sender);
    if (!keyCode) return;
    if (handleCancellation(keyCode, event.getType())) return;
    Unicode::UnicodeChar character = layout[m_isCapsLock ? 1 : 0][keyCode];
    if (!character) return;
    emitKeyPressedCallback();
    typeCharacter(character);
}

void Keyboard::handleStaticKey(const Key::Static& sender, const ClickEvent& event)
{
    uint8_t keyCode = getKeyCode(sender);
    switch (keyCode)
    {
    case 11:
        handleBackspace(event.getType());
        break;
    case 45:
        if (handleCancellation(keyCode, event.getType())) break;
        handleEscape();
        break;
    case 49:
        if (handleCancellation(keyCode, event.getType())) break;
        handleEnter();
        break;
    default:
        break;
    };
}

void Keyboard::handleBlankKey(const Key::Blank& sender, const ClickEvent& event)
{
    uint8_t keyCode = getKeyCode(sender);
    if (keyCode != 46) return;
    if (handleCancellation(keyCode, event.getType())) return;
    handleSpace();
}

void Keyboard::handleToggleKey(const Key::Toggle& sender, const ClickEvent& event)
{
    if (m_keys[34].contains(sender)) handleShift(m_keys[34], m_keys[44], event.getType());
    else if (m_keys[44].contains(sender)) handleShift(m_keys[44], m_keys[34], event.getType());
}

void Keyboard::handleBackspace(EventType e)
{
    switch (e)
    {
    case EventType::PRESSED:
        m_bsFrames = static_cast<uint16_t>(bsHoldTime * FPS);
        break;
    case EventType::CANCEL:
        m_bsFrames = 0;
        break;
    case EventType::RELEASED:
        if (m_bsFrames)
        {
            emitKeyPressedCallback();
            removeCharacter();
            m_bsFrames = 0;
        }
        break;
    default:
        break;
    }
}

void Keyboard::handleShift(const Key& source, const Key& target, const EventType e)
{
    bool state = source.getPressed();
    target.setPressed(state);
    if (handleCancellation(source.code(), e)) return;
    m_isCapsLock = state;
    applyKeyLabels();
}

void Keyboard::handleEscape()
{
    cancel();
    emitCanceledCallback();
}

void Keyboard::handleSpace()
{
    typeCharacter(' ');
}

void Keyboard::handleEnter()
{
    apply();
    emitAppliedCallback();
}

void Keyboard::applyKeyLabels()
{
    for (Key& k : m_keys)
        if (k.type() == Key::Type::Mapped)
            k.setLabel(layout[m_isCapsLock ? 1 : 0][k.code()]);
}

uint8_t Keyboard::getKeyCode(const Drawable& key)
{
    for (Key& k : m_keys) if (k.contains(key)) return k.code();
    return 0; // Not found in the keys container.
}

void Keyboard::typeCharacter(Unicode::UnicodeChar character)
{
    if (m_caretX > m_input.size() - 1 || !character) return;
    textBuffer[m_caretX] = character;
    if (m_caretX < m_input.size() - 1) textBuffer[m_caretX + 1] = 0;
    emitCharacterTypedCallback(character);
    text.invalidate();
    ++m_caretX;
    caretUpdatePosition();
}

void Keyboard::removeCharacter()
{
    emitKeyPressedCallback();
    if (m_caretX < 1) return;
    --m_caretX;
    textBuffer[m_caretX] = 0;
    text.invalidate();
    emitCharacterTypedCallback(8);
    caretUpdatePosition();
}

void Keyboard::removeAll()
{
    emitKeyPressedCallback();
    m_caretX = 0;
    textBuffer[0] = 0;
    text.invalidate();
    caretUpdatePosition();
}

void Keyboard::caretBlink()
{
    caret.setVisible(!caret.isVisible());
    caret.invalidate();
}

void Keyboard::caretUpdatePosition()
{
    Unicode::UnicodeChar tmpBuffer[TEXT_SIZE] = {};
    Unicode::strncpy(tmpBuffer, textBuffer, m_caretX);
    uint16_t xOffset = m_font->getStringWidth(tmpBuffer);
    caret.invalidate();
    caret.setX(xOffset);
    caret.invalidate();
}

uint16_t Key::m_textOffset = 0;
uint16_t Key::m_fontHeight = 0;
constexpr Unicode::UnicodeChar KeyboardLayout::layout[2][50];
