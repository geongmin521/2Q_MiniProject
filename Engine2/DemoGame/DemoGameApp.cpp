#include "pch.h"
#include "DemoGameApp.h"
#include "Music.h"
#include "SceneManager.h"
#include "TitleWorld.h"



void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);
	Music::soundManager->GetInstance()->Init();
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::GameOver, true, "../Data/Sound/BGM/GameOver.wav");
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::MainTheme, true, "../Data/Sound/BGM/Gameplaynight.wav");
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BatDestroy, false , "../Data/Sound/Enemy/BatDestroy.wav");
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Lock, false, "../Data/Sound/Interface/Lock.wav");
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Reward, false, "../Data/Sound/Interface/RewardPopup.wav");
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaveStart, true, "../Data/Sound/Interface/WaveStart.wav");
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerUpgrade, false, "../Data/Sound/Tower/TowerUpgrade.wav");
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PileHitted, false, "../Data/Sound/Tower/PileHitted.wav");

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

