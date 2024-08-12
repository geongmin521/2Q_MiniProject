#include "pch.h"
#include "EventSystem.h"
#include "InputSystem.h"
#include "IClickAble.h"
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



GameObject* EventSystem::FindTargetUI()
{
	GameObject* curUi = nullptr;
	int maxOrder = INT_MIN;
	for (auto ele : Ui) 
	{
		if (ele->GetActive() == false) //활성화중인것들만 검사
			continue;

		float xpos = inputSystem->GetMouseState()._x;
		float ypos = inputSystem->GetMouseState()._y;
		MathHelper::Vector2F mousePos{ xpos,ypos };
		if (ele->boundBox->CheckPoint(mousePos)) 
		{
			if (ele->renderOrder > maxOrder) //랜더 순서가 같을수없다! //대부분의 경우 위에있는것만 적용되는데.. 흠.. 함수로 처리하는걸로하자.. 
			{
				maxOrder = ele->renderOrder;
				curUi = ele;
			}
		}
	}
	return curUi;
}

IDropAble* EventSystem::FindDrop() //드랍만 특수한로직으로 검사.. 이거 다이나믹캐스드토 안하게템플릿으로하고 특수화할까? 
{
	IDropAble* curUi = nullptr;
	int maxOrder = INT_MIN;
	for (auto ele : Ui)
	{
		if (ele->GetActive() == false) //활성화중인것들만 검사
			continue;

		float xpos = inputSystem->GetMouseState()._x;
		float ypos = inputSystem->GetMouseState()._y;
		MathHelper::Vector2F mousePos{ xpos,ypos };

		if (ele->boundBox->CheckPoint(mousePos))
		{
			curUi = dynamic_cast<IDropAble*>(ele);
			if (curUi != nullptr)
			{
				return curUi;
			}
		}
	}
	return nullptr;
}

void EventSystem::DropEvent(GameObject* ui)
{
	IDropAble* dropAble = FindDrop();
	if (dropAble == nullptr)
		return;
	dropAble->OnDrop(ui);
	std::cout << "OnDrop";
}

void EventSystem::ClickEvent()
{
	GameObject* curUi = FindTargetUI();
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
	GameObject* curUi = FindTargetUI();
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
		DropEvent(dynamic_cast<GameObject*>(curDrag)); //드롭이 일어남
		curDrag = nullptr; //드래그를 비워주기
	}	
	else
		curDrag->StayDrag(inputSystem->GetMouseState());
}



