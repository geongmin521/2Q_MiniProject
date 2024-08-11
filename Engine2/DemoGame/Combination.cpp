#include "pch.h"
#include "Combination.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"

Combination::Combination()
{
	//������ ��ư
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 500, WinHalfSizeY - 400 }).setRoot(&subUi);
	//����ǥ �̹��� �ϳ���?
	Factory().createObj<Image>(L"Combination.png").setPosition({ WinHalfSizeX , WinHalfSizeY }).setRoot(&subUi);
	renderOrder = 100;
}

Combination::~Combination()
{
}
