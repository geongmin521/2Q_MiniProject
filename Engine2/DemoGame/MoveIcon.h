#pragma once
#include "UI.h"
#include "IDragAble.h"
class Container;
class MoveIcon : public UI, public IDragAble //아 추상클래스로 만들까? 그럼 공통된 정의를 가질수있을텐데.. 
	//아 근데 인터페이스도 아니고 클래스의 다중상속은 좀그럼.. 문제 생길거같은데.. 
{
private:

public://UI로 묶어서 관리한다면.. 노티피랑 aabb랑 묶어서 저장할까? 
	Container* container;
	MoveIcon(std::wstring filePath);
	virtual ~MoveIcon();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	virtual void BeginDrag(const MouseState& state) override;
	virtual void StayDrag( const MouseState& state) override;
	virtual void EndDrag(  const MouseState& state) override;
};

