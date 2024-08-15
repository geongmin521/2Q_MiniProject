#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"

Compensation::Compensation() 
{
	float LPad = 200; 
	//���
	Make(Image)(L"BigBack.png").setPosition({ LPad , 100 }).setParent(this->transform);
	//���� ��ư 
	for (int i = 0; i < 3; i++)	
		Make(Button)(L"ImageBack.png", [i, this]() {}).setPos_Parent({LPad + i * 200, 100},this->transform);
	//����Ȯ�� ��ư 
	Make(Button)(L"ImageBack.png", [this]() {}).setPos_Parent({ LPad + 500, 300 },this->transform);
	SetActive(false);
}

Compensation::~Compensation() //��ư������ ���� ���� ���̵� �����ϰ� �ִٰ� Ȯ���ϸ� ��Ű��Ʈ �Ŵ������� �����ֱ�
{
}
