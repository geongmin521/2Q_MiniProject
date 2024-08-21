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
		return;//�����߿��� �׸�������
	__super::Render(pRenderTarget, Alpha);
	D2DRenderer::GetInstance()->DrawAABB(*boundBox); 
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
	ui->transform->SetRelativeLocation(transform->GetWorldLocation());
	return true;
}

void Container::OnMouse() //�� ���׾���� onmouse�� �ؿ��־ �����̵Ǿ��־���ϴµ�.. //on���콺�� ��� �����ϴ°Ǿ? ���� on���콺�� ��� ����Ǵ°� �����̶� �׸���ѻ����ݾ�.
{
	if (containerId < 4)
		return;
	GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/GridActive.png");
}

void Container::OutMouse()
{
	GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/Grid.png");
}

