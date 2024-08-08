#pragma once
#include "../D2DEngine/UI.h"
#include "../D2DEngine/IClickAble.h"
class D2DFont;

class Button: public UI , public IClickAble //드래그랑 단순클릭은 어떻게 구분할지도 생각해봐야함.. 
{
private:

public://UI로 묶어서 관리한다면.. 노티피랑 aabb랑 묶어서 저장할까? 
	Button(std::wstring imagePath);
	virtual ~Button();
	std::function<void(void)> clickFunc;//여기에 함수정의하기.. 
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	virtual void OnClick() override;
	void AddListener(std::function<void(void)> func) { clickFunc = func; }

	D2DFont* test;
};

