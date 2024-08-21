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
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerUpgrade, false, "../Data/Sound/Tower/TowerUpgrade.wav");	// effect1 -> Ÿ���� 2���̳� 3������ ��ȯ�ɶ� + �ռ��Ҷ� �Ҹ� �����ؼ� 2�� ����?
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PileHitted, false, "../Data/Sound/Tower/PileHitted.wav");		//  TowerHitted, -> ���Ͷ� ��ħ
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
    // ��Ʈ�� ���� �ε�
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, bitmapPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);

    if (hBitmap)
    {
        // ������ ������ ����
        ICONINFO iconInfo = {};
        iconInfo.fIcon = FALSE; // Ŀ���� ����
        iconInfo.xHotspot = 0;  // Ŀ�� �ֽ��� x ��ġ (���ϴ� ������ ����)
        iconInfo.yHotspot = 0;  // Ŀ�� �ֽ��� y ��ġ (���ϴ� ������ ����)
        iconInfo.hbmMask = hBitmap;  // ����ũ ��Ʈ�� �ڵ�
        iconInfo.hbmColor = hBitmap; // �÷� ��Ʈ�� �ڵ�

        // Ŀ�� ����
        HCURSOR hCursor = CreateIconIndirect(&iconInfo);

        if (hCursor)
        {
            // Ŀ�� ����
            SetCursor(hCursor);

            // ���� �������� Ŀ���� ���� (�޽��� ť�� �����ϴ� �⺻ Ŀ���� ����)
            SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
        }

        // ��Ʈ�� ���� (Ŀ���� ���������Ƿ� �� �̻� ��Ʈ���� �ʿ����� ����)
        DeleteObject(hBitmap);
    }
}

