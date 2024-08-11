#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"

Compensation::Compensation() 
{
	float LeftPadding = 200;
	for (int i = 0; i < 3; i++)//보상 버튼 //눌리면 아마 선택된 상태로 전환되고 
		Factory().createObj<Button>(L"ImageBack.png", [i, this]() {}).setPosition({ LeftPadding + i * 200, WinHalfSizeY + 100 }).setRoot(&subUi);
	//보상확정 버튼 
	Factory().createObj<Button>(L"ImageBack.png", [this]() {}).setPosition({ LeftPadding + 500, WinHalfSizeY + 300 }).setRoot(&subUi);
}

Compensation::~Compensation()
{
}
