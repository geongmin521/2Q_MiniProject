#pragma once
#include "UI.h"
#include "IDropAble.h"
#include "IClickAble.h"
class MoveIcon;
class Container: public UI ,public IDropAble
{
private:
	int id;
public:
	bool isContain;
	Container(int id = 0); 
	virtual ~Container();
	void Clear(); 
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override; 
	virtual void OnDrop(GameObject* ui) override; 
};

