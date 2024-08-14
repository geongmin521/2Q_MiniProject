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

public:	
	POINT startPoint;
	bool isDragging;
	bool isClickValid;
	int dragThresholdX;
	int dragThresholdY;

	EventSystem() = default;
	~EventSystem() = default;
	std::set<GameObject*> Ui; 
	IDragAble* curDrag;
	IOnMouse* curOnMouse;
	void Updata(float deltaTime);
	void StayDragEvent();
	void BeginDragEvent();
	void EndDragEvent();
	GameObject* FindTargetUI();
	IDropAble* FindDrop();
	void DropEvent(GameObject* ui);
	void ClickEvent();
	void DoubleClickEvent();
	void OnMouseEvent();

	
};

