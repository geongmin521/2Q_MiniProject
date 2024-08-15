#include "pch.h"
#include "Combination.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"

Combination::Combination()
{
	renderOrder += 100;
	Make(Button)(L"smallBack.png", [this]() { SetActive(false); }).setPos_Parent({500, -400},this->transform);//나가기 버튼
	Make(Image)(L"Combination.png").setParent(this->transform);	//조합표	
	SetActive(false);
}

Combination::~Combination()
{
}
