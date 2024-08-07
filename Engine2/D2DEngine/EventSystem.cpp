#include "pch.h"
#include "EventSystem.h"
#include "InputSystem.h"
#include "IClickAble.h".h"
#include "IDragAble.h"
#include "IDropAble.h"
#include "IOnMouse.h"
#include "UI.h"
#include "AABB.h"

void EventSystem::Updata(float deltaTime)
{
	

	if (curDrag != nullptr) //on마우스 이벤트도.. 드래그중일땐 호출하지않기? 
		DragEvent();
	else
	{
		OnMouseEvent();

		if (inputSystem->GetMouseButtonDown(0)) //그럼 눌렀을때만 체크하면되는거지? 		
			ClickEvent();
			
	}
}

UI* EventSystem::FindTargetUI()
{
	UI* curUi = nullptr;
	int maxOrder = INT_MIN;
	for (auto ele : Ui)
	{
		if (ele->isActive == false) //활성화중인것들만 검사
			continue;

		float xpos = inputSystem->GetMouseState()._x;
		float ypos = inputSystem->GetMouseState()._y;
		MathHelper::Vector2F mousePos{ xpos,ypos };
		if (ele->boundBox->CheckPoint(mousePos)) 
		{
			if (ele->renderOrder > maxOrder) //랜더 순서가 같을수없다!
			{
				maxOrder = ele->renderOrder;
				curUi = ele;
			}
		}
	}//UI같은거는 처음에 생성되고 나면 문제없을테니까..  그냥 벡터에 순서대로 넣어놓을까? 

	return curUi;
	//위에를 재사용해야하고.. 아래거는 각각의 걸로 빼볼까? 그럼 템플리승로 만들수있을까? 근데 애들한테 접근해야함.. 
	//즉 헤더에 만들면... UI의 기능을 못씀.. 

}

void EventSystem::DropEvent(UI* ui)
{
	UI* curUi = FindTargetUI();
	IDropAble* dropAble = dynamic_cast<IDropAble*>(curUi);
	if (dropAble == nullptr)
		return;
	dropAble->OnDrop(ui);
	std::cout << "OnDrop";
}

void EventSystem::ClickEvent()
{
	UI* curUi = FindTargetUI();
	if (curUi == nullptr)
		return;
	IDragAble* dragAble = dynamic_cast<IDragAble*>(curUi);
	IClickAble* clickAble = dynamic_cast<IClickAble*>(curUi);

	if (dragAble)
	{
		dragAble->BeginDrag(inputSystem->GetMouseState()); //드래그는 좀 딜레이가 있어야하지않을까? 잘 모르겠네.. 
		curDrag = dragAble;
	}
	if (clickAble)
		clickAble->OnClick();  // 성공적으로 다운캐스팅됨
}

void EventSystem::OnMouseEvent()
{
	UI* curUi = FindTargetUI();
	if (curUi == nullptr)
		return;

	IOnMouse* onMouse = dynamic_cast<IOnMouse*>(curUi); 
	if (onMouse && curOnMouse == nullptr)
	{
		onMouse->OnMouse();
		curOnMouse = onMouse;
		std::cout << "OnMouse";
	}
	else if (curOnMouse != nullptr && onMouse == curOnMouse)
	{
		curOnMouse->StayMouse();
		std::cout << "StayMouse";
	}
	else if (onMouse != curOnMouse) 
	{
		curOnMouse->OutMouse();
		std::cout << "OutMouse";
		curOnMouse = nullptr;
	}
}

void EventSystem::DragEvent()
{
	if (InputSystem::GetInstance()->GetMouseButtonUp(0)) //마우스가 올라가면 드래그끝남
	{
		IsMouseDown = false;
		curDrag->EndDrag(inputSystem->GetMouseState());
		DropEvent(dynamic_cast<UI*>(curDrag)); //드롭이 일어남
		curDrag = nullptr; //드래그를 비워주기
	}	
	else
		curDrag->StayDrag(inputSystem->GetMouseState());
}



