#pragma once
#include "../D2DEngine/UI.h"

class Image : public UI
{
private:

public: //�ܼ��� ���� ���� �̹���
	Image(std::wstring ImagePath); //�Ƹ´� ��ü�� �����ڿ��� �Ű������� ������.. 
	~Image();
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

};

