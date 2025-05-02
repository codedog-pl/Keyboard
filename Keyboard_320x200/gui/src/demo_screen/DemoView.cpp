#include "gui/demo_screen/DemoView.hpp"
#include <iostream>

DemoView::DemoView()
:   editable1(Editable(line1, line1Buffer, LINE1_SIZE)),
    editable2(Editable(line2, line2Buffer, LINE2_SIZE)),
    text1(), text2() { }

void DemoView::line1Edit()
{
    keyboard.edit(editable1);
}

void DemoView::line2Edit()
{
    keyboard.edit(editable2);
}

void DemoView::editCancel()
{

}

void DemoView::editApply()
{
    if (keyboard.targets(editable1)) editable1.toUTF8(text1, LINE1_SIZE);
    else if (keyboard.targets(editable2)) editable1.toUTF8(text2, LINE2_SIZE);
}

void DemoView::keyPressed()
{
    std::cout << "KeyPressed" << std::endl;
}

void DemoView::characterTyped(Unicode::UnicodeChar character)
{
    std::cout << character << std::endl;
}
