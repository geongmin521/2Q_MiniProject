#include "pch.h"
#include "BattleWorld.h"
#include "Factory.h"
#include "D2DFont.h"
#include "GameManager.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "Pools.h"

#include "EnemySpawner.h" //이게 가지고있어야하는 구체클래스.. 팩토리한테 전부 넘기고싶은데 방법을모르겠네.. 
#include "Button.h"
#include "Image.h"
#include "Map.h"
#include "GameOver.h"
#include "Compensation.h"
#include "GodStore.h"
#include "Shop.h"
#include "ShowWave.h"
#include "Combination.h"
#include "Container.h"
#include "Light.h" // 라이트 테스트
#include "Artifact.h"
#include "TowerBase.h"
#include "Music.h"

#include "D2DFontManager.h"

BattleWorld::BattleWorld()
{
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::MainTheme, Music::eSoundChannel::BGM);
}

BattleWorld::~BattleWorld()
{
}

void BattleWorld::MakeObject()
{
	D2DFontManager::GetInstance()->LoadFont(L"..\\Data\\Font\\DNFBitBitv2.ttf", L"Test");
	D2DFontManager::GetInstance()->LoadFont(L"..\\Data\\Font\\Maplestory Bold.ttf", L"Map");

	Make(Image)(L"afternoon.png").setScale({ 0.75f,0.75f }).setRenderOrder(-100).setPosition(WinHalfSizeXY); //효과를 위한 오파시티 맵
	Make(EnemySpawner)();
	Make(Map)();
	MakeUI();
	showWave->Show();
	RegisterEvent();
}

void BattleWorld::MakeUI()//샵 빼고 여기서 어떤 기능 필요한지 분석한다음에. 헤더도 정리가능할듯? 여기가 이뻐지고 나면 끝인가? 다른 코드는 괜찮나?
{
	Make(GodStore)().setPosition({ WinHalfSizeXY }).Get(Objs["GodStore"]);//성역상점 이미지 교체 필요
	Make(Button)(L"smallBack.png", [this]() { if (gameManager->isBattle == false) Objs["GodStore"]->SetActive(true); }).setPosition({ 100, WinHalfSizeY }); //성역상점 버튼
	Make(Image)(L"UI.png").setPosition({ WinHalfSizeX, 100 }).AddText(L"Wave 1", 40).GetComponent<D2DFont>(WaveCount); //웨이브카운트
	Make(Image)(L"UI.png").setPosition({ WinSizeX - 100, 100 }).AddText(L"신앙심 : 0", 40).GetComponent<D2DFont>(goldText); //보유재화
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(0); }).setPosition({ WinSizeX - 400, 200 }); //시간 조절 버튼
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(1); }).setPosition({ WinSizeX - 300, 200 });
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(2); }).setPosition({ WinSizeX - 200, 200 });
	Make(Shop)().setPosition(WinHalfSizeXY).Get<Shop>(shop);  shop->SetOtherUI(Objs["Combination"]);
	Make(ShowWave)().setPosition({ WinHalfSizeX+1200,WinHalfSizeY}).Get<ShowWave>(showWave); //UI 패널들을 다시모아도될거같기도하고.. 


	Make(Combination)().setPosition (WinHalfSizeXY).Get(Objs["Combination"]);
	Make(Compensation)().setPosition(WinHalfSizeXY).Get(Objs["Compensation"]);
	Make(Button)(L"UI.png", [this]() { Objs["Combination"]->SetActive(true); }).setPosition(WinSizeXYAdd(-600, -100)).AddText(L"조합식", 50); //조합식
	Make(GameOver)().setPosition({ WinHalfSizeXY }).Get(Objs["GameOver"]);
	//Make(Light)();
}

void BattleWorld::RegisterEvent()
{
	gameManager->events[Event::EndWave] = [this]() { //웨이브 종료시 함수
		shop->GetSwapButton()->SetInteractive(true);
		shop->init();
		gameManager->chance = 1;
		shop->ChangeButton(ButtonState::TowerSpawn);
		WaveCount->SetDialog(L"Wave " + std::to_wstring(gameManager->WaveLevel));
		if (gameManager->WaveLevel == 3 || gameManager->WaveLevel == 6)
		{
			Objs["Compensation"]->SetActive(true);
		}
		else
		{
			showWave->Show();
		}
		for (auto& it : m_GameObjects)
		{
			if (it && it->name == "Tower")
			{
				TowerBase* tower = dynamic_cast<TowerBase*>(it);

				if (tower)
				{
					if (tower->curHP <= 0)
					{
						tower->prevHp = tower->towerData.HP;
					}
					tower->curHP = tower->prevHp;
					tower->StatUpdate();
				}
			}
		}

		};
	gameManager->events[Event::GameOverEvent] = [this]() {Objs["GameOver"]->SetActive(true);
	Music::soundManager->StopMusic(Music::eSoundChannel::BGM); };
	//Music::soundManager->PlayMusic(Music::eSoundList::GameOver, Music::eSoundChannel::BGM); };
	gameManager->events[Event::UseGold] = [this]() { goldText->SetDialog(L"신앙심:" + std::to_wstring(gameManager->GetGold())); };
	gameManager->events[Event::Reset] = [this]() { Pools::GetInstance().get()->reset(); };//또 싱글톤이면서 이전게임의 데이터를 담고있는애가있나? 
} 

void BattleWorld::Update(float deltaTime)
{
	__super::Update(deltaTime);
	gameManager->Update();	
	goldText->SetDialog(L"신앙심 :" + std::to_wstring(gameManager->GetGold())); // 실시간 적용을 위해 일단 추가해놓음
}

void BattleWorld::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
