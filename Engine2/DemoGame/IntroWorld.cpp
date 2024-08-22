#include "pch.h"
#include "IntroWorld.h"
#include "Factory.h"
#include "Image.h"
#include "SceneManager.h"
#include "BattleWorld.h" 
#include "GameManager.h"
#include "Music.h"
#include "FadeOut.h"
#include "EndingWrold.h"
#include "InputSystem.h"
IntroWorld::IntroWorld()
{
	Music::soundManager->PlayMusic(Music::eSoundList::Intro, Music::eSoundChannel::BGM);
}

IntroWorld::~IntroWorld()
{
}

void IntroWorld::Update(float deltaTime)
{
	__super::Update(deltaTime);
	elapsedTime += deltaTime;
	if (elapsedTime > 4.5f)          //�������� �ѱ�� �ð��� ��ȹ�̶� ���� 
	{
		if (introNum < 3)
		introNum++;
		image->ChangeImage(L"../Data/Image/Intro" + to_wstring(introNum) + L".png");
		elapsedTime = 0;
	}
	
	if (inputSystem->GetMouseButtonDown(0))
	{
		if(introNum <3)
		introNum++;
		image->ChangeImage(L"../Data/Image/Intro" + to_wstring(introNum) + L".png");
		elapsedTime = 0;
	}

	if (introNum >= 3)           //3�� �� ������ ���ڰ� �� ����
	{
		if(elapsedTime > 2.5f)
		SceneManager::GetInstance().get()->ChangeScene(new BattleWorld);
		return;
	}
}

void IntroWorld::MakeObject()
{
	Make(Image)(L"Intro0.png").setPosition(WinHalfSizeXY).Get<Image>(image);
}
