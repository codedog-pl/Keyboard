#pragma once

#include "gui_generated/demo_screen/DemoViewBase.hpp"
#include "gui/demo_screen/DemoPresenter.hpp"

class DemoView final : public DemoViewBase
{

public:

    DemoView();
    void line1Edit() override;
    void line2Edit() override;
    void editCancel() override;
    void editApply() override;
    void keyPressed() override;
    void characterTyped(Unicode::UnicodeChar character) override;

private:

    Editable editable1; // Line1 editable.
    Editable editable2; // Line2 editable.
    char text1[LINE1_SIZE]; // UTF-8 text buffer for line 1.
    char text2[LINE2_SIZE]; // UTF-8 text buffer for line 2.

};

