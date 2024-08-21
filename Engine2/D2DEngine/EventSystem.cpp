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

void EventSystem::reset()
{
	Ui.clear();
	curDrag = nullptr;
	curOnMouse.clear();
}

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
	IDragAble* dragAble = dynamic_cast<IDragAble*>(curUi); //어? 커렌트가 툴팁이 잡혀? 
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

	float xpos = inputSystem->GetMouseState()._x;
	float ypos = inputSystem->GetMouseState()._y;
	MathHelper::Vector2F mousePos{ xpos,ypos };

	for (auto ele : Ui)  //렌더 오더로 처리하긴하는데 겹치는게 너무 많나? 
	{
		if (ele->GetActive() == false) //활성화중인것들만 검사
			continue;		
		if (ele->boundBox->CheckPoint(mousePos)) 
		{
			if (ele->renderOrder > maxOrder) 
			{
				maxOrder = ele->renderOrder;
				curUi = ele;
			}
		}
	}
	if(curUi != nullptr)
		std::cout << curUi->name;
	return curUi;
}

std::vector<GameObject*> EventSystem::FindTargetsUI()//나중에 찾는 UI를 확정하는 방식만 다르게 해서 중복코드 줄여보자 일단 테스트
{
	std::vector<GameObject*> result;
	float xpos = inputSystem->GetMouseState()._x; //이게 업데이트가 느린건가? 
	float ypos = inputSystem->GetMouseState()._y;
	MathHelper::Vector2F mousePos{ xpos,ypos };
	
	for (auto ele : Ui)  //렌더 오더로 처리하긴하는데 겹치는게 너무 많나? 
	{
		if (ele->GetActive() == false) //활성화중인것들만 검사
			continue;
		if (ele->boundBox->CheckPoint(mousePos))
		{
			result.push_back(ele);
		}
	}
	return result;
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
		drag->FailDrop(); //여기서도 실패해야지
		return;
	}
		
	if (dropAble->OnDrop(ui) ==false)
	{
		IDragAble* drag = dynamic_cast<IDragAble*>(ui);
		drag->FailDrop(); 
	}
	std::cout << "OnDrop";
}

void EventSystem::ClickEvent()
{
	std::cout << "클릭 판정"; 
	GameObject* curUi = FindTargetUI();							
	IClickAble* clickAble = dynamic_cast<IClickAble*>(curUi);	//뭐야 지운거같은데.. 왜 들어오지.. 
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

//void EventSystem::OnMouseEvent()
//{
//	GameObject* curUi = FindTargetUI();
//	if (curUi == nullptr)
//		return;
//
//	IOnMouse* onMouse = dynamic_cast<IOnMouse*>(curUi); 
//	if (onMouse && curOnMouse == nullptr)
//	{
//		onMouse->OnMouse();
//		curOnMouse = onMouse;
//		std::cout << "OnMouse";
//	}
//	else if (onMouse != curOnMouse) 
//	{
//		curOnMouse->OutMouse();
//		std::cout << "OutMouse";
//		curOnMouse = nullptr;
//	}
//}

void EventSystem::OnMouseEvent() //테스트용 
{
	std::vector<GameObject*> curUi = FindTargetsUI();	
	if (curUi.empty())
		return;
	std::vector<IOnMouse*> onMouseUis; //현재 마우스가 위에올려진 오브젝트
	for (int i = 0; i < curUi.size(); i++)
	{
		IOnMouse* onMouse = dynamic_cast<IOnMouse*>(curUi[i]);
	
		if (onMouse != nullptr)
		{
			onMouse->OnMouse();
			onMouseUis.push_back(onMouse);			
			curOnMouse.insert(onMouse);
			std::cout << "OnMouse";
		}
		//else if (curOnMouse.find(onMouse) == curOnMouse.end()) //현재 온마우스를 저장하고있지만.. 현재 //저장하고있을까?
		//{
		//	onMouse->OutMouse();
		//	std::cout << "OutMouse";
		//	curOnMouse.erase(onMouse);
		//}
	}

	for (auto it = curOnMouse.begin(); it != curOnMouse.end();)
	{
		if (std::find(onMouseUis.begin(), onMouseUis.end(), *it) == onMouseUis.end()) // onMouseUis에 없는 경우
		{
			(*it)->OutMouse();
			it = curOnMouse.erase(it); // 현재 요소 삭제 후 다음 요소로 이동
		}
		else
		{
			++it; // 현재 요소가 유지되는 경우 다음 요소로 이동
		}
	}
	
}
