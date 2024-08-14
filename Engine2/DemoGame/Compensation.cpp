#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"

Compensation::Compensation() 
{
	float LeftPadding = 200; 
	Factory().createObj<Image>(L"BigBack.png").setPosition({ LeftPadding , WinHalfSizeY + 100 }).setParent(this->transform);
	for (int i = 0; i < 3; i++)//보상 버튼 
		Factory().createObj<Button>(L"ImageBack.png", [i, this]() {}).setPosition({ LeftPadding + i * 200, WinHalfSizeY + 100 }).setParent(this->transform); 
	//보상확정 버튼 
	Factory().createObj<Button>(L"ImageBack.png", [this]() {}).setPosition({ LeftPadding + 500, WinHalfSizeY + 300 }).setParent(this->transform);
	SetActive(false);
}

Compensation::~Compensation() //버튼누르면 현재 보상 아이디를 저장하고 있다가 확정하면 아키펙트 매니저한테 전해주기
{
}
