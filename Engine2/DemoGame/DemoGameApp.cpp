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
	__super::Initialize(hInstance, nShowCmd);	 // 윈도우 생성 , Direct2D 초기화
	//여기서는 필요한 월드만 생성해주면되는거지? 
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

