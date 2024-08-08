#include "../D2DEngine/pch.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/D2DRenderer.h"
#include "Container.h"
#include "MoveIcon.h"

Container::Container()
{
	boundBox->SetExtent(75,75); //�̰͵� �����ڿ��� ó���ؾ��ϴ°� �ƴѰ�? 
}

Container::~Container()
{

}

void Container::Clear()
{
	containUi = nullptr;
}

void Container::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
}

void Container::OnDrop(UI* ui) //���⼭ �������� ��� ��������? moveicon�� �����̳ʸ��� ����־���ϳ�? 
{
	MoveIcon* icon = dynamic_cast<MoveIcon*>(ui);
	if(containUi == nullptr&& icon)
	{
		icon->container = this;
		containUi = icon;
		containUi->transform->SetRelativeLocation(this->transform->GetWorldLocation());
	}
}
