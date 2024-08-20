#pragma once
#include "UI.h"
#include "IClickAble.h"
class D2DFont;

enum  ButtonType
{
	Single, //�̹��� ��ü����
	Blink,  //�����̴� �ִϸ��̼� ����
	Active  //Ȱ��ȭ ��Ȱ��ȭ�� ����
};

class Button: public UI , public IClickAble 
{
private:
	bool interactive =true;
	bool isClicked = false;
	bool isEnable = true;
	std::function<void(void)> clickFunc;
	float aniTime =0.5f;
	float Timer =0;
	std::function<void(void)> Click;
public:
	Button(std::wstring imagePath, std::function<void(void)> func, ButtonType type = ButtonType::Blink);
	virtual ~Button();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;
	virtual void OnClick() override;
	void SetListener(std::function<void(void)> func) { clickFunc = func; }
	void ClearListener() { clickFunc = nullptr; }
	void SetInteractive(bool active) { interactive = active; }
	bool GetInteractive() {return interactive; }
	void Blick();
	void Single();
	void Active();
	void SetIsEnable(bool enable);
};

//���� ��ư���� ó���ϰ������� �޶��� �κ��� 3�����ε�
// �Ƴ� �ΰ��� ����.. �׳� ����, active Ȱ��ȭ ��ư �������� �̺�Ʈ�� �����ؼ� .. gamemanager�� ó����.. 