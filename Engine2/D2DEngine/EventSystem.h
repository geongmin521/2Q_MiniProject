#pragma once
#include "SingletonBase.h"

class IClickAble;
class IDragAble;
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
	

	void Updata(float deltaTime);

	void ClickEvent();
	void DragEvent();
	void FindTargetUI();
};

