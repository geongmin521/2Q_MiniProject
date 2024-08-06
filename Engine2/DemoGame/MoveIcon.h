#pragma once
#include "../D2DEngine/UI.h"
#include "../D2DEngine/IDragAble.h"
class MoveIcon : public UI, public IDragAble //�� �߻�Ŭ������ �����? �׷� ����� ���Ǹ� �����������ٵ�.. 
	//�� �ٵ� �������̽��� �ƴϰ� Ŭ������ ���߻���� ���׷�.. ���� ����Ű�����.. 
{
private:

public://UI�� ��� �����Ѵٸ�.. ��Ƽ�Ƕ� aabb�� ��� �����ұ�? 
	MoveIcon(std::wstring filePath);
	~MoveIcon();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	virtual void BeginDrag(const MouseState& state) override;
	virtual void StayDrag( const MouseState& state) override;
	virtual void EndDrag(  const MouseState& state) override;
};

