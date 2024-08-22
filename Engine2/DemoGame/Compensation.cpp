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
	renderOrder += 200;
	float LPad = 810; 
	//배경
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setParent(this->transform);
	//csv로 타입 받아서 만들기.. 
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
		Make(Button)(L"Frame", [this, i]() {selectedId = compensationId[i]; btn->SetInteractive(true); ButtonSelect(i); }, ButtonType::Active). //두번째웨이브일때는 그냥 아이디 3만 더해주기
			AddComponent(name[i]). //위치를 좀 정해주고싶은데.. 
			AddComponent(explain[i]).
			setPos_Parent({ LPad - (810 * i), -100 }, transform).Get(compensationButton[i]);
		compensationButton[i]->SetIsEnable(false);
	}

	//보상을 위한 이미지를 만들고 교체해주기.. 
	for (int i = 0; i < 3; i++)
	{
		Make(Image)(L"Artifact/Bible.png").AddRenderOrder(50).setPos_Parent({LPad - (810 * i), -100}, transform).setBoundBox(0,0).Get(img[i]);
	}
	//보상확정 버튼 
	Make(Button)(L"Commit", [this]() {GetCompensation();
	Music::soundManager->PlayMusic(Music::eSoundList::RewardClose, Music::eSoundChannel::Effect2);
	}).setPos_Parent({ 0, 410 }, this->transform).Get(btn);
	SetActive(false);

	SpecialArtifactID = dataManager->getSpecialArtifactID();
}

Compensation::~Compensation() //버튼누르면 현재 보상 아이디를 저장하고 있다가 확정하면 아키펙트 매니저한테 전해주기
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


void Compensation::GetCompensation() //흠 이것도 추상화하면 합칠수있나? 근데 성역상점이랑 보상페이지는 성격이 많이다르긴한데.. 
{

	if (selectedId == -1)
		return; //선택안됨
	artifact->SelectArtifact(selectedId);
	auto it = std::find(SpecialArtifactID.begin(), SpecialArtifactID.end(), selectedId);
	if (it != SpecialArtifactID.end()) {
		SpecialArtifactID.erase(it); //스페셜유물은 뽑고나면 지우기
	}
	isSelect = true;
	auto& scale = transform->relativeScale;
	new DOTween(scale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.75f, 0.05);
	new DOTween(scale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.75f, 0.05);
}

void Compensation::ChoseCompensation(bool special)
{
	vector<int> result;
	if (special == false)
		result = Utility::RandomUniqueValuesFromVector(dataManager->getNormalArtifactID(), 3); //노말 유물 3개뽑기
	else 
		result = Utility::RandomUniqueValuesFromVector(SpecialArtifactID, 3);//특별 유물 3개뽑기 //이거 3개보다 부족할수없겠지? 유물이 3개이상 뽑을순없겠지? 
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
	Music::soundManager->PlayMusic(Music::eSoundList::RewardOpen, Music::eSoundChannel::Effect1);
}

void Compensation::ButtonSelect(int num)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == num)
			continue;
		compensationButton[i]->SetIsEnable(false);
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
	for(int i=0;i<3;i++)
		compensationButton[i]->SetIsEnable(false);
}

void Compensation::Disable()
{
	if (gameManager->events[Event::ShowWaveFunc] != nullptr && showonce == true)
	{
		showonce = false;
		gameManager->events[Event::ShowWaveFunc]();
	}	
}
