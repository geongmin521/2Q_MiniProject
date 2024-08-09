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
	//containUi = nullptr;
}

void Container::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
}

void Container::OnDrop(GameObject* ui) //여기서 떠날때는 어떻게 감지하지? moveicon이 컨테이너를또 들고있어야하나? //다른 UI들도 처리하기.. 아이콘이 드래그앤 드롭이 아니라니..
//이걸 활용할수있는방법도 지금당장은 안떠오르고.. 
{
	IDragAble* icon = dynamic_cast<IDragAble*>(ui); //컨테이너가 무브 아이콘을 담고있는 방식인거같은데..,.,. 이거좀 그래..  인터페이스는 유지하고싶고.. 진짜 하드코딩할거면.. 컨테이너를 들고있는.. 그걸로 해야함.. 근데 서로를 알고있어야할까? 
	//그냥 담고있다 아니다만 저장하면되지않나? 음.. 그렇긴하지 서로 상호 참조할필요없지.. 
	//if (contain == nullptr && icon)
	//{
	//	icon->container = this;
	//	containUi = icon;
	//	containUi->transform->SetRelativeLocation(this->transform->GetWorldLocation());
	//}
}

void Container::OnClick()//온클릭하면 담고있는 애를 버퍼에 넣어주고.. 버퍼는 마우스가 계속 누르고있어야 되는거고 놓는순간.. 다른 컨테이너를 찾는거죠? 
{ //이거완전.. 음.. 
}
