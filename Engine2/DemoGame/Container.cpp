#include "pch.h"
#include "Transform.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "Container.h"
#include "TowerBase.h"
#include "GameManager.h"

Container::Container(int id): id(id)
{
	renderOrder += id -1000;	
	boundBox->SetExtent(75,75); 
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
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
}

void Container::OnDrop(GameObject* ui) 
{
	TowerBase* tower = dynamic_cast<TowerBase*>(ui);
	if (tower == nullptr)
		return;
	if (isContain == true|| gameManager->isBattle == true) 
		return;
	tower->container = this;
	isContain = true;
	ui->transform->SetRelativeLocation(transform->GetWorldLocation());
}

