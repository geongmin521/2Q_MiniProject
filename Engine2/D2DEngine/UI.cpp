#include "pch.h"
#include "UI.h"
#include "../D2DEngine/EventSystem.h"

UI::UI()
{
	EventSystem::GetInstance().get()->Ui.insert(this);
}

UI::~UI()
{
}

void UI::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void UI::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget); //UI�� ���ӿ�����Ʈ�� �Ϻ��ΰԸ���.. �и��ؼ� ó���ϸ��������������� ��ġ�� �κ��� �ٽ� ������� �ϳ��� �����ϰ�������� ������ �����.. 
}
