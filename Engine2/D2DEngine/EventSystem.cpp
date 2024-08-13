#include "pch.h"
#include "EventSystem.h"
#include "InputSystem.h"
#include "IClickAble.h"
#include "IDragAble.h"
#include "IDropAble.h"
#include "IOnMouse.h"
#include "IDoubleClickAble.h"
#include "UI.h"
#include "AABB.h"

void EventSystem::Updata(float deltaTime) 
{
	OnMouseEvent();
}

void EventSystem::StayDragEvent()
{
	std::cout << "드래그 중";
	if (curDrag == nullptr)
		return;
	curDrag->StayDrag(inputSystem->GetMouseState());
}

void EventSystem::BeginDragEvent()
{
	std::cout << "드래그 판정";
	GameObject* curUi = FindTargetUI();
	IDragAble* dragAble = dynamic_cast<IDragAble*>(curUi);
	if (dragAble)
	{
		dragAble->BeginDrag(inputSystem->GetMouseState()); 
		curDrag = dragAble;
	}
}

void EventSystem::EndDragEvent()
{
	std::cout << "드래그 종료";
	if (curDrag == nullptr)
		return;
	curDrag->EndDrag(inputSystem->GetMouseState()); 
	DropEvent(dynamic_cast<GameObject*>(curDrag)); //드롭이 일어남
	curDrag = nullptr; //드래그를 비워주기
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

void EventSystem::DropEvent(GameObject* ui) //드롭이 들어올려면.. 드래그 에이블이여하는데 매개변수를 바꿀까? 
{
	IDropAble* dropAble = FindDrop();
	if (dropAble == nullptr)
	{
		IDragAble* drag = dynamic_cast<IDragAble*>(ui);
		drag->FailDrop();
		return;
	}
		
	dropAble->OnDrop(ui);
	std::cout << "OnDrop";
}

void EventSystem::ClickEvent()
{
	std::cout << "클릭 판정"; 
	GameObject* curUi = FindTargetUI(); //애도 템플릿으로 만들어서 다이나믹 캐스트를 해서 넘기는 식으로 하자.. 
	IClickAble* clickAble = dynamic_cast<IClickAble*>(curUi);//이렇게 하는게 아니라 한번더 판단을 하는건데...
	if (clickAble)
		clickAble->OnClick();  // 성공적으로 다운캐스팅됨
}

void EventSystem::DoubleClickEvent() //윈도우 메세지로 처리하면 아주쉽게 판별할수가있네요.. 허허.. 
{
	std::cout << "더블클릭";
	GameObject* curUi = FindTargetUI();
	IDoubleClickAble* doubleClickAble = dynamic_cast<IDoubleClickAble*>(curUi);
	if(doubleClickAble)
		doubleClickAble->OnDoubleClick();
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


