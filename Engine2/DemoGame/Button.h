#pragma once
#include "UI.h"
#include "IClickAble.h"
class D2DFont;

class Button: public UI , public IClickAble //�巡�׶� �ܼ�Ŭ���� ��� ���������� �����غ�����.. 
{
private:
	bool interactive =true;
	std::function<void(void)> clickFunc;
public:
	Button(std::wstring imagePath, std::function<void(void)> func);
	virtual ~Button();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;
	virtual void OnClick() override;
	void SetListener(std::function<void(void)> func) { clickFunc = func; } //��ǻ� ���尡 �Ƴ��� ����̳� 
	void ClearListener() { clickFunc = nullptr; }
	void SetInteractive(bool active) { interactive = active; }
	bool GetInteractive() {return interactive; }
};

