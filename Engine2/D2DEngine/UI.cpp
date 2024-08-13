#include "pch.h"
#include "UI.h"
#include "EventSystem.h"
#include "D2DFont.h"
#include "Bitmap.h"

UI::UI()
{
	EventSystem::GetInstance().get()->Ui.insert(this);
}

void UI::AddText(std::wstring text,int size) //이걸 팩토리한테 넘길수있을까? 일단한번해보면되지.. 
{
	D2DFont* Text = new D2DFont(text);
	Text->SetSize(size,{0,(unsigned int)text.size()});
	AddComponent(Text);
	Text->SetBoxSize(GetComponent<Bitmap>()->GetSize());
}

void UI::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void UI::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}

