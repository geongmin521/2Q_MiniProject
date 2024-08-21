#include "pch.h"
#include "Factory.h"
#include "ShowWave.h"
#include "Image.h"
#include "Button.h"
#include "DataManager.h"
#include "GameManager.h"
#include "Image.h"
#include "DOTween.h"
#include "Transform.h"
#include "D2DFontManager.h"
#include "D2DFont.h"

ShowWave::ShowWave()
{
	float LPad = -200;
	//배경
	//적들아이콘
	//종료버튼
	Make(Image)(L"UI/Pop_up/popup_Round.png").setParent(this->transform);
	for (int i = 0; i < 4; i++)	
		Make(Image)(L"Enemy/One/NormalEnemy.png").setPos_Parent({LPad + i * 400 ,0}, transform).AddText(L"", 70,0,95).Get<Image>(images[i]);		
	//Make(Button)(L"smallBack", [this]() { SetActive(false); }).setPos_Parent({ 400, -400 }, transform);
	SetActive(false);
}

ShowWave::~ShowWave()
{

}

void ShowWave::Update(float deltatime)
{
	__super::Update(deltatime);
	
	elapsedTime += deltatime;
	if (!isMid && elapsedTime >= 3.f)
	{
		isMid = true; //중앙에 왔다고하면 3초대기후 
		elapsedTime = 0;
	}
	
	if (isMid && !isExit && elapsedTime >= middleTime)
	{
		isExit = true;
		auto& loca = transform->relativeLocation;
		elapsedTime = 0;
		new DOTween(loca.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 5.f, loca.x, loca.x- 2000);
	}

	if (isMid && isExit && elapsedTime >= 5.0f)
	{
		SetActive(false);
		elapsedTime = 0;
	}
	
}


void ShowWave::Show()  
{
	dataManager->ChoseWave(); 
	isMid = false;
	isExit = false;
	elapsedTime = 0;
	SetActive(true);
	transform->SetRelativeLocation({ WinHalfSizeX + 1200, WinHalfSizeY });
	
	int curid = gameManager->curWaveId;
	WaveData wave = dataManager->getWaveData(curid);
	int size = wave.enemyId.size();
	
	for (int i = 0; i < size; i++) 
	{
		images[i]->ChangeImage(L"../Data/Image/Enemy/One/"+ Utility::convertFromString(dataManager->getEnemyData(wave.enemyId[i]).name) + L".png");
		images[i]->GetComponent<D2DFont>()->SetDialog(L"X "+ std::to_wstring(wave.enemyCount[i])); 
	}
	for (int i = size; i < 4; i++) 
	{
		images[i]->SetActive(false);
	}
	auto& loca = transform->relativeLocation;
	new DOTween(loca.x, EasingEffect::OutBack, StepAnimation::StepOnceForward, 3.f, loca.x, WinHalfSizeX);
	
}


