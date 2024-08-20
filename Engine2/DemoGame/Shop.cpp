#include "pch.h"
#include "D2DRenderer.h"
#include "Pools.h"
#include "Transform.h"
#include "Factory.h"
#include "Shop.h"
#include "Image.h"
#include "Container.h"
#include "Combination.h"
#include "EnemySpawner.h"
#include "Button.h"
#include "TowerBase.h"
#include "D2DFont.h"
#include "GameManager.h"
#include "Dotween.h"

#include "D2DEffectManager.h"
#include "CrossFadeEffect.h"
Shop::Shop() 
{
	Make(GameObject)().setParent(transform).Get(child);
	ImagePath = { L"Crossbow.png",L"Water.png",L"Pile.png",L"HolyCross.png",L"vampire.png" };
	TowerName = {L"����Ÿ��", L"����Ÿ��", L"����Ÿ��", L"��Ÿ��" };
	Make(Image)(L"BigBack.png").setScale({ 2,2 }).setParent(child->transform);
	float LPad = -200; 
	for (int i = 0; i < 5; i++)//������
		Make(Image)(L"Crossbow.png").setPos_Parent({ LPad + i * 130 , -100 }, child->transform).Get<Image>(Icons);
	for (int i = 0; i < 5; i++)//���� ��ױ�
		Make(Button)(L"smallBack.png", [i, this]() { isLock[i] = !isLock[i]; }).setPos_Parent_Text({ LPad + i * 130, 0 }, child->transform, L"Lock", 20);
	//���� ��ư	 //�������� ���� ���̴ϱ� �̻ڱ��ѵ� �������� ���� ��������..
	//����ǥ Ȯ�� ��ư
	//��ȯ�ϱ� ��ư
	//��ȯ�ϱ� ��ư
	//���� Ƚ�� �ؽ�Ʈ�ڽ�
	//���� Ȱ��ȭ ��ư
	Make(Button)(L"ImageBack.png", std::bind(&Shop::Reroll, this)).setPos_Parent_Text({ LPad + 250, 100 }, child->transform, L"��ü����", 30).GetComponent<D2DFont>(rerollButtonText);
	Make(Button)(L"ImageBack.png", [this]() {combination->SetActive(true); }).setPos_Parent_Text({ LPad + 650, +100 }, child->transform, L"���ս�", 30);
	Make(Button)(L"ImageBack.png", std::bind(&Shop::Spawn, this)).setPos_Parent_Text({ LPad + 650, +200 }, child->transform, L"��ȯ�ϱ�", 30);
	Make(Image)(L"ImageBack.png").setPos_Parent_Text({ LPad + 250, +200 }, child->transform, L"", 20).GetComponent<D2DFont>(compensationText);
	Make(Image)(L"ImageBack.png").setPos_Parent_Text({ LPad + 250, +300 }, child->transform, L"���� ���� Ƚ��" + std::to_wstring(reroll), 20).GetComponent<D2DFont>(rerollText);
	Make(Button)(L"UI.png", []() {}).setPosition(WinSizeXYAdd(-200, -100)).AddText(L"�� ��ȯ", 50).Get<Button>(shop_spawnButton);

	for (int i = 0; i < 4; i++) //Ÿ�� �κ�
		Make(Container)().setPosition({ 100.0f + i * 150, WinSizeY - 100 }).Get<Container>(Containers);
	child->SetActive(false); ChangeButton(ButtonState::TowerSpawn); shop_spawnButton->SetInteractive(true);
}

void Shop::init()
{
	for (int i = 0; i < 5; i++)
	{
		isLock[i] = false;
	}
	reroll = 50;
	rerollText->SetDialog(L"���� ���� Ƚ��" + std::to_wstring(reroll));
}

Shop::~Shop()
{
}

void Shop::Update(float deltaTime) 
{
	if (gameManager->chance <= 0)
		ChangeButton(ButtonState::EnemySpawn);
	else
		ChangeButton(ButtonState::TowerSpawn); 

	for (int i = 0; i < 5; i++)
	{
		//Icons[i]->transform->SetRelativeScale({ test, test}); //Ʈ�������� �װɳѱ�°ͺ��� �̰� �ŷڵ��� ����.. �ٸ����� �������ؼ��׷���? 
	}

	if (curState == ButtonState::EnemySpawn) 
	{
		int count = 0;
		for (int i = 0; i < Containers.size(); i++)
		{
			if (Containers[i]->isContain == false)
				count++;
		}
		if (count == 4 && gameManager->isBattle == false)  //Ÿ���� ���� ����ִ��� �˻�
		{
			shop_spawnButton->SetInteractive(true);	
		}
		else
		{
			shop_spawnButton->SetInteractive(false);
		}
	}
	else if (curState = ButtonState::TowerSpawn)
	{
		if (child->GetActive() == false) //������ �����ִ»��¸� Ȱ��ȭ
			shop_spawnButton->SetInteractive(true);	
	}
	
	if (gameManager->isBattle == true)
	{
		D2DEffectManager::GetInstance()->FindIEffect<CrossFadeEffect>(L"MapFade")->isFadeIn = false;
	}
}

