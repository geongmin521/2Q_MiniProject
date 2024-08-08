#pragma once
#include "SingletonBase.h"

class IClickAble;
class IDragAble;
class IDropAble;
class IOnMouse;
class UI;
class EventSystem : public SingletonBase<EventSystem>
{
private :
	float ClickTimer;
	bool IsMouseDown;
public:
	EventSystem() = default;
	~EventSystem() = default;
	std::set<UI*> Ui;
	IDragAble* curDrag;
	IOnMouse* curOnMouse;
	void Updata(float deltaTime);
	void DragEvent();
	UI* FindTargetUI();
	IDropAble* FindDrop();
	void DropEvent(UI* ui);
	void ClickEvent();
	void OnMouseEvent();

	
};

