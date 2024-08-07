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
	

	if (curDrag != nullptr) //on���콺 �̺�Ʈ��.. �巡�����϶� ȣ�������ʱ�? 
		DragEvent();
	else
	{
		OnMouseEvent();

		if (inputSystem->GetMouseButtonDown(0)) //�׷� ���������� üũ�ϸ�Ǵ°���? 		
			ClickEvent();
			
	}
}

UI* EventSystem::FindTargetUI()
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

	return curUi;
	//������ �����ؾ��ϰ�.. �Ʒ��Ŵ� ������ �ɷ� ������? �׷� ���ø��·� �����������? �ٵ� �ֵ����� �����ؾ���.. 
	//�� ����� �����... UI�� ����� ����.. 

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
		dragAble->BeginDrag(inputSystem->GetMouseState()); //�巡�״� �� �����̰� �־������������? �� �𸣰ڳ�.. 
		curDrag = dragAble;
	}
	if (clickAble)
		clickAble->OnClick();  // ���������� �ٿ�ĳ���õ�
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
	if (InputSystem::GetInstance()->GetMouseButtonUp(0)) //���콺�� �ö󰡸� �巡�׳���
	{
		IsMouseDown = false;
		curDrag->EndDrag(inputSystem->GetMouseState());
		DropEvent(dynamic_cast<UI*>(curDrag)); //����� �Ͼ
		curDrag = nullptr; //�巡�׸� ����ֱ�
	}	
	else
		curDrag->StayDrag(inputSystem->GetMouseState());
}



