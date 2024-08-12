#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"

Compensation::Compensation() 
{
	float LeftPadding = 200;
	for (int i = 0; i < 3; i++)//���� ��ư //������ �Ƹ� ���õ� ���·� ��ȯ�ǰ� 
		Factory().createObj<Button>(L"ImageBack.png", [i, this]() {}).setPosition({ LeftPadding + i * 200, WinHalfSizeY + 100 }).setParent(this->transform);
	//����Ȯ�� ��ư 
	Factory().createObj<Button>(L"ImageBack.png", [this]() {}).setPosition({ LeftPadding + 500, WinHalfSizeY + 300 }).setParent(this->transform);
}

Compensation::~Compensation()
{
}
