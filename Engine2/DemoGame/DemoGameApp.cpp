#include "pch.h"
#include "DemoGameApp.h"
#include "World.h" 
#include "D2DRenderer.h"
#include "Transform.h"
#include "Music.h"
#include "Factory.h"
#include "SceneManager.h"

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
	SceneManager::GetInstance().get()->ChangeScene(new TitleWorld); 

} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}

