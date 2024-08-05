#include "../D2DEngine/pch.h"
#include "DemoGameApp.h"
#include "../D2DEngine/World.h" 
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/Music.h"
#include "../D2DEngine/Factory.h"

#include "BattleWorld.h"
#include "TitleWorld.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);	 // ������ ���� , Direct2D �ʱ�ȭ
	//���⼭�� �ʿ��� ���常 �������ָ�Ǵ°���? 
	Music::soundManager->GetInstance()->Init();
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BGM,true,"../Data/Sound/bonfire.mp3");
	//Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::BGM,Music::eSoundChannel::BGM);

	curWorld = new TitleWorld; //�θ�� �ϳ��� ���°žƴϿ���? 
	Factory::GetInstance().get()->curWorld = curWorld; //�̷��� �ϳ��ϳ������� ����� �������� ���Ŵ��� ����°� ���������ϰڳ�... 
	curWorld->MakeObject();
} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}

void DemoGameApp::ChangeCurWorld(World* world)
{
	curWorld = world;
	Factory::GetInstance().get()->curWorld = curWorld;
	curWorld->MakeObject();
}

