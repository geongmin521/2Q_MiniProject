#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"
#include "Transform.h"
#include "DOTween.h"
#include "Artifact.h"
#include "GameManager.h"
#include "D2DFont.h"
#include "DataManager.h"

#include "Music.h"
Compensation::Compensation() 
{
	float LPad = 100; 
	//배경
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setPosition({ LPad , 100 }).setParent(this->transform);

	//csv로 타입 받아서 만들기.. 
	for (int i = 0; i < 3; i++)
		name[i] = new D2DFont(L""); //이걸 그냥 더해버리면.. 사이즈를 내가 다해야함? 
	for (int i = 0; i < 3; i++)
		explain[i] = new D2DFont(L"");
	for (int i = 0; i < 3; i++)
	{
		Make(Button)(L"Frame", [this,i]() {selectedId = compensationId[i]; btn->SetInteractive(true); },ButtonType::Active). //두번째웨이브일때는 그냥 아이디 3만 더해주기
			AddComponent(name[i]).
			AddComponent(explain[i]).
			setPos_Parent({ LPad - 100 * i, 0 }, transform);
	}
	
	//보상확정 버튼 
	Make(Button)(L"Commit", [this]() {GetCompensation(); 
	Music::soundManager->PlayMusic(Music::eSoundList::Reward, Music::eSoundChannel::Effect1); }).
		setPos_Parent_Text({ LPad + 500, 300 }, this->transform, L"선택 완료", 20).Get(btn);
	SetActive(false);

	//내일 아 csv를 오늘부터 테스트하고 넘겨야할듯. 
	texts.push_back(L"성수의 공격력이 증가합니다."); //나중에 csv 한글 텍스트 읽는거 테스타하기 그 인코딩이 유니-8 csv인듯
	texts.push_back(L"말뚝의 공격력이 증가합니다.");
	texts.push_back(L"석궁의 공격력이 증가합니다.");
	texts.push_back(L"십자가의 회복량이 증가합니다.");
	texts.push_back(L"성수 캐릭터의 체력이 증가합니다.");
	texts.push_back(L"말뚝 캐릭터의 체력이 증가합니다.");
	texts.push_back(L"석궁 캐릭터의 체력이 증가합니다.");
	texts.push_back(L"십자가 캐릭터의 체력이 증가합니다.");
	texts.push_back(L"성수 캐릭터의 공격 속도가 증가합니다.");
	texts.push_back(L"말뚝 캐릭터의 공격 속도가 증가합니다.");
	texts.push_back(L"석궁 캐릭터의 공격 속도가 증가합니다.");
	texts.push_back(L"십자가 캐릭터의 회복 속도가 증가합니다.");
	texts.push_back(L"일정 시간 동안 적들에게 추가 지속 피해를 입힙니다.");
	texts.push_back(L"신앙심의 획득량이 증가합니다.");
	texts.push_back(L"내 모든 캐릭터의 공격 사거리가 증가합니다.");
	texts.push_back(L"내 모든 캐릭터의 넉백 수치가 증가합니다.");
	texts.push_back(L"적들의 공격 속도가 감소합니다.");
	texts.push_back(L"적들의 이동 속도가 줄어듭니다.");
}

Compensation::~Compensation() //버튼누르면 현재 보상 아이디를 저장하고 있다가 확정하면 아키펙트 매니저한테 전해주기
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


void Compensation::GetCompensation() //흠 이것도 추상화하면 합칠수있나? 근데 성역상점이랑 보상페이지는 성격이 많이다르긴한데.. 
{

	if (selectedId == -1)
		return; //선택안됨
	artifact->SelectArtifact(selectedId);
	isSelect = true;
	auto& scale = transform->relativeScale;
	new DOTween(scale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 1, 0.05);
	new DOTween(scale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 1, 0.05);
}

void Compensation::Enable()
{
	if (gameManager->curWaveId == 3 || gameManager->curWaveId == 6) //내일 유물이랑.. 보상 선택더 잘 해놓기.. 
	{
		//특별보상 에서 뽑기.. 
	}
	else
	{
		name[0]->SetDialog(Utility::convertFromString(dataManager->getArtifactData(0).nameText));
	}

	selectedId = -1;
	isSelect = false;
	auto& scale = transform->relativeScale;
	new DOTween(scale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 2.f, 0.2, 1);
	new DOTween(scale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 2.f, 0.2, 1);
	elapsedTime = 0;
}
