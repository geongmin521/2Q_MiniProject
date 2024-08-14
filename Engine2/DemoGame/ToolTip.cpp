#include "pch.h"
#include "ToolTip.h"
#include "D2DFont.h"
#include "Bitmap.h"

void ToolTip::Init()
{
    std::wstring textbuffer; 

    for (const auto& val : texts) {
        textbuffer += val + L"\n";
    }
    text = new D2DFont(textbuffer);
    AddComponent(new Bitmap(L"../Data/Image/smallBack.png")); 
    AddComponent(text);     
  
    text->SetSize(20, { 0, static_cast<unsigned int>(textbuffer.size()) });

}
