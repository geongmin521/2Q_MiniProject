#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"

Compensation::Compensation() 
{
	float LPad = 200; 
	//배경
	Make(Image)(L"BigBack.png").setPosition({ LPad , 100 }).setParent(this->transform);
	//보상 버튼 
	for (int i = 0; i < 3; i++)	
		Make(Button)(L"ImageBack.png", [i, this]() {}).setPos_Parent({LPad + i * 200, 100},this->transform);
	//보상확정 버튼 
	Make(Button)(L"ImageBack.png", [this]() {}).setPos_Parent({ LPad + 500, 300 },this->transform);
	SetActive(false);
}

Compensation::~Compensation() //버튼누르면 현재 보상 아이디를 저장하고 있다가 확정하면 아키펙트 매니저한테 전해주기
{
}
