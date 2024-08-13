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
#include "D2DFont.h"

Shop::Shop() //얘한테 매개변수로 하나 넘겨줄까? 
{
	ImagePath = { L"Crossbow.png",L"Water.png",L"Pile.png",L"HolyCross.png",L"vampire.png" };//태그를 만들게 되면 이걸쓸듯? 아몰라.. 바뀔수도있는거지.. 
	TowerName = {L"석궁타워", L"성수타워", L"말뚝타워", L"힐타워" };

	renderOrder = 80;
	Factory().createObj<Image>(L"BigBack.png").setPosition(WinHalfSizeXY).setScale({ 2,2 }).setParent(this->transform);
	float LeftPadding = 700; 
	for (int i = 0; i < 5; i++)//아이콘
		Icons.push_back(Factory().createObj<Image>(L"Crossbow.png").setPosition({ LeftPadding + i * 130 ,WinHalfSizeY - 200 }).setParent(this->transform).Get<Image>());
	for (int i = 0; i < 5; i++)//리롤 잠그기
		Factory().createObj<Button>(L"smallBack.png", [i, this]() { isLock[i] = !isLock[i]; }).setPosition({ LeftPadding + i * 130, WinHalfSizeY - 100 }).setParent(this->transform).AddText(L"Lock", 20);
	
	Factory().createObj<Button>(L"ImageBack.png", std::bind(&Shop::Reroll, this)).setPosition({ LeftPadding + 250, WinHalfSizeY + 100 }).setParent(this->transform).AddText(L"전체리롤", 30).setRenderOrder(120);
	//보상 텍스트박스 
	compensationText = Factory().createObj<Image>(L"ImageBack.png").setPosition({ LeftPadding + 250, WinHalfSizeY + 200 }).setParent(this->transform).AddText(L"", 20).Get()->GetComponent<D2DFont>();//근데 이친구들이 원하는 텍스트를 따라가고싶단말이지.. 
	//리롤가능한 횟수를 출력하는 텍스트박스
	rerollText = Factory().createObj<Image>(L"ImageBack.png").setPosition({ LeftPadding + 250, WinHalfSizeY + 300 }).setParent(this->transform).AddText(L"리롤 가능 횟수" + std::to_wstring(reroll), 20).Get()->GetComponent<D2DFont>();
	//조합표 확인 버튼
	Factory().createObj<Button>(L"ImageBack.png", [this]() {combination->SetActive(true); }).setPosition({LeftPadding + 650, WinHalfSizeY + 100}).setParent(this->transform).AddText(L"조합식", 30); //아 여기에는 어떻게 넣어줄까...  상점도 조합표를 가져올까?
	//소환하기 버튼
	Factory().createObj<Button>(L"ImageBack.png", std::bind(&Shop::Spawn, this)).setPosition({ LeftPadding + 650, WinHalfSizeY + 200 }).setParent(this->transform).AddText(L"소환하기", 30);

	SetActive(false); 
}//길게 나열하는것도 괜찮긴한데.. 너무 길지않나? 

Shop::~Shop() //인규형이 만들어준 텍스트클래스를 기준으로 텍스트 박스도 빠르게 만들어야지.. 특정값을 출력할수있게 템플릿으로 만들수있을려나? 
{
}

void Shop::Reroll() //맨처음에는 어떻게 처리하는지 올라온거 봤었는데 그거대로 처리할수있도록하자.. 
{
	
	if (reroll <= 0)
		return;
	compensationList.clear();
	Text = L""; //텍스트 초기화
	reroll--;
	rerollText->SetDialog(L"리롤 가능 횟수" +std::to_wstring(reroll));
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
	//여기서 모든 아이콘이 1일때만 예외처리하고 
	if (count[0] == 1 && count[1] == 1 && count[2] == 1 && count[3] == 1 && count[4] == 1)
	{
		Text = L"모든 타워 2성";
		compensationText->SetDialog(Text);
		return; //아이콘 생성하기.. 
	}

	for (int i = 0; i < 4; i++)
	{
		MakeText(i, count[i]);
	}
	if (Text == L"")
		Text = L"꽝";
	compensationText->SetDialog(Text);
}

void Shop::Spawn() //이제 텍스트도 띄우고 좀더 이쁘게 만들어야겠다.. 
{
	int inven = 0;
	for (auto var : compensationList)
	{	
		GameObject* tower = Pools::GetInstance().get()->PopPool(var);   // 아이콘을 소환하는게아니라.타워를 소환
		if (tower != nullptr) //현재 모든 타워가 미완이라 터질수있으니 일단 이렇게 처리함
			tower->transform->SetRelativeLocation(Containers[inven]->transform->GetWorldLocation()); //팩토리처럼 만들때 세팅할수있듯이.. 오브젝트풀도? 그렇게 해볼까? 
		inven++;
	}
	compensationList.clear(); 
	spawner->StartWave();
	SetActive(false);
}

void Shop::MakeText(int order, int count) //내 생각에는 될거같은데 테스트는 해봐야할듯.. //이름으로 받지말고.. 아이디로 받자
{
	
	if (count == 2)
	{
		if (Text != L"") //아 중복 개싫다
			Text += L"+";
		compensationList.push_back(order * 3 + 0);
		compensationList.push_back(order * 3 + 0);
		Text += L"1성" + TowerName[order] + L"2개"; //타워의 종류가 늘어나면 버그니까 알아서 잘 그전에 고치셈
	}
	else if (count == 3)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 1);
		Text += L"2성" + TowerName[order];
	}
	else if (count == 4)
	{
		if (Text != L"")
			Text += L"+";
		compensationList.push_back(order * 3 + 1);
		compensationList.push_back(order * 3 + 1);
		Text += L"2성" + TowerName[order] + L"2개"; //인벤토리에 띄워야함.. 위에 별도 가지고있는 방식으로.. 보상을 push 하는방식으로? 그럼 레벨에 종류를 들고있는 페어정보를 저장하면되겠네.. 
	}
	else if (count == 5)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 2);
		Text += L"3성" + TowerName[order];
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
