#include "../D2DEngine/pch.h"
#include "DemoGameApp.h"
#include "../D2DEngine/World.h" 
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/Music.h"

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
} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}

