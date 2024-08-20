#include "pch.h"
#include "DemoGameApp.h"
#include "Music.h"
#include "SceneManager.h"
#include "TitleWorld.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);
	Music::soundManager->GetInstance()->Init();
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::GameOver, true, "../Data/Sound/BGM/GameOver.wav");				// bgm
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::MainTheme, true, "../Data/Sound/BGM/Gameplaynight.wav");		// bgm
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BatDestroy, false , "../Data/Sound/Enemy/BatDestroy.wav");		// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Lock, false, "../Data/Sound/Interface/Lock.wav");				// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Reward, false, "../Data/Sound/Interface/RewardPopup.wav");		// effect2
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaveStart, false, "../Data/Sound/Interface/WaveStart.wav");	// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerUpgrade, false, "../Data/Sound/Tower/TowerUpgrade.wav");	// effect2 -> 타워가 2성이나 3성으로 소환될때 + 합성할때 소리 나야해서 2번 적기?
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PileHitted, false, "../Data/Sound/Tower/PileHitted.wav");		// effect2 -> 몬스터랑 겹침

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

