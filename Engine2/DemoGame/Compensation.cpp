#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"
#include "Artifact.h"

Compensation::Compensation() 
{
	float LPad = 200; 
	//���
	Make(Image)(L"BigBack.png").setPosition({ LPad , 100 }).setScale({2,2}).setParent(this->transform);

	Make(Button)(L"smallBack.png", [this]() {compensationId = 1; btn->SetInteractive(true); }). //�ι�°���̺��϶��� �׳� ���̵� 3�� �����ֱ�
		AddText(L"���� ���ݷ� ��ȭ", 20, 0, -100).
		AddText(L"���� ĳ������ \n���ݷ��� ����\n �����Ѵ�", 20, 0, 100).
		setPos_Parent({ -100, 0 }, transform);
	Make(Button)(L"smallBack.png", [this]() {compensationId = 2; btn->SetInteractive(true); }).
		AddText(L"���� ���� �ӵ� ��ȭ", 20, 0, -100).
		AddText(L"���� ĳ������ \n���ݼӵ��� ����\n �����Ѵ�", 20, 0, 100).
		setPos_Parent({ 0, 0 }, transform);
	Make(Button)(L"smallBack.png", [this]() {compensationId = 3; btn->SetInteractive(true); }).
		AddText(L"���ڰ� ȸ�� ��ȭ", 20, 0, -100).
		AddText(L"���ڰ� ĳ������ \nȸ������ ����\n �����Ѵ�", 20, 0, 100).
		setPos_Parent({ 100, 0 }, transform);
	//����Ȯ�� ��ư 
	Make(Button)(L"ImageBack.png", [this]() {GetCompensation(); }).setPos_Parent_Text({ LPad + 500, 300 }, this->transform, L"���� �Ϸ�", 20).Get(btn);
	SetActive(false);
}

Compensation::~Compensation() //��ư������ ���� ���� ���̵� �����ϰ� �ִٰ� Ȯ���ϸ� ��Ű��Ʈ �Ŵ������� �����ֱ�
{
}

void Compensation::GetCompensation() //�� �̰͵� �߻�ȭ�ϸ� ��ĥ���ֳ�? �ٵ� ���������̶� ������������ ������ ���̴ٸ����ѵ�.. 
{
	if (compensationId == -1)
		return; //���þȵ�
	artifact->SelectArtifact(compensationId);
	SetActive(false);
}

void Compensation::Enable()
{
	compensationId = -1;
}
