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
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BatDestroy, false , "../Data/Sound/Enemy/BatDestroy.wav");		// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BatBombDestroy, false , "../Data/Sound/Enemy/BatBombDestroy.mp3");		// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::DeffendDestroy, false , "../Data/Sound/Enemy/DefDestroy.wav");		// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Lock, false, "../Data/Sound/Interface/Lock.wav");				// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::UnLock, false, "../Data/Sound/Interface/Unlock.wav");				// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Reward, false, "../Data/Sound/Interface/RewardPopup.mp3");		// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaveStart, false, "../Data/Sound/Interface/WaveStart.wav");	// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerUpgrade, false, "../Data/Sound/Tower/TowerUpgrade.wav");	// effect1 -> 타워가 2성이나 3성으로 소환될때 + 합성할때 소리 나야해서 2번 적기?
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PileHitted, false, "../Data/Sound/Tower/PileHitted.wav");		//  TowerHitted, -> 몬스터랑 겹침
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerReplace, false, "../Data/Sound/Tower/TowerReplace.mp3");	// effect1 
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::CrossbowAttack, false, "../Data/Sound/Tower/ArrowAttack.mp3");	// TowerAttack
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaterAttack, false, "../Data/Sound/Tower/WaterAttack.mp3");	// TowerAttack
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HiddenAttack, false, "../Data/Sound/Tower/HiddenAttack.mp3");	// TowerAttack
    Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HolyCrossAttack, false, "../Data/Sound/Tower/Heal.mp3");	            // TowerAttack
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::CrossbowEffect, false, "../Data/Sound/Tower/ArrowEffect.mp3");	// TowerEffect
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaterEffect, false, "../Data/Sound/Tower/WaterEffect.mp3");	// TowerEffect
	

	SceneManager::GetInstance().get()->ChangeScene(new TitleWorld); 
    SetCustomCursor(hInstance, L"..\\Data\\Image\\2Star.bmp");
    
} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}

void DemoGameApp::SetCustomCursor(HINSTANCE hInstance, std::wstring bitmapPath)
{
    // 비트맵 파일 로드
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, bitmapPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);

    if (hBitmap)
    {
        // 아이콘 정보를 설정
        ICONINFO iconInfo = {};
        iconInfo.fIcon = FALSE; // 커서를 생성
        iconInfo.xHotspot = 0;  // 커서 핫스팟 x 위치 (원하는 값으로 설정)
        iconInfo.yHotspot = 0;  // 커서 핫스팟 y 위치 (원하는 값으로 설정)
        iconInfo.hbmMask = hBitmap;  // 마스크 비트맵 핸들
        iconInfo.hbmColor = hBitmap; // 컬러 비트맵 핸들

        // 커서 생성
        HCURSOR hCursor = CreateIconIndirect(&iconInfo);

        if (hCursor)
        {
            // 커서 설정
            SetCursor(hCursor);

            // 메인 윈도우의 커서를 설정 (메시지 큐가 관리하는 기본 커서를 변경)
            SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
        }

        // 비트맵 해제 (커서를 설정했으므로 더 이상 비트맵이 필요하지 않음)
        DeleteObject(hBitmap);
    }
}

