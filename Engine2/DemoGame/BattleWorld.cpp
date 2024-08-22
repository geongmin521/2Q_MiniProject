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

#include "D2DFontManager.h"
#include "ProductionCamera.h"

BattleWorld::BattleWorld()
{
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::MainTheme, Music::eSoundChannel::BGM);
	artifact->SelectArtifact(8);
	
}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject()
{
	D2DFontManager::GetInstance()->LoadFont(L"..\\Data\\Font\\Pretendard-Bold.otf", L"Result");

	Make(Image)(L"afternoon.png").setScale({ 0.75f,0.75f }).setRenderOrder(-100).setPosition(WinHalfSizeXY); //효과를 위한 오파시티 맵
	Make(Image)(L"UI/mainUI/MainFrame.png").setScale({ 0.75f,0.75f }).setRenderOrder(-90).setPosition(WinHalfSizeXY); //UI 프레임
	Make(EnemySpawner)();
	Make(Map)();
	MakeUI();
	showWave->Show();
	RegisterEvent();
}

void BattleWorld::MakeUI()
{
	Make(GodStore)().setPosition({ WinHalfSizeXY }).setScale({ 0.75f,0.75f }).Get(Objs["GodStore"]);
	Make(Button)(L"Pause", [this]() {timeManager->SetTimeScale(0); TimeScaleIsClick(0); }, ButtonType::Active).setPosition({ WinSizeX - 330, 75 }).Get(TimeScaleButton[0]); //시간 조절 버튼
	Make(Button)(L"Resume",[this]()  {timeManager->SetTimeScale(1); TimeScaleIsClick(1); }, ButtonType::Active).setPosition({ WinSizeX - 210, 75 }).Get(TimeScaleButton[1]);
	Make(Button)(L"Multi",[this]() {timeManager->SetTimeScale(2); TimeScaleIsClick(2); }, ButtonType::Active).setPosition({ WinSizeX - 90, 75 }) .Get(TimeScaleButton[2]);
	TimeScaleButton[0]->SetIsEnable(false);
	TimeScaleButton[2]->SetIsEnable(false);

	Make(Combination)().setScale({0.75,0.75}).setPosition(WinHalfSizeXY).Get(Objs["Combination"]);
	Make(Shop)().setPosition(WinHalfSizeXY).setScale({ 0.75f,0.75f }).Get<Shop>(shop);  shop->SetOtherUI(Objs["Combination"]);
	Make(ShowWave)().setPosition(WinHalfSizeXY).setScale({ 0.75f,0.75f }).Get<ShowWave>(showWave); //UI 패널들을 다시모아도될거같기도하고.. 
	Make(Compensation)().setPosition(WinHalfSizeXY).setScale({ 0.75f,0.75f }).Get(Objs["Compensation"]);
	Make(Button)(L"Create", [this]() { Objs["Combination"]->SetActive(true); }).setPosition(WinSizeXYAdd(-600, -100)); //조합식
	Make(GameOver)().setPosition({ WinHalfSizeXY }).setScale({ 0.75f,0.75f }).Get(Objs["GameOver"]);
	Make(Image)(L"UI/tooltip/HolyCrossTower.png").setActive(false).Get(Objs["ToolTip"]);
	Make(Image)(L"UI/mainUI/gauge0.png").setScale({0.75,0.75}).setPosition({ WinHalfSizeX , 65 }).Get(Objs["WaveCount"]); //웨이브 주기.. 
	Make(ProductionCamera)().Get()->name = "Camera";

	 Make(Image)(L"UI/mainUI/Special_inven.png").setScale({ 0.5 , 0.5 }).setPosition({ 1280, 350 }).AddText(L"크하하하", 50,0,0, &BossDialogue).Get()->name = "BossDialogue";
	 BossDialogue->SetBoxSize(400, 200);
	 FindObject<Image>("BossDialogue")->SetActive(false);
}

void BattleWorld::RegisterEvent()
{
	gameManager->events[Event::EndWave] = [this]() { //웨이브 종료시 함수
		shop->GetSwapButton()->SetInteractive(true);
		shop->init();
		gameManager->chance = 1;
		shop->ChangeButton(ButtonState::TowerSpawn);
		Objs["WaveCount"]->GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/UI/mainUI/gauge"+std::to_wstring(gameManager->WaveLevel) + L".png");
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
	//};
	gameManager->events[Event::OpenGodStore] = [this]() {Objs["GodStore"]->SetActive(true); };
	gameManager->events[Event::UseGold] = [this]() { goldText->SetDialog(L"신앙심:" + std::to_wstring(gameManager->GetGold())); };
	gameManager->Compensation = [this](bool special) { Objs["Compensation"]->SetActive(true); };
	gameManager->getObject = [this](std::string key) { return Objs[key]; };
}
void BattleWorld::TimeScaleIsClick(int num)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == num)
			continue;
		TimeScaleButton[i]->SetIsEnable(false);
	}
}

void BattleWorld::Update(float deltaTime)
{
	__super::Update(deltaTime);
	gameManager->Update();	
}

void BattleWorld::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
