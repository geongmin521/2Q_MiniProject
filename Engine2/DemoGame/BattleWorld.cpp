#include "pch.h"
#include "BattleWorld.h"
#include "Camera.h"
#include "Button.h"
#include "MoveIcon.h"
#include "Factory.h"
#include "Shop.h"
#include "ShowWave.h"
#include "Combination.h"
#include "Container.h"
#include "TimeSystem.h"
#include "DataManager.h"
#include "Transform.h"
#include "EnemySpawner.h"
#include "GameManager.h"
#include "Image.h"
#include "Map.h"
#include "D2DFont.h"
#include "GameOver.h"
#include "CollisionManager.h"
#include "InputSystem.h"

#include "Light.h" // ����Ʈ �׽�Ʈ


BattleWorld::BattleWorld()
{
}

BattleWorld::~BattleWorld()
{
}

void BattleWorld::MakeObject() //������ ��ǥ�����͵鵵 csv�� �����Ҽ���������? 
{
	Factory().createObj<Image>(L"afternoon.png").setRenderOrder(-100).setPosition(WinHalfSizeXY); // �׽�Ʈ�� ������ //���̰�.. �ʿ��� �׸��°� �ƴ϶� �׳� �̹������س�����.. 
	spwaner = Factory().createObj<EnemySpawner>().Get<EnemySpawner>(); 
	Factory().createObj<Map>();
	MakeUI();

	DataManager::GetInstance().get()->ChoseWave();
	showWave->Show(); 
}

void BattleWorld::MakeUI() //�տ� ��δ� �������������ϱ� ������ ó������.. 
{
	WaveCount = Factory().createObj<Image>(L"UI.png").setPosition({ WinHalfSizeX, 100 }).AddText(L"Wave 1", 40).Get<Image>(); //wave //���̺� ������ �Ϲ� �̹����δ�����ϱ� showwave���� �ѱ���. 
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(0); }).setPosition({ WinSizeX - 400, 200 }); //�ð� ���� ��ư
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(1); }).setPosition({ WinSizeX - 300, 200 });
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(2); }).setPosition({ WinSizeX - 200, 200 });

	for (int i = 0; i < 4; i++) //Ÿ�� �κ�
	{
		TowerInventory.push_back(Factory().createObj<Container>().setPosition({ 100.0f + i * 150, WinSizeY - 100 }).Get<Container>());
	}
		
	combination = Factory().createObj<Combination>().Get<Combination>();
	shop = Factory().createObj<Shop>().Get<Shop>(); shop->SetOtherUI(TowerInventory, combination); shop->spawner = spwaner;//������ ������ ��������ʿ����
	showWave = Factory().createObj<ShowWave>().Get<ShowWave>();
	
	Factory().createObj<Button>(L"UI.png", [this]() { combination->SetActive(true); }).setPosition({ WinSizeX - 600, WinSizeY - 100 }).AddText(L"���ս�", 50); //����ǥ����
	shop_spawnButton = Factory().createObj<Button>(L"UI.png", []() {}).setPosition({ WinSizeX - 200, WinSizeY - 100 }).AddText(L"�� ��ȯ", 50).Get<Button>();
	//�ϴ� ������.. �Լ��� �Ҵ����ֱ�.. 
	//gameManager->ShowWave = [this]() { showWave->Show(); }; 
	gameManager->EndWave = [this]() { 
		shop_spawnButton->SetInteractive(true); 
		WaveCount->GetComponent<D2DFont>()->SetDialog(L"Wave " + std::to_wstring(gameManager->WaveLevel)); 
		showWave->Show();
		shop->init();
	}; //���̺갡������ �ʿ��� �Լ����� ����� �����س���..
	gameManager->GameClear = []() { Factory().createObj<GameOver>(); }; //�̱��� init���� �ʱ�ȭ�� ���ѹ������ҵ�? 
	ChangeButton();
	shop_spawnButton->SetInteractive(true); //ó������ �ϴܰ����ϰ�
	//gameManager->GameClear();

} 

void BattleWorld::ChangeButton() //���⼱ ���״�� ��ɸ� �ٲ��ְ�.. �������� ���ٽ����� ����ִ°ɷΰ���... 
{
	if (Swap)
	{
		shop_spawnButton->SetListener([this]() { spwaner->StartWave(); ChangeButton(); }); //�������� �̰� �ñ��ȵǳ�? 
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"����ȯ");
	}
	else
	{
		shop_spawnButton->SetListener([this]() { shop->SetActive(true); ChangeButton(); });
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"Ÿ����ȯ");
	}
	Swap = !Swap;
	shop_spawnButton->SetInteractive(false); //�̰� ���ͷ�Ƽ�긦 ����������ϴµ�.. �̰� ���ӸŴ������� �ñ�°� �³�? �ƴϸ�? ������ ������Ʈ�� ������������? �׳�? //�̰� ������Ʈ�� ������Ʈ�δ� �����ϰŰ�����.. 
}

void BattleWorld::Update(float deltaTime) //�������� �Ը��� ������ ��ü�������δ� ó�������µ� �̰� �´°ɱ�?  
{
	__super::Update(deltaTime);
	gameManager->Update(); //������Ʈ�� ��Ʋ�߿��� �������ҵ�? 
	if (Swap == false) //���� ����ȯ��ư�̸鼭, ��Ȱ��ȭ �����϶�. 
	{
		int count=0;
		for (int i = 0; i < TowerInventory.size(); i++)
		{
			if (TowerInventory[i]->isContain == false)
				count++;
		}
		if (count == 4) //���� ��������� Ȱ��ȭ
		{
			shop_spawnButton->SetInteractive(true);
		}
		else
		{
			shop_spawnButton->SetInteractive(false); //�ϴ� �̷��� ������ ¥���� ���߿� ��ġ�� �ð�����
		}		
	}

	if (InputSystem::GetInstance()->isKeyDown('K'))
	{
		gameManager->LiveEenmy = 0;
		gameManager->isBattle = true;
	}
}

void BattleWorld::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
