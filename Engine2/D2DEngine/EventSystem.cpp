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
	curDrag = nullptr; 
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
			if (ele->renderOrder > maxOrder) 
			{
				maxOrder = ele->renderOrder;
				curUi = ele;
			}
		}
	}
	return curUi;
}

IDropAble* EventSystem::FindDrop() 
{
	IDropAble* curUi = nullptr;
	int maxOrder = INT_MIN;
	for (auto ele : Ui)
	{
		if (ele->GetActive() == false) 
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
	GameObject* curUi = FindTargetUI();							
	IClickAble* clickAble = dynamic_cast<IClickAble*>(curUi);	
	if (clickAble)
		clickAble->OnClick(); 
}

void EventSystem::DoubleClickEvent() 
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
	//else if (curOnMouse != nullptr && onMouse == curOnMouse) //일단 필요없어서 제외
	//{
	//	curOnMouse->StayMouse();
	//	std::cout << "StayMouse";
	//}
	else if (onMouse != curOnMouse) 
	{
		curOnMouse->OutMouse();
		std::cout << "OutMouse";
		curOnMouse = nullptr;
	}
}


