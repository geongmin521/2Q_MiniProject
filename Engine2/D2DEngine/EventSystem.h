#pragma once
#include "SingletonBase.h"

class IClickAble;
class IDragAble;
class IDropAble;
class IOnMouse;
class GameObject;
class EventSystem : public SingletonBase<EventSystem>
{
private :
	float ClickTimer;
	bool IsMouseDown;
public:
	EventSystem() = default;
	~EventSystem() = default;
	std::set<GameObject*> Ui; //��� UI�� ��� ���߿��� ã�Ƽ� ���̳��� ĳ������ �ϰ��־��µ�.. ������ �о߸� ���� ã�ƾ�������? 
	//�ƴϸ� �����̳ʰ� .. Ŭ���̺�Ʈ�� ���´ٸ�? 
	IDragAble* curDrag;
	IOnMouse* curOnMouse;
	void Updata(float deltaTime);
	void DragEvent();
	GameObject* FindTargetUI();
	IDropAble* FindDrop();
	void DropEvent(GameObject* ui);
	void ClickEvent();
	void OnMouseEvent();

	
};

