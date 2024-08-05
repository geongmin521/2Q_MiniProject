#include "../D2DEngine/pch.h"
#include "DemoGameApp.h"
#include "../D2DEngine/World.h" 
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/Music.h"

#include "Map.h"
#include "Camera.h"
#include "ArrowTower.h"
#include "Vampire.h"
#include "EnemySpawner.h"
void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);	 // 윈도우 생성 , Direct2D 초기화
	world->CreateGameObject<ArrowTower>(); 
	world->CreateGameObject<Vampire>();
	world->CreateGameObject<EnemySpawner>();
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BGM,true,"../Data/Sound/bonfire.mp3");
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::BGM,Music::eSoundChannel::BGM);
} 

void DemoGameApp::Run()
{
	Music::soundManager->GetInstance()->SetVolume(10, Music::eSoundChannel::BGM);
	__super::Run();
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}

