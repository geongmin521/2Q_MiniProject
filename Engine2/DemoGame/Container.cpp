#include "../D2DEngine/pch.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/D2DRenderer.h"
#include "Container.h"
#include "MoveIcon.h"

Container::Container()
{
	boundBox->SetExtent(75,75); //이것도 생성자에서 처리해야하는거 아닌가? 
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

void Container::OnDrop(UI* ui) //여기서 떠날때는 어떻게 감지하지? moveicon이 컨테이너를또 들고있어야하나? 
{
	MoveIcon* icon = dynamic_cast<MoveIcon*>(ui);
	if(containUi == nullptr&& icon)
	{
		icon->container = this;
		containUi = icon;
		containUi->transform->SetRelativeLocation(this->transform->GetWorldLocation());
	}
}
