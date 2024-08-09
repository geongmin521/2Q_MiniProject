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

Shop::Shop() //������ �Ű������� �ϳ� �Ѱ��ٱ�? 
{
	ImagePath = { L"Crossbow.png",L"Water.png",L"Pile.png",L"HolyCross.png",L"vampire.png" };//�±׸� ����� �Ǹ� �̰ɾ���? �Ƹ���.. �ٲ�����ִ°���.. 
	TowerName = {L"����Ÿ��", L"����Ÿ��", L"����Ÿ��", L"��Ÿ��" }; //�� enum���� �����? 
	//enum int�� ��ȯ�ؼ� 3���ϰ� ������ -1 ���� �����ָ� ���ƴѰ�? 
	renderOrder = 80;
	Fac->CreateImage(L"BigBack.png", WinHalfSizeXY, {2,2}, &subUi);
	float LeftPadding = 700; 
	for (int i = 0; i < 5; i++)//������
		Icons.push_back(Fac->CreateImage(L"Crossbow.png", { LeftPadding + i * 130 ,WinHalfSizeY - 200}, {1,1}, &subUi));
	for (int i = 0; i < 5; i++)//���� ��ױ�
		Fac->CreateButton(L"smallBack.png", [i, this]() { isLock[i] = !isLock[i]; }, { LeftPadding + i * 130, WinHalfSizeY - 100 },&subUi);

	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Reroll, this), { LeftPadding + 250, WinHalfSizeY + 100 }, &subUi);
	//����ǥ�� ���� ������ ���� ����ϴ� �ؽ�Ʈ�ڽ�.. 
	Fac->CreateImage(L"ImageBack.png", { LeftPadding + 250, WinHalfSizeY + 200 }, { 1,1 }, &subUi);
	//���Ѱ����� Ƚ���� ����ϴ� �ؽ�Ʈ�ڽ�
	Fac->CreateImage(L"ImageBack.png", { LeftPadding + 250, WinHalfSizeY + 300 }, { 1,1 }, &subUi);
	//����ǥ Ȯ�� ��ư
	Fac->CreateButton(L"ImageBack.png", [this]() {combination->isActive = true; }, { LeftPadding + 650, WinHalfSizeY + 100 }, &subUi); //�� ���⿡�� ��� �־��ٱ�...  ������ ����ǥ�� �����ñ�?
	//��ȯ�ϱ� ��ư
	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Spawn, this), { LeftPadding + 650, WinHalfSizeY + 200 }, &subUi);
}

Shop::~Shop() //�α����� ������� �ؽ�ƮŬ������ �������� �ؽ�Ʈ �ڽ��� ������ ��������.. Ư������ ����Ҽ��ְ� ���ø����� �������������? 
{
}

void Shop::Reroll() //��ó������ ��� ó���ϴ��� �ö�°� �þ��µ� �װŴ�� ó���Ҽ��ֵ�������.. 
{
	Text = L""; //�ؽ�Ʈ �ʱ�ȭ
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
	//���⼭ ��� �������� 1�϶��� ����ó���ϰ� 
	if (count[0] == 1 && count[1] == 1 && count[2] == 1 && count[3] == 1 && count[4] == 1)
	{
		Text = L"��� Ÿ�� 2��";
		return; //������ �����ϱ�.. 
	}

	for (int i = 0; i < 4; i++)
	{
		MakeText(i, count[i]);
	}
	if (Text == L"")
		Text = L"��";
}

void Shop::Spawn() //���� �ؽ�Ʈ�� ���� ���� �̻ڰ� �����߰ڴ�.. 
{
	int inven = 0;
	for (auto var : compensationList)
	{
		//Pools::GetInstance().get()->PopPool(); //�������� �������ϳ�? �����̴� �����ܵ� ������ƮǮ�� ���ʿ䰡�ֳ�? �𸣰ڴ�.. 
		//Fac->CreateMoveIcon(ImagePath[var/3], Containers[inven]->transform->GetWorldLocation()); /�������� ��ȯ�ϴ°Ծƴ϶�. Ÿ���� ��ȯ
		GameObject* tower =  Fac->CreateGameObjectFromId(var);  // �������� ��ȯ�ϴ°Ծƴ϶�.Ÿ���� ��ȯ
		if (tower != nullptr) //���� ��� Ÿ���� �̿��̶� ������������ �ϴ� �̷��� ó����
			tower->transform->SetRelativeLocation(Containers[inven]->transform->GetWorldLocation());
		inven++;

	}
	compensationList.clear(); 
	spawner->StartWave();
	isActive = false; //���ֱ�.. 
}

void Shop::MakeText(int order, int count) //�� �������� �ɰŰ����� �׽�Ʈ�� �غ����ҵ�.. //�̸����� ��������.. ���̵�� ����
{
	
	if (count == 2)
	{
		if (Text != L"") //�� �ߺ� ���ȴ�
			Text += L"+";
		compensationList.push_back(order * 3 + 0);
		compensationList.push_back(order * 3 + 0);
		Text += L"1��" + TowerName[order] + L"2��"; //Ÿ���� ������ �þ�� ���״ϱ� �˾Ƽ� �� ������ ��ġ��
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
		Text += L"2��" + TowerName[order] + L"2��"; //�κ��丮�� �������.. ���� ���� �������ִ� �������.. ������ push �ϴ¹������? �׷� ������ ������ ����ִ� ��������� �����ϸ�ǰڳ�.. 
	}
	else if (count == 5)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 2);
		Text += L"3��" + TowerName[order];
	}
} 

void Shop::Update(float deltaTime)
{
	//�̰� �׳� ������Ʈ�������̶� ������Ʈ���� ������Ʈ�� �������ָ�ɵ�
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
