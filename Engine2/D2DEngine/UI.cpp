#include "pch.h"
#include "UI.h"
#include "EventSystem.h"

UI::UI()
{
	EventSystem::GetInstance().get()->Ui.insert(this);
}

void UI::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void UI::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget); //UI�� ���ӿ�����Ʈ�� �Ϻ��ΰԸ���.. �и��ؼ� ó���ϸ��������������� ��ġ�� �κ��� �ٽ� ������� �ϳ��� �����ϰ�������� ������ �����.. 
}
