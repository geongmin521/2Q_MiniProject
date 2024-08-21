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

Compensation::Compensation() 
{
	float LPad = 810; 
	//���
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setParent(this->transform);
	renderOrder += 50;
	//csv�� Ÿ�� �޾Ƽ� �����.. 
	for (int i = 0; i < 3; i++)
	{
		name[i] = new D2DFont(L"");
		name[i]->SetPos(0, -115);
		name[i]->SetSize(40, {0,0});
		name[i]->SetBoxSize({380,80});
	}

	for (int i = 0; i < 3; i++)
	{
		explain[i] = new D2DFont(L"");
		explain[i]->SetPos(0, 140);
		explain[i]->SetSize(40, { 0,0 });
		explain[i]->SetBoxSize({ 380,180 });
	}
		
	for (int i = 0; i < 3; i++)
	{
		Make(Button)(L"Frame", [this,i]() {selectedId = compensationId[i]; btn->SetInteractive(true); },ButtonType::Active). //�ι�°���̺��϶��� �׳� ���̵� 3�� �����ֱ�
			AddComponent(name[i]). //��ġ�� �� �����ְ������.. 
			AddComponent(explain[i]).
			setPos_Parent({ LPad - (810 * i), -100 }, transform).Get(compensationButton[i]);
		compensationButton[i]->SetIsEnable(false);
	}

	//������ ���� �̹����� ����� ��ü���ֱ�.. 
	for (int i = 0; i < 3; i++)
	{
		Make(Image)(L"Artifact/Bible.png").setPos_Parent({ LPad - (810 * i), -100 }, transform).Get(img[i]);
	}
	//����Ȯ�� ��ư 
	Make(Button)(L"Commit", [this]() {GetCompensation(); }).
		setPos_Parent({ 0, 410 }, this->transform).Get(btn);
	SetActive(false);
}

Compensation::~Compensation() //��ư������ ���� ���� ���̵� �����ϰ� �ִٰ� Ȯ���ϸ� ��Ű��Ʈ �Ŵ������� �����ֱ�
{
}

void Compensation::Update(float deltatime)
{
	__super::Update(deltatime);
	std::cout << transform->GetRelativeScale().x;
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
	new DOTween(scale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.75f, 0.05);
	new DOTween(scale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.75f, 0.05);
}

void Compensation::ChoseCompensation(bool special)
{
	vector<int> result;
	if (special == false)
		result = Utility::RandomUniqueValuesFromVector(dataManager->getNormalArtifactID(), 3); //�븻 ���� 3���̱�
	else 
		result = Utility::RandomUniqueValuesFromVector(dataManager->getSpecialArtifactID(), 3);//Ư�� ���� 3���̱�
	for (int i = 0; i < result.size(); i++)
	{
		wstring wtext1 = Utility::StringToWStringA(dataManager->getArtifactData(result[i]).nameText);
		wstring wtext2 = Utility::StringToWStringA(dataManager->getArtifactData(result[i]).explainText);
		wstring artifactPath = Utility::StringToWStringA(dataManager->getArtifactData(result[i]).filePath);
		name[i]->SetDialog(wtext1);
		explain[i]->SetDialog(wtext2);
		compensationId[i] = result[i];
		img[i]->ChangeImage(L"../Data/Image/Artifact/"+ artifactPath +L".png");
	}
}

void Compensation::Enable() 
{
	selectedId = -1;
	isSelect = false;
	auto& scale = transform->relativeScale;
	new DOTween(scale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 2.f, 0.2, 0.75f);
	new DOTween(scale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 2.f, 0.2, 0.75f);
	elapsedTime = 0;
}

void Compensation::Disable()
{
	if(gameManager->events[Event::ShowWaveFunc] != nullptr)
		gameManager->events[Event::ShowWaveFunc]();
}
