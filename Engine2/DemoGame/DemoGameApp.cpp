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
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::GameOver, true, "../Data/Sound/BGM/GameOver.wav");							// bgm X
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::GameTheme, true, "../Data/Sound/BGM/Gameplaynight.wav");					// bgm
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::MainTheme, true, "../Data/Sound/BGM/MainMenu.wav");						// bgm
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BossWave, true, "../Data/Sound/BGM/BossWave.wav");							// bgm  ���� ���忬��� �Ұ�
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Ending, true, "../Data/Sound/BGM/Ending.wav");								// bgm  ����?
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BatDestroy, false , "../Data/Sound/Enemy/BatDestroy.wav");					// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BatBombDestroy, false , "../Data/Sound/Enemy/BatBombDestroy.mp3");			// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::DeffendDestroy, false , "../Data/Sound/Enemy/DefDestroy.wav");				// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::EnemyDestroy, false , "../Data/Sound/Enemy/EnemyDestroy.wav");				// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BossSummon, false , "../Data/Sound/Enemy/BossSummon.wav");					// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BossAttack, false , "../Data/Sound/Enemy/BossAttack.wav");					// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BossAppear, false , "../Data/Sound/Enemy/BossAppear.wav");					// ���� ���忬�� �ÿ�? �ƴϸ� �׳�? X
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::BossDestroy, false , "../Data/Sound/Enemy/BossDestroy.wav");				// EnemyHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Lock, false, "../Data/Sound/Interface/Lock.wav");							// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::UnLock, false, "../Data/Sound/Interface/Unlock.wav");						// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::RewardClose, false, "../Data/Sound/Interface/RewardClose.wav");			// effect2	
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::RewardOpen, false, "../Data/Sound/Interface/RewardOpen.wav");				// effect1	
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Reroll, false, "../Data/Sound/Interface/Reroll.wav");						// effect1	
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PopupClose, false, "../Data/Sound/Interface/PopupClose.wav");				// effect1	
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PopupOpen, false, "../Data/Sound/Interface/PopupOpen.wav");				// effect1	
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::MainButtonClick, false, "../Data/Sound/Interface/MainButtonClick.wav");	// effect1	
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::ButtonClick, false, "../Data/Sound/Interface/ButtonClick.wav");			// �Ϻα���	�ٳֱ�
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::NexusDestroy, false, "../Data/Sound/Interface/NexusDestroy.wav");			// TowerHitted	
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaveStart, false, "../Data/Sound/Interface/WaveStart.wav");				// effect1
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Tower1Star, false, "../Data/Sound/Interface/Tower1Star.wav");				// �̱��� �ϴ� ������
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Tower2Star, false, "../Data/Sound/Interface/Tower2Star.wav");				// �̱��� �ϴ� ������
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::Tower3Star, false, "../Data/Sound/Interface/Tower3Star.wav");				// �̱��� �ϴ� ������
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PileHitted, false, "../Data/Sound/Tower/PileHitted.wav");					//  TowerHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerHitted, false, "../Data/Sound/Tower/TowerHitted.wav");				// TowerHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerDestroy, false, "../Data/Sound/Tower/TowerDestroy.wav");				// TowerHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::PileHitted, false, "../Data/Sound/Tower/PileHitted.wav");					// TowerHitted
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::TowerReplace, false, "../Data/Sound/Tower/TowerReplace.wav");				// effect1 
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HiddenSummon, false, "../Data/Sound/Tower/HiddenSummon.wav");				// effect1 
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::CrossbowAttack, false, "../Data/Sound/Tower/ArrowAttack.mp3");				// TowerAttack		������ wav���� ����
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaterAttack, false, "../Data/Sound/Tower/WaterAttack.wav");				// TowerAttack
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HiddenAttack, false, "../Data/Sound/Tower/HiddenAttack.wav");				// TowerAttack
    Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HolyCrossAttack, false, "../Data/Sound/Tower/Heal.wav");					// TowerAttack
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::CrossbowEffect, false, "../Data/Sound/Tower/ArrowEffect.wav");				// TowerEffect
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::WaterEffect, false, "../Data/Sound/Tower/WaterEffect.wav");				// TowerEffect
	Music::soundManager->GetInstance()->LoadMusic(Music::eSoundList::HiddenEffect, false, "../Data/Sound/Tower/HiddenEffect.wav");				// TowerEffect
	

	SceneManager::GetInstance().get()->ChangeScene(new IntroWorld); //��Ʈ�� �߰��ش޷���
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

