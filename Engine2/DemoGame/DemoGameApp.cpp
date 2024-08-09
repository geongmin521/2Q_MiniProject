#include "pch.h"
#include "DemoGameApp.h"
#include "World.h" 
#include "D2DRenderer.h"
#include "Transform.h"
#include "Music.h"
#include "Factory.h"

#include "BattleWorld.h"
#include "TitleWorld.h"

#include "Map.h"
#include "Camera.h"
#include "Vampire.h"
#include "EnemySpawner.h"
void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);
	Music::soundManager->GetInstance()->Init();
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BGM,true,"../Data/Sound/bonfire.mp3");
	//Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::BGM,Music::eSoundChannel::BGM);

	curWorld = new TitleWorld; //부모라도 하나만 갖는거아니였나? 
	Factory::GetInstance().get()->curWorld = curWorld; //이런거 하나하나일일이 만들기 귀찮으면 씬매니적 만드는게 오히렬편하겠네... 
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

