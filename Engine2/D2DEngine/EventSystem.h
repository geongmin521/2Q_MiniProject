#pragma once
#include "SingletonBase.h"

class IClickAble;
class IDragAble;
class IDropAble;
class IOnMouse;
class GameObject;

#define eventSystem EventSystem::GetInstance().get()

class EventSystem : public SingletonBase<EventSystem>
{
private :

public:	
	POINT startPoint;
	bool isDragging;
	bool isClickValid;
	int dragThresholdX;
	int dragThresholdY;

	EventSystem();
	virtual ~EventSystem() = default;
	virtual void reset() override;
	std::set<GameObject*> Ui; 
	IDragAble* curDrag;
	std::set<IOnMouse*> curOnMouse;
	void Updata(float deltaTime);
	void StayDragEvent();
	void BeginDragEvent();
	void EndDragEvent();
	GameObject* FindTargetUI(); 
	std::vector<GameObject*> FindTargetsUI();
	IDropAble* FindDrop();
	void DropEvent(GameObject* ui);
	void ClickEvent();
	void DoubleClickEvent();
	void OnMouseEvent();
};

