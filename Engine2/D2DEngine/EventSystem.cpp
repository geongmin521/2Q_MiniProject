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
	std::cout << "�巡�� ��";
	if (curDrag == nullptr)
		return;
	curDrag->StayDrag(inputSystem->GetMouseState());
}

void EventSystem::BeginDragEvent()
{
	std::cout << "�巡�� ����";
	GameObject* curUi = FindTargetUI();
	IDragAble* dragAble = dynamic_cast<IDragAble*>(curUi); //��? Ŀ��Ʈ�� ������ ����? 
	if (dragAble)
	{
		dragAble->BeginDrag(inputSystem->GetMouseState()); 
		curDrag = dragAble;
	}
}

void EventSystem::EndDragEvent()
{
	std::cout << "�巡�� ����";
	if (curDrag == nullptr)
		return;
	curDrag->EndDrag(inputSystem->GetMouseState()); 
	DropEvent(dynamic_cast<GameObject*>(curDrag)); //����� �Ͼ
	curDrag = nullptr; 
}

GameObject* EventSystem::FindTargetUI() 
{
	GameObject* curUi = nullptr;
	int maxOrder = INT_MIN;

	float xpos = inputSystem->GetMouseState()._x;
	float ypos = inputSystem->GetMouseState()._y;
	MathHelper::Vector2F mousePos{ xpos,ypos };

	for (auto ele : Ui)  //���� ������ ó���ϱ��ϴµ� ��ġ�°� �ʹ� ����? 
	{
		if (ele->GetActive() == false) //Ȱ��ȭ���ΰ͵鸸 �˻�
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

std::vector<GameObject*> EventSystem::FindTargetsUI()//���߿� ã�� UI�� Ȯ���ϴ� ��ĸ� �ٸ��� �ؼ� �ߺ��ڵ� �ٿ����� �ϴ� �׽�Ʈ
{
	std::vector<GameObject*> result;
	float xpos = inputSystem->GetMouseState()._x; //�̰� ������Ʈ�� �����ǰ�? 
	float ypos = inputSystem->GetMouseState()._y;
	MathHelper::Vector2F mousePos{ xpos,ypos };
	
	for (auto ele : Ui)  //���� ������ ó���ϱ��ϴµ� ��ġ�°� �ʹ� ����? 
	{
		if (ele->GetActive() == false) //Ȱ��ȭ���ΰ͵鸸 �˻�
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
		drag->FailDrop(); //���⼭�� �����ؾ���
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
	std::cout << "Ŭ�� ����"; 
	GameObject* curUi = FindTargetUI();							
	IClickAble* clickAble = dynamic_cast<IClickAble*>(curUi);	//���� ����Ű�����.. �� ������.. 
	if (clickAble)
		clickAble->OnClick(); 
}

void EventSystem::DoubleClickEvent() 
{
	std::cout << "����Ŭ��";
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

void EventSystem::OnMouseEvent() //�׽�Ʈ�� 
{
	std::vector<GameObject*> curUi = FindTargetsUI();	
	if (curUi.empty())
		return;
	std::vector<IOnMouse*> onMouseUis; //���� ���콺�� �����÷��� ������Ʈ
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
		//else if (curOnMouse.find(onMouse) == curOnMouse.end()) //���� �¸��콺�� �����ϰ�������.. ���� //�����ϰ�������?
		//{
		//	onMouse->OutMouse();
		//	std::cout << "OutMouse";
		//	curOnMouse.erase(onMouse);
		//}
	}

	for (auto it = curOnMouse.begin(); it != curOnMouse.end();)
	{
		if (std::find(onMouseUis.begin(), onMouseUis.end(), *it) == onMouseUis.end()) // onMouseUis�� ���� ���
		{
			(*it)->OutMouse();
			it = curOnMouse.erase(it); // ���� ��� ���� �� ���� ��ҷ� �̵�
		}
		else
		{
			++it; // ���� ��Ұ� �����Ǵ� ��� ���� ��ҷ� �̵�
		}
	}
	
}
