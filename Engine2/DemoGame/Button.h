#pragma once
#include "UI.h"
#include "IClickAble.h"
class D2DFont;

enum  ButtonType
{
	Single, //이미지 교체없음
	Blink,  //깜빡이는 애니메이션 존재
	Active  //활성화 비활성화가 존재
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

//지금 버튼으로 처리하고있지만 달라진 부분이 3가지인데
// 아냐 두개로 나눠.. 그냥 눌러, active 활성화 버튼 나머지는 이벤트로 저장해서 .. gamemanager로 처리해.. 