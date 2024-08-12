#pragma once
#include "UI.h"
#include "IClickAble.h"
class D2DFont;

class Button: public UI , public IClickAble //�巡�׶� �ܼ�Ŭ���� ��� ���������� �����غ�����.. 
{
private:

public://UI�� ��� �����Ѵٸ�.. ��Ƽ�Ƕ� aabb�� ��� �����ұ�? 
	Button(std::wstring imagePath, std::function<void(void)> func);
	virtual ~Button();
	std::function<void(void)> clickFunc;//���⿡ �Լ������ϱ�.. 
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;
	virtual void OnClick() override;
	void AddListener(std::function<void(void)> func) { clickFunc = func; }
};

