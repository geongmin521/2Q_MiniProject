#include "pch.h"
#include "DemoGameApp.h"
#include "Music.h"
#include "SceneManager.h"
#include "TitleWorld.h"
#include "IntroWorld.h"



void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);
	Music::soundManager->GetInstance()->Init();
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::GameOver, true, "../Data/Sound/BGM/GameOver.wav");				// bgm
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::GameTheme, true, "../Data/Sound/BGM/Gameplaynight.wav");		// bgm
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::MainTheme, true, "../Data/Sound/BGM/MainMenu.wav");		// bgm
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BatDestroy, false , "../Data/Sound/Enemy/BatDestroy.wav");		// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BatBombDestroy, false , "../Data/Sound/Enemy/BatBombDestroy.mp3");		// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::DeffendDestroy, false , "../Data/Sound/Enemy/DefDestroy.wav");		// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::EnemyDestroy, false , "../Data/Sound/Enemy/EnemyDestroy.wav");		// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Lock, false, "../Data/Sound/Interface/Lock.wav");				// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::UnLock, false, "../Data/Sound/Interface/Unlock.wav");				// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Reward, false, "../Data/Sound/Interface/RewardPopup.mp3");		// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaveStart, false, "../Data/Sound/Interface/WaveStart.wav");	// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerUpgrade, false, "../Data/Sound/Tower/TowerUpgrade.wav");	// effect1 -> 타워가 2성이나 3성으로 소환될때 + 합성할때 소리 나야해서 2번 적기?
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PileHitted, false, "../Data/Sound/Tower/PileHitted.wav");		//  TowerHitted, -> 몬스터랑 겹침
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerHitted, false, "../Data/Sound/Tower/TowerHitted.wav");	// 미구현
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerDestroy, false, "../Data/Sound/Tower/TowerDestroy.wav");	// 미구현
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PileHitted, false, "../Data/Sound/Tower/PileHitted.wav");		// TowerHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerReplace, false, "../Data/Sound/Tower/TowerReplace.mp3");	// effect1 
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::CrossbowAttack, false, "../Data/Sound/Tower/ArrowAttack.mp3");	// TowerAttack
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaterAttack, false, "../Data/Sound/Tower/WaterAttack.mp3");	// TowerAttack
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HiddenAttack, false, "../Data/Sound/Tower/HiddenAttack.mp3");	// TowerAttack
    Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HolyCrossAttack, false, "../Data/Sound/Tower/Heal.mp3");	    // TowerAttack
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::CrossbowEffect, false, "../Data/Sound/Tower/ArrowEffect.mp3");	// TowerEffect
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaterEffect, false, "../Data/Sound/Tower/WaterEffect.mp3");	// TowerEffect
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HiddenEffect, false, "../Data/Sound/Tower/HiddenEffect.wav");	// TowerEffect
	

	SceneManager::GetInstance().get()->ChangeScene(new IntroWorld); //인트로 추가해달래서
} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}

