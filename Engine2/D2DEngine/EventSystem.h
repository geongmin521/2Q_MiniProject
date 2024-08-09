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
	std::set<GameObject*> Ui; //모든 UI를 들고 그중에서 찾아서 다이나믹 캐스팅을 하고있었는데.. 각각의 분야를 따로 찾아야할지도? 
	//아니면 컨테이너가 .. 클릭이벤트를 갖는다면? 
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

