#pragma once
#include "UI.h"
#include "IDropAble.h"
#include "IClickAble.h"
#include "IOnMouse.h"
class MoveIcon;
class Container: public UI ,public IDropAble, public IOnMouse
{
private:

public:
	int containerId;
	bool isContain;
	Container(int id); 
	virtual ~Container();
	void Clear(); 
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override; 
	virtual void Update(float deltaTime) override;
	virtual bool OnDrop(GameObject* ui) override;
	virtual void OnMouse() override;
	virtual void OutMouse()override; 
};

