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
		if (inputSystem->GetMouseButtonDown(0)) //�׷� ���������� üũ�ϸ�Ǵ°���? 
			FindTargetUI();
	}
}

void EventSystem::FindTargetUI() 
{
	UI* curUi = nullptr;
	int maxOrder = INT_MIN;
	for (auto ele : Ui)
	{
		if (ele->isActive == false) //Ȱ��ȭ���ΰ͵鸸 �˻�
			continue;

		float xpos = inputSystem->GetMouseState()._x;
		float ypos = inputSystem->GetMouseState()._y;
		MathHelper::Vector2F mousePos{ xpos,ypos };
		if (ele->boundBox->CheckPoint(mousePos)) 
		{
			if (ele->renderOrder > maxOrder) //���� ������ ����������!
			{
				maxOrder = ele->renderOrder;
				curUi = ele;
			}
		}
	}//UI�����Ŵ� ó���� �����ǰ� ���� ���������״ϱ�..  �׳� ���Ϳ� ������� �־������? 
	IDragAble* dragAble = dynamic_cast<IDragAble*>(curUi);
	IClickAble* clickAble = dynamic_cast<IClickAble*>(curUi);
	if (dragAble)
	{
		dragAble->BeginDrag(inputSystem->GetMouseState()); //�巡�״� �� �����̰� �־������������? �� �𸣰ڳ�.. 
		curDrag = dragAble;
	}		 
	if (clickAble) 
		clickAble->OnClick();  // ���������� �ٿ�ĳ���õ�
}

void EventSystem::DragEvent()
{
	if (InputSystem::GetInstance()->GetMouseButtonUp(0)) //���콺�� �ö󰡸� �巡�׳���
	{
		IsMouseDown = false;
		curDrag->EndDrag(inputSystem->GetMouseState());
		curDrag = nullptr; //�巡�׸� ����ֱ�
	}	
	else
		curDrag->StayDrag(inputSystem->GetMouseState());
}



