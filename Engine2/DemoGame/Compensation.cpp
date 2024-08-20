#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"
#include "Transform.h"
#include "DOTween.h"
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

void Compensation::Update(float deltatime)
{
	__super::Update(deltatime);
	if(isSelect)
	elapsedTime += deltatime;
	if (deleteTime < elapsedTime)
	{
		SetActive(false);
		elapsedTime = 0;
	}
}


void Compensation::GetCompensation() //�� �̰͵� �߻�ȭ�ϸ� ��ĥ���ֳ�? �ٵ� ���������̶� ������������ ������ ���̴ٸ����ѵ�.. 
{
	if (compensationId == -1)
		return; //���þȵ�
	artifact->SelectArtifact(compensationId);
	isSelect = true;
	auto& scale = transform->relativeScale;
	new DOTween(scale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 1, 0.05);
	new DOTween(scale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 1, 0.05);
}

void Compensation::Enable()
{
	compensationId = -1;
	isSelect = false;
	auto& scale = transform->relativeScale;
	new DOTween(scale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 2.f, 0.2, 1);
	new DOTween(scale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 2.f, 0.2, 1);
	elapsedTime = 0;
}
