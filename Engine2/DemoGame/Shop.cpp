#include "../D2DEngine/pch.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Pools.h"
#include "../D2DEngine/Transform.h"
#include "Factory.h"
#include "Shop.h"
#include "Image.h"
#include "Container.h"
#include "Combination.h"

Shop::Shop() //얘한테 매개변수로 하나 넘겨줄까? 
{
	ImagePath = { L"arrow.png",L"sungsu.png",L"wood.png",L"heal.png",L"vampire.png" };//태그를 만들게 되면 이걸쓸듯? 아몰라.. 바뀔수도있는거지.. 
	TowerName = {L"석궁타워", L"성수타워", L"말뚝타워", L"힐타워" }; //걍 enum으로 만들까? 
	//enum int로 변환해서 3곱하고 성급을 -1 빼서 더해주면 끝아닌가? 
	renderOrder = 80;
	Fac->CreateImage(L"BigBack.png", WinHalfSizeXY, {2,2}, &subUi);
	float LeftPadding = 700; 
	for (int i = 0; i < 5; i++)//아이콘
		Icons.push_back(Fac->CreateImage(L"arrow.png", { LeftPadding + i * 130 ,WinHalfSizeY - 200}, {1,1}, &subUi));
	for (int i = 0; i < 5; i++)//리롤 잠그기
		Fac->CreateButton(L"smallBack.png", [i, this]() { isLock[i] = !isLock[i]; }, { LeftPadding + i * 130, WinHalfSizeY - 100 },&subUi);

	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Reroll, this), { LeftPadding + 250, WinHalfSizeY + 100 }, &subUi);
	//조합표를 보고 보상이 뭔지 출력하는 텍스트박스.. 
	Fac->CreateImage(L"ImageBack.png", { LeftPadding + 250, WinHalfSizeY + 200 }, { 1,1 }, &subUi);
	//리롤가능한 횟수를 출력하는 텍스트박스
	Fac->CreateImage(L"ImageBack.png", { LeftPadding + 250, WinHalfSizeY + 300 }, { 1,1 }, &subUi);
	//조합표 확인 버튼
	Fac->CreateButton(L"ImageBack.png", [this]() {combination->isActive = true; }, { LeftPadding + 650, WinHalfSizeY + 100 }, &subUi); //아 여기에는 어떻게 넣어줄까...  상점도 조합표를 가져올까?
	//소환하기 버튼
	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Spawn, this), { LeftPadding + 650, WinHalfSizeY + 200 }, &subUi);
}

Shop::~Shop() //인규형이 만들어준 텍스트클래스를 기준으로 텍스트 박스도 빠르게 만들어야지.. 특정값을 출력할수있게 템플릿으로 만들수있을려나? 
{
}

void Shop::Reroll() //맨처음에는 어떻게 처리하는지 올라온거 봤었는데 그거대로 처리할수있도록하자.. 
{
	Text = L""; //텍스트 초기화
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
		return; //아이콘 생성하기.. 
	}

	for (int i = 0; i < 4; i++)
	{
		MakeText(TowerName[i], count[i]);
	}
	if (Text == L"")
		Text = L"꽝";
}

void Shop::Spawn() //이제 텍스트도 띄우고 좀더 이쁘게 만들어야겠다.. 
{
	int inven = 0;
	for (auto var : compensationList)
	{
		//Pools::GetInstance().get()->PopPool(); //아이콘은 만들어야하나? 움직이는 아이콘도 오브젝트풀을 쓸필요가있나? 모르겠다.. 
		Fac->CreateMoveIcon(ImagePath[var/3], Containers[inven]->transform->GetWorldLocation()); //가지고 있는 인벤토리의 위치도 넣어주기 
		inven++;
	}
	compensationList.clear();
	isActive = false; //꺼주기.. 
}

void Shop::MakeText(std::wstring name, int count) //내 생각에는 될거같은데 테스트는 해봐야할듯.. 
{
	
	if (count == 2)
	{
		if (Text != L"") //아 중복 개싫다
			Text += L"+";
		compensationList.push_back(TowerNameToID(name) + 0);
		compensationList.push_back(TowerNameToID(name) + 0);
		Text += L"1성" + name + L"2개";
	}
	else if (count == 3)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(TowerNameToID(name) + 1);
		Text += L"2성" + name;
	}
	else if (count == 4)
	{
		if (Text != L"")
			Text += L"+";
		compensationList.push_back(TowerNameToID(name) + 1);
		compensationList.push_back(TowerNameToID(name) + 1);
		Text += L"2성" + name + L"2개"; //인벤토리에 띄워야함.. 위에 별도 가지고있는 방식으로.. 보상을 push 하는방식으로? 그럼 레벨에 종류를 들고있는 페어정보를 저장하면되겠네.. 
	}
	else if (count == 5)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(TowerNameToID(name) + 2);
		Text += L"3성" + name;
	}
} 

void Shop::Update(float deltaTime)
{
	//이건 그냥 오브젝트의집합이라 오브젝트들의 오브젝트만 실행해주며될듯
	for (auto var : subUi)
		var->Update(deltaTime);
}

void Shop::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto var : subUi)
		var->Render(pRenderTarget);

	D2DRenderer::GetInstance()->DrawTextFunc(Text,0,0);//, WinHalfSizeX, WinHalfSizeY);
}

int Shop::TowerNameToID(std::wstring name)
{
	for (int i = 0; i < TowerName.size(); i++)
	{
		if (TowerName[i] == name)
			return i * 3;
	}
}
