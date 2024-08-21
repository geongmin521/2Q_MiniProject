#include "pch.h"
#include "Transform.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "Container.h"
#include "TowerBase.h"
#include "GameManager.h"
#include "Bitmap.h"

Container::Container(int id): containerId(id)
{
	renderOrder += id - 1000;	
	boundBox->SetExtent(75,75); 
	AddComponent(new Bitmap(L"../Data/Image/Grid.png"));
}

Container::~Container()
{

}

void Container::Clear()
{
	isContain = false;
}

void Container::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	if (gameManager->isBattle == true)
		return;//전투중에는 그리지않음
	__super::Render(pRenderTarget, Alpha);
#if(_DEBUG) 
	D2DRenderer::GetInstance()->DrawAABB(*boundBox); 
#endif
}

void Container::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

bool Container::OnDrop(GameObject* ui) 
{
	TowerBase* tower = dynamic_cast<TowerBase*>(ui);
	if (tower == nullptr)
		return false;
	if (isContain == true|| gameManager->isBattle == true) 
		return false;
	tower->container = this;
	isContain = true;
	ui->transform->SetRelativeLocation({ transform->GetWorldLocation().x, transform->GetWorldLocation().y - 50 });
	return true;
}

void Container::OnMouse() //아 컨테어너의 onmouse는 밑에있어도 적용이되어있어야하는데.. //on마우스는 모두 적용하는건어떰? 지금 on마우스가 모두 적용되는게 툴팁이랑 그리드ㅡ뿐이잖아.
{
	if (containerId < 4)
		return;
	GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/GridActive.png");
}

void Container::OutMouse()
{
	GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/Grid.png");
}

