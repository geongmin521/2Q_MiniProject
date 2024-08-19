#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"
#include "Artifact.h"

Compensation::Compensation() 
{
	float LPad = 200; 
	//배경
	Make(Image)(L"BigBack.png").setPosition({ LPad , 100 }).setScale({2,2}).setParent(this->transform);

	Make(Button)(L"smallBack.png", [this]() {compensationId = 1; btn->SetInteractive(true); }). //두번째웨이브일때는 그냥 아이디 3만 더해주기
		AddText(L"석궁 공격력 강화", 20, 0, -100).
		AddText(L"석궁 캐릭터의 \n공격력이 소폭\n 증가한다", 20, 0, 100).
		setPos_Parent({ -100, 0 }, transform);
	Make(Button)(L"smallBack.png", [this]() {compensationId = 2; btn->SetInteractive(true); }).
		AddText(L"성수 공격 속도 강화", 20, 0, -100).
		AddText(L"성수 캐릭터의 \n공격속도가 소폭\n 증가한다", 20, 0, 100).
		setPos_Parent({ 0, 0 }, transform);
	Make(Button)(L"smallBack.png", [this]() {compensationId = 3; btn->SetInteractive(true); }).
		AddText(L"십자가 회복 강화", 20, 0, -100).
		AddText(L"십자가 캐릭터의 \n회복력이 소폭\n 증가한다", 20, 0, 100).
		setPos_Parent({ 100, 0 }, transform);
	//보상확정 버튼 
	Make(Button)(L"ImageBack.png", [this]() {GetCompensation(); }).setPos_Parent_Text({ LPad + 500, 300 }, this->transform, L"선택 완료", 20).Get(btn);
	SetActive(false);
}

Compensation::~Compensation() //버튼누르면 현재 보상 아이디를 저장하고 있다가 확정하면 아키펙트 매니저한테 전해주기
{
}

void Compensation::GetCompensation() //흠 이것도 추상화하면 합칠수있나? 근데 성역상점이랑 보상페이지는 성격이 많이다르긴한데.. 
{
	if (compensationId == -1)
		return; //선택안됨
	artifact->SelectArtifact(compensationId);
	SetActive(false);
}

void Compensation::Enable()
{
	compensationId = -1;
}
