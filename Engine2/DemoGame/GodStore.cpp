#include "pch.h"
#include "GodStore.h"
#include "Factory.h"
#include "Image.h"
#include "Button.h"

GodStore::GodStore()
{
	renderOrder += 100;
	//���
	Factory().createObj<Image>(L"Combination.png").setPosition({ WinHalfSizeX , WinHalfSizeY }).setParent(this->transform);
	//������ ��ư
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 500, WinHalfSizeY - 400 }).setParent(this->transform);
	//�� ���� ��ư
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 500, WinHalfSizeY - 400 }).setParent(this->transform);
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 500, WinHalfSizeY - 400 }).setParent(this->transform);
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 500, WinHalfSizeY - 400 }).setParent(this->transform);
	//���ÿϷ�
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 500, WinHalfSizeY - 400 }).setParent(this->transform);
	
	SetActive(false);
}

GodStore::~GodStore()
{
}
