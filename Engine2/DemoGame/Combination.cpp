#include "pch.h"
#include "Combination.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"

Combination::Combination()
{
	renderOrder += 100;
	//������ ��ư
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 500, WinHalfSizeY - 400 }).setParent(this->transform);
	//����ǥ �̹��� �ϳ���?
	Factory().createObj<Image>(L"Combination.png").setPosition({ WinHalfSizeX , WinHalfSizeY }).setParent(this->transform);
	
	SetActive(false);
}

Combination::~Combination()
{
}
