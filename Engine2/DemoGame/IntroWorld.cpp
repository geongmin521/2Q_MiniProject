#include "pch.h"
#include "IntroWorld.h"
#include "Factory.h"
#include "Image.h"
#include "SceneManager.h"
#include "TitleWorld.h" 
#include "BattleWorld.h" 
#include "GameManager.h"
#include "Music.h"
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
	if (elapsedTime > 0.3f)          //�������� �ѱ�� �ð��� ��ȹ�̶� ���� 
	{
		if (introNum >= 3)           //3�� �� ������ ���ڰ� �� ����
		{
			SceneManager::GetInstance().get()->ChangeScene(new BattleWorld);
			return;
		}			
		else
		{
			introNum++;
			image->ChangeImage(L"../Data/Image/Intro" + to_wstring(introNum) + L".png");
		}
		elapsedTime = 0;
	}
	
	
}

void IntroWorld::MakeObject()
{
	Make(Image)(L"Intro0.png").setPosition(WinHalfSizeXY).Get<Image>(image);
}