void Shop::Reroll() 
{
	if (reroll <= 0)
		rerollButtonText->SetDialog(L"��ü���� -10 �žӽ�");
	
	if(reroll > 0)
		reroll--;
	else if(gameManager->GetGold() >= 10)
	{
		gameManager->UseGold(10);
	}
	else
		return;

	for (int i = 0; i < Icons.size(); i++) //
	{
		//std::cout << "�ִϸ��̼� ����";
		//new DOTween(test, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.2, 1);
		new DOTween(Icons[i]->transform->relativeScale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.2, 1); //�̰� �� �ȵǴ��� �������ٺ� ����...
		new DOTween(Icons[i]->transform->relativeScale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.2, 1);
	} 
	compensationList.clear();
	Text = L""; //�ؽ�Ʈ �ʱ�ȭ
	
	rerollText->SetDialog(L"���� ���� Ƚ��" +std::to_wstring(reroll));
	for (int i = 0; i < 5; i++)
	{
		if (isLock[i])
			continue;
		int random = Utility::RandomBetween(0, ImagePath.size() - 1);
		Icons[i]->ChangeImage(L"../Data/Image/" + ImagePath[random]);
		Id[i] = random;
	}

	int count[5] = { 0,0,0,0,0 };

	for (auto var : Id)
		count[var]++;

	if (count[0] == 1 && count[1] == 1 && count[2] == 1 && count[3] == 1 && count[4] == 1) //�������� ���������
	{
		Text = L"��� Ÿ�� 1��";
		compensationText->SetDialog(Text);
		compensationList = { 0,3,6,9 };
		return;
	}
	else if (count[4] == 5)//����Ÿ������
	{
		Text = L"����Ÿ��";
		compensationText->SetDialog(Text);
		compensationList = { 12 };
	}

	for (int i = 0; i < 4; i++)
	{
		MakeText(i, count[i]);
	}
	if (Text == L"")
		Text = L"��";
	compensationText->SetDialog(Text);
}

void Shop::Spawn()
{
	int inven = 0;
	for (auto var : compensationList)
	{	
		GameObject* tower = Pools::GetInstance().get()->PopPool(var);  
		if (dynamic_cast<TowerBase*>(tower) != nullptr)
		{
			dynamic_cast<TowerBase*>(tower)->Init(Containers[inven]->transform->GetWorldLocation());
			Containers[inven]->OnDrop(tower); 
		}
		
		inven++;
	}
	compensationList.clear(); 
	child->SetActive(false);
}

void Shop::MakeText(int order, int count)
{	
	if (count == 2)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 0);
		compensationList.push_back(order * 3 + 0);
		Text += L"1��" + TowerName[order] + L"2��"; 
	}
	else if (count == 3)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 1);
		Text += L"2��" + TowerName[order];
	}
	else if (count == 4)
	{
		if (Text != L"")
			Text += L"+";
		compensationList.push_back(order * 3 + 1);
		compensationList.push_back(order * 3 + 1);
		Text += L"2��" + TowerName[order] + L"2��"; 
	}
	else if (count == 5)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 2);
		Text += L"3��" + TowerName[order];
	}
} 

int Shop::TowerNameToID(std::wstring name)
{
	for (int i = 0; i < TowerName.size(); i++)
	{
		if (TowerName[i] == name)
			return i * 3;
	}
}

void Shop::ChangeButton(ButtonState state)
{
	if (curState == state)
		return;
	curState = state;

	if (curState == ButtonState::EnemySpawn)
	{
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"����ȯ");
		shop_spawnButton->SetListener([this]() { gameManager->events[Event::SpawnEnemy](); });
	}
	else if(curState == ButtonState::TowerSpawn) //�̰� �������� ����������?
	{
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"Ÿ����ȯ");
		shop_spawnButton->SetListener([this]() { child->SetActive(true); Reroll(); init(); gameManager->chance--; });
	}	
	shop_spawnButton->SetInteractive(false);
}