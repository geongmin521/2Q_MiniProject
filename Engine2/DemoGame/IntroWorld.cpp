#include "pch.h"
#include "IntroWorld.h"
#include "Factory.h"
#include "Image.h"
#include "SceneManager.h"
#include "TitleWorld.h" 
#include "GameManager.h"
IntroWorld::IntroWorld()
{
}

IntroWorld::~IntroWorld()
{
}

void IntroWorld::Update(float deltaTime)
{
	__super::Update(deltaTime);
	elapsedTime += deltaTime;
	if (elapsedTime > 2.0f)
	{
		if(introNum > 1)
			SceneManager::GetInstance().get()->ChangeScene(new TitleWorld);
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
	Make(Image)(L"Intro.png").setPosition(WinHalfSizeXY).Get<Image>(image);
}
