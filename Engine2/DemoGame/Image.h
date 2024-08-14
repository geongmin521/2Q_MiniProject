#pragma once
#include "UI.h"

class Image : public UI
{
private:

public:
	Image(std::wstring ImagePath); 
	virtual ~Image();
	void ChangeImage(std::wstring path);
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;

};

