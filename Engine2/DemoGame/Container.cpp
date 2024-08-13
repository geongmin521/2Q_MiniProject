#include "pch.h"
#include "Transform.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "Container.h"
#include "MoveIcon.h"
#include "TowerBase.h"

Container::Container()
{
	boundBox->SetExtent(75,75); //이것도 생성자에서 처리해야하는거 아닌가? 
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
	if (isContain == true)
		return;
	//다른곳으로의 드롭이 성공하면 얘는 false가되어야하고.. 
	//아 정말 이렇게 하기 싫긴한데.. 방법을 모르겠네..
	TowerBase* tower = dynamic_cast<TowerBase*>(ui);
	if (tower != nullptr)
		tower->container = this;
	isContain = true;
	ui->transform->SetRelativeLocation(transform->GetWorldLocation());//이친구의 월드위치로 변경하기.. 
}

void Container::OnClick()//온클릭하면 담고있는 애를 버퍼에 넣어주고.. 버퍼는 마우스가 계속 누르고있어야 되는거고 놓는순간.. 다른 컨테이너를 찾는거죠? 
{ //이거완전.. 음.. 
}
