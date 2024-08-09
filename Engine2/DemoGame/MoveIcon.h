#pragma once
#include "UI.h"
#include "IDragAble.h"
class Container;
class MoveIcon : public UI, public IDragAble //�� �߻�Ŭ������ �����? �׷� ����� ���Ǹ� �����������ٵ�.. 
	//�� �ٵ� �������̽��� �ƴϰ� Ŭ������ ���߻���� ���׷�.. ���� ����Ű�����.. 
{
private:

public://UI�� ��� �����Ѵٸ�.. ��Ƽ�Ƕ� aabb�� ��� �����ұ�? 
	Container* container;
	MoveIcon(std::wstring filePath);
	virtual ~MoveIcon();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	virtual void BeginDrag(const MouseState& state) override;
	virtual void StayDrag( const MouseState& state) override;
	virtual void EndDrag(  const MouseState& state) override;
};

