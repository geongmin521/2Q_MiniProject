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
	//이친구는 드래그엔 드롭을 전혀안쓸지도?
	//클릭하면 놓고.. 클릭하면 다시올리고?
	//아 타워는 드래그앤 드롭이여야하는데 흠.. 
	//그럼 걍 원래하던대로 할걸그랬나? 소환해서 바꿔주고 바꿔주고 소환하고 체력이나 유지될려면 왔다갔다하는것도 별로안좋고.. 
	//아 머리가 별로 안돌아가네 먹으면서 생각하자.. 
}

void Container::OnClick()//온클릭하면 담고있는 애를 버퍼에 넣어주고.. 버퍼는 마우스가 계속 누르고있어야 되는거고 놓는순간.. 다른 컨테이너를 찾는거죠? 
{ //이거완전.. 음.. 
}
