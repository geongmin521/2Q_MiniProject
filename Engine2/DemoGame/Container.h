#pragma once
#include "UI.h"
#include "IDropAble.h"
#include "IClickAble.h"
class MoveIcon;
class Container: public UI ,public IDropAble, IClickAble//이친구는 UI가 맞을까나? dropAble 인터페이스를 상속받을거긴해
{
private:
public:
	bool isContain;
	Container();
	virtual ~Container();
	void Clear(); // 저장공간에서 빠져 나갈때
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override; //여기에 일단 박스를 그려볼까?
	virtual void OnDrop(GameObject* ui) override; //온드롭에는 현재 드래그 중인 UI가 들어와야지
	virtual void OnClick() override;
};

//상태가 아이콘상태로 다시 돌아가는게 맞나? 그게 아니라면 좀 곤란할거같은데.. 타워는 UI가 아니라..