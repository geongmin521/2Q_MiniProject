#pragma once
#include "UI.h"

class Image : public UI
{
private:

public: //�ܼ��� ���� ���� �̹���
	Image(std::wstring ImagePath); //�Ƹ´� ��ü�� �����ڿ��� �Ű������� ������.. 
	virtual ~Image();
	void ChangeImage(std::wstring path);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

};

