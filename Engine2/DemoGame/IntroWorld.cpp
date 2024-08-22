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
	if (elapsedTime > 1.3f)          //�������� �ѱ�� �ð��� ��ȹ�̶� ���� 
	{
		if (introNum >= 3)           //3�� �� ������ ���ڰ� �� ����
		{
			SceneManager::GetInstance().get()->ChangeScene(new TitleWorld);
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
	Make(Image)(L"Intro.png").setPosition(WinHalfSizeXY).Get<Image>(image);
}
