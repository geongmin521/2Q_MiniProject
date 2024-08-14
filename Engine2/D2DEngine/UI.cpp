#include "pch.h"
#include "UI.h"
#include "EventSystem.h"
#include "D2DFont.h"
#include "Bitmap.h"

UI::UI()
{
	renderOrder = 1000;
	EventSystem::GetInstance().get()->Ui.insert(this);
}

void UI::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void UI::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget, Alpha);
}

