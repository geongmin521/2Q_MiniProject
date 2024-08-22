#include "pch.h"
#include "Factory.h"
#include "ShowWave.h"
#include "Image.h"
#include "Button.h"
#include "DataManager.h"
#include "GameManager.h"
#include "DOTween.h"
#include "Transform.h"
#include "D2DFontManager.h"
#include "D2DFont.h"
#include "Music.h"

ShowWave::ShowWave()
{
	renderOrder += 100;
	float LPad = -600;
	//���
	//���������
	//�����ư
	Make(Image)(L"UI/Pop_up/popup_Round.png").AddText(L"",50,0, -165).setParent(this->transform).GetComponent<D2DFont>(text);
	for (int i = 0; i < 4; i++)	
		Make(Image)(L"Enemy/One/NormalEnemy.png").setPos_Parent({LPad + i * 400 ,0}, transform).AddText(L"", 70,0,95).Get<Image>(images[i]);		
	Make(Button)(L"Ready", [this]() { SetActive(false); 
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect1);	}).setPos_Parent({ 0, 387 }, transform);
	SetActive(false);
}

ShowWave::~ShowWave()
{

}

void ShowWave::Update(float deltatime)
{
	__super::Update(deltatime);
	
	elapsedTime += deltatime;
	if (!isMid && elapsedTime >= 2.3f)
	{
		isMid = true; //�߾ӿ� �Դٰ��ϸ� 3�ʴ���� 
		elapsedTime = 0;
	}
	
	if (isMid && !isExit && elapsedTime >= middleTime)
	{
		isExit = true;
		auto& loca = transform->relativeLocation;
		elapsedTime = 0;
		new DOTween(loca.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 4.f, loca.x, loca.x- 2000);
	}

	if (isMid && isExit && elapsedTime >= 5.0f)
	{
		SetActive(false);
		elapsedTime = 0;
	}
	
}


void ShowWave::Show()  
{
	Music::soundManager->PlayMusic(Music::eSoundList::WaveStart, Music::eSoundChannel::Effect1);
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
	text->SetDialog(to_wstring(gameManager->WaveLevel));

	auto& loca = transform->relativeLocation;
	new DOTween(loca.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 3.f, loca.x, WinHalfSizeX);
	
}


