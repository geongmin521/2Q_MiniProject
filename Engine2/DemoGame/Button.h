#pragma once
#include "../D2DEngine/UI.h"
#include "../D2DEngine/IClickAble.h"
class D2DFont;

class Button: public UI , public IClickAble //�巡�׶� �ܼ�Ŭ���� ��� ���������� �����غ�����.. 
{
private:

public://UI�� ��� �����Ѵٸ�.. ��Ƽ�Ƕ� aabb�� ��� �����ұ�? 
	Button(std::wstring imagePath);
	virtual ~Button();
	std::function<void(void)> clickFunc;//���⿡ �Լ������ϱ�.. 
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	virtual void OnClick() override;
	void AddListener(std::function<void(void)> func) { clickFunc = func; }

	D2DFont* test;
};

