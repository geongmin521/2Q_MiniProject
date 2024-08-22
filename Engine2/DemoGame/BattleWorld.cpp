#include "pch.h"
#include "BattleWorld.h"
#include "Factory.h"
#include "D2DFont.h"
#include "GameManager.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "EventSystem.h"
#include "Transform.h"
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
#include "EndingWrold.h"
#include "FadeOut.h"
#include "SceneManager.h"
#include "D2DFontManager.h"
#include "ProductionCamera.h"
#include "InputSystem.h"
BattleWorld::BattleWorld()
{
	// 낮 밤 바뀌는거 물어볼 것 따로 변수가 있는지?
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::GameTheme, Music::eSoundChannel::BGM);
	timeManager->SetTimeScale(2);
}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject()
{
	D2DFontManager::GetInstance()->LoadFont(L"..\\Data\\Font\\Pretendard-Bold.otf", L"Result");

	Make(Image)(L"afternoon.png").setScale({ 0.75f,0.75f }).setRenderOrder(-100).setPosition(WinHalfSizeXY); //효과를 위한 오파시티 맵
	Make(Image)(L"UI/mainUI/MainFrame.png").setScale({ 0.75f,0.75f }).AddText(L"0", 60,-430,262).setRenderOrder(-90).setPosition(WinHalfSizeXY).GetComponent<D2DFont>(goldText); //UI 프레임
	Make(EnemySpawner)();
	Make(Map)();
	MakeUI();
	showWave->Show();
	RegisterEvent();
}

void BattleWorld::MakeUI()
{
	Make(GodStore)().setPosition({ WinHalfSizeXY }).setScale({ 0.75f,0.75f }).Get(Objs["GodStore"]);
	Make(Button)(L"Pause", [this]() {timeManager->SetTimeScale(0); TimeScaleIsClick(0);
	Music::soundManager->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect1);
	Music::soundManager->SetPause(Music::eSoundChannel::BGM, true);
		}, ButtonType::Single).setPosition({ WinSizeX - 330, 75 }).Get(TimeScaleButton[0]); //시간 조절 버튼
	Make(Button)(L"Resume", [this]() {timeManager->SetTimeScale(2); TimeScaleIsClick(1), timeManager->SetBeforeTimeScale(2);
	Music::soundManager->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect1);
	Music::soundManager->SetPause(Music::eSoundChannel::BGM, false);
		}, ButtonType::Single).setPosition({ WinSizeX - 210, 75 }).Get(TimeScaleButton[1]);
	Make(Button)(L"Multi", [this]() {timeManager->SetTimeScale(3); TimeScaleIsClick(2), timeManager->SetBeforeTimeScale(3);
	Music::soundManager->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect1);
	Music::soundManager->SetPause(Music::eSoundChannel::BGM, false);
		}, ButtonType::Single).setPosition({ WinSizeX - 90, 75 }).Get(TimeScaleButton[2]);


	TimeScaleButton[0]->SetIsEnable(false);
	TimeScaleButton[2]->SetIsEnable(false);

	Make(Combination)().setScale({ 0.75,0.75 }).setPosition(WinHalfSizeXY).Get(Objs["Combination"]);
	Make(Shop)().setPosition(WinHalfSizeXY).setScale({ 0.75f,0.75f }).Get<Shop>(shop);  shop->SetOtherUI(Objs["Combination"]);
	Make(ShowWave)().setPosition(WinHalfSizeXY).setScale({ 0.75f,0.75f }).Get<ShowWave>(showWave); //UI 패널들을 다시모아도될거같기도하고.. 
	Make(Compensation)().setPosition(WinHalfSizeXY).setScale({ 0.75f,0.75f }).Get(compensation);
	Make(Button)(L"Recipe", [this]() {
		Objs["Combination"]->SetActive(true);
		Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::PopupOpen, Music::eSoundChannel::Effect1);
		}).setScale({ 0.9,0.9 }).setPosition(WinSizeXYAdd(-600, -100)); //조합식
	Make(GameOver)().setPosition({ WinHalfSizeXY }).setScale({ 0.75f,0.75f }).Get(Objs["GameOver"]);
	Make(Image)(L"UI/tooltip/HolyCrossTower.png").setScale({ 0.65f,0.65f }).setActive(false).setBoundBox(0, 0).Get(Objs["ToolTip"]);
	Make(Image)(L"UI/mainUI/gauge0.png").setScale({ 0.75,0.75 }).setPosition({ WinHalfSizeX , 65 }).Get(Objs["WaveCount"]); //웨이브 주기.. 
	Make(ProductionCamera)().Get()->name = "Camera";

	Make(Image)(L"UI/boss_speech.png").setScale({ 1.0 , 1.0 }).setPosition({ 1320, 370 }).Get()->name = "BossDialogue";
	FindObject<Image>("BossDialogue")->SetActive(false);
}

