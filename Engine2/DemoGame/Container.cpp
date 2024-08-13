#include "pch.h"
#include "Transform.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "Container.h"
#include "MoveIcon.h"
#include "TowerBase.h"
#include "GameManager.h"

Container::Container(int id): id(id)
{
	renderOrder += id -1000; //얘도 UI로 해놓긴했는데 그리는 순서는 내려가야지
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
	TowerBase* tower = dynamic_cast<TowerBase*>(ui);
	if (tower == nullptr)
		return;
	if (isContain == true|| gameManager->isBattle == true) //아 여기서 게임매니저로 검사하기 싫은데.. 애초에.. 비긴 드래그를 못하면 이후가 진행되지않게만들기.. 
		return;
	tower->container = this;
	isContain = true;
	ui->transform->SetRelativeLocation(transform->GetWorldLocation());//이친구의 월드위치로 변경하기.. 
}

void Container::OnClick()//온클릭하면 담고있는 애를 버퍼에 넣어주고.. 버퍼는 마우스가 계속 누르고있어야 되는거고 놓는순간.. 다른 컨테이너를 찾는거죠? 
{ //이거완전.. 음.. 
}
