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
	__super::Render(pRenderTarget); //UI�� ���ӿ�����Ʈ�� �Ϻ��ΰԸ���.. �и��ؼ� ó���ϸ��������������� ��ġ�� �κ��� �ٽ� ������� �ϳ��� �����ϰ�������� ������ �����.. 
}

