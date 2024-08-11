#include "pch.h"
#include "UI.h"
#include "EventSystem.h"
#include "D2DFont.h"
#include "Bitmap.h"

UI::UI()
{
	EventSystem::GetInstance().get()->Ui.insert(this);
}

void UI::AddText(std::wstring text)
{
	D2DFont* Text = new D2DFont(text);
	AddComponent(Text);
	Text->SetBoxSize(GetComponent<Bitmap>()->GetSize());
}

void UI::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void UI::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget); //UI도 게임오브젝트의 일부인게맞지.. 분리해서 처리하면좋은점도있지만 겹치는 부분은 다시 만들던가 하나로 관리하고싶은때는 오히려 곤란함.. 
}

