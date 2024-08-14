#pragma once
#include "UI.h"
class D2DFont;

class ToolTip : public UI
{
private:
    std::vector<std::wstring> texts; 
    D2DFont* text; 
public:

    template<typename... Args> 
    ToolTip(Args&&... args)
        : texts{ std::forward<Args>(args)... } {
        Init();
    }

    virtual ~ToolTip() = default;

private:
    void Init();
};