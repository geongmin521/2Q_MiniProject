#pragma once
#include "../D2DEngine/UI.h"

class Image : public UI
{
private:

public: //단순히 띄우기 위한 이미지
	Image(std::wstring ImagePath); //아맞다 객체의 생성자에는 매개변수를 못넣지.. 
	~Image();
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

};

