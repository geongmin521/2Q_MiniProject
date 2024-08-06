#include "pch.h"
#include "EventSystem.h"
#include "InputSystem.h"
#include "IClickAble.h".h"
#include "IDragAble.h"
#include "UI.h"
#include "AABB.h"

void EventSystem::Updata(float deltaTime)
{
	if (curDrag != nullptr)
		DragEvent();
	else
	{
		if (inputSystem->GetMouseButtonDown(0)) //그럼 눌렀을때만 체크하면되는거지? 
			FindTargetUI();
	}
}

void EventSystem::FindTargetUI() 
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

void EventSystem::DragEvent()
{
	if (InputSystem::GetInstance()->GetMouseButtonUp(0)) //마우스가 올라가면 드래그끝남
	{
		IsMouseDown = false;
		curDrag->EndDrag(inputSystem->GetMouseState());
		curDrag = nullptr; //드래그를 비워주기
	}	
	else
		curDrag->StayDrag(inputSystem->GetMouseState());
}



