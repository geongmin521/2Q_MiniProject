#pragma once
#include "UI.h"
class Button: public UI //드래그 에이블 드롭 에이블 만들어서 상속받게하고... 클릭 노티피도 만들고.. 인터페이스를 상속받고있는 모든 
	//옵서버 패턴이 되는건가? 입력 눌렀을때.. 입력받기.. 
{
private:

public:
	Button();
	~Button();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

