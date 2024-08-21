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
	//���
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setPosition({ LPad , 100 }).setParent(this->transform);

	//csv�� Ÿ�� �޾Ƽ� �����.. 
	for (int i = 0; i < 3; i++)
		name[i] = new D2DFont(L""); //�̰� �׳� ���ع�����.. ����� ���� ���ؾ���? 
	for (int i = 0; i < 3; i++)
		explain[i] = new D2DFont(L"");
	for (int i = 0; i < 3; i++)
	{
		Make(Button)(L"Frame", [this,i]() {selectedId = compensationId[i]; btn->SetInteractive(true); },ButtonType::Active). //�ι�°���̺��϶��� �׳� ���̵� 3�� �����ֱ�
			AddComponent(name[i]).
			AddComponent(explain[i]).
			setPos_Parent({ LPad - 100 * i, 0 }, transform);
	}
	
	//����Ȯ�� ��ư 
	Make(Button)(L"Commit", [this]() {GetCompensation(); 
	Music::soundManager->PlayMusic(Music::eSoundList::Reward, Music::eSoundChannel::Effect1); }).
		setPos_Parent_Text({ LPad + 500, 300 }, this->transform, L"���� �Ϸ�", 20).Get(btn);
	SetActive(false);

	//���� �� csv�� ���ú��� �׽�Ʈ�ϰ� �Ѱܾ��ҵ�. 
	texts.push_back(L"������ ���ݷ��� �����մϴ�."); //���߿� csv �ѱ� �ؽ�Ʈ �д°� �׽�Ÿ�ϱ� �� ���ڵ��� ����-8 csv�ε�
	texts.push_back(L"������ ���ݷ��� �����մϴ�.");
	texts.push_back(L"������ ���ݷ��� �����մϴ�.");
	texts.push_back(L"���ڰ��� ȸ������ �����մϴ�.");
	texts.push_back(L"���� ĳ������ ü���� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ü���� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ü���� �����մϴ�.");
	texts.push_back(L"���ڰ� ĳ������ ü���� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ���� �ӵ��� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ���� �ӵ��� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ���� �ӵ��� �����մϴ�.");
	texts.push_back(L"���ڰ� ĳ������ ȸ�� �ӵ��� �����մϴ�.");
	texts.push_back(L"���� �ð� ���� ���鿡�� �߰� ���� ���ظ� �����ϴ�.");
	texts.push_back(L"�žӽ��� ȹ�淮�� �����մϴ�.");
	texts.push_back(L"�� ��� ĳ������ ���� ��Ÿ��� �����մϴ�.");
	texts.push_back(L"�� ��� ĳ������ �˹� ��ġ�� �����մϴ�.");
	texts.push_back(L"������ ���� �ӵ��� �����մϴ�.");
	texts.push_back(L"������ �̵� �ӵ��� �پ��ϴ�.");
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

	if (selectedId == -1)
		return; //���þȵ�
	artifact->SelectArtifact(selectedId);
	isSelect = true;
	auto& scale = transform->relativeScale;
	new DOTween(scale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 1, 0.05);
	new DOTween(scale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 1, 0.05);
}

void Compensation::Enable()
{
	if (gameManager->curWaveId == 3 || gameManager->curWaveId == 6) //���� �����̶�.. ���� ���ô� �� �س���.. 
	{
		//Ư������ ���� �̱�.. 
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
