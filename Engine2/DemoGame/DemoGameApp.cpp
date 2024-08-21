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