void BattleWorld::RegisterEvent()
{
	gameManager->events[Event::EndWave] = [this]() { //웨이브 종료시 함수

		shop->GetSwapButton()->SetInteractive(true);
		shop->init();
		gameManager->chance = 1;
		shop->ChangeButton(ButtonState::TowerSpawn);
		compensation->showonce = true;
		Objs["WaveCount"]->GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/UI/mainUI/gauge" + std::to_wstring(gameManager->WaveLevel) + L".png");

		if (gameManager->WaveLevel == 3 || gameManager->WaveLevel == 6)
			gameManager->Compensation(true);
		else
			gameManager->Compensation(false);

		for (auto& it : m_GameObjects)
		{
			if (it && it->name == "Tower")
			{
				TowerBase* tower = dynamic_cast<TowerBase*>(it);

				if (tower)
				{
					if (tower->curHP <= 0)
					{
						tower->curHP = tower->maxHP;
					}
					tower->prevHp = tower->curHP;
					tower->StatUpdate();
				}
			}
		}
		goldText->SetDialog(std::to_wstring(gameManager->GetGold()));
	};
	gameManager->events[Event::GameClearEvent] = [this]() {Make(FadeOut)([]() {SceneManager::GetInstance().get()->ChangeScene(new EndingWrold); }, true); };
	gameManager->events[Event::GameOverEvent] = [this]() {Objs["GameOver"]->SetActive(true);
	Music::soundManager->PlayMusic(Music::eSoundList::NexusDestroy, Music::eSoundChannel::Effect2);
	Music::soundManager->PlayMusic(Music::eSoundList::GameOver, Music::eSoundChannel::BGM);
		};
	gameManager->events[Event::OpenGodStore] = [this]() {Objs["GodStore"]->SetActive(true);
	Music::soundManager->PlayMusic(Music::eSoundList::RewardOpen, Music::eSoundChannel::Effect1); };
	gameManager->events[Event::UseGold] = [this]() { goldText->SetDialog(std::to_wstring(gameManager->GetGold())); };
	gameManager->events[Event::ShowWaveFunc] = [this]() { showWave->Show(); };
	gameManager->Compensation = [this](bool special) { compensation->ChoseCompensation(special); compensation->SetActive(true); };
	gameManager->getObject = [this](std::string key) { return Objs[key]; };
}
void BattleWorld::TimeScaleIsClick(int num)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == num)
		{
			TimeScaleButton[i]->SetIsEnable(true);
			continue;
		}
		else
		{
			TimeScaleButton[i]->SetIsEnable(false);
		}
	}
}

void BattleWorld::Update(float deltaTime)
{
	__super::Update(deltaTime);
	
	gameManager->Update();
	if (compensation->isSelect == true)
	{
		for (auto& it : m_GameObjects)
		{
			if (it && it->name == "Tower")
			{
				TowerBase* tower = dynamic_cast<TowerBase*>(it);
				if (tower)
				{
					tower->AbilityUpdate();
				}
			}

		}
	}

	if (inputSystem->isKeyDown(VK_F8))
	{
		gameManager->gold += 100;
		goldText->SetDialog(std::to_wstring(gameManager->GetGold()));
	}
}

void BattleWorld::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
