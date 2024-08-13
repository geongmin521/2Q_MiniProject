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

Shop::Shop() //������ �Ű������� �ϳ� �Ѱ��ٱ�? 
{
	ImagePath = { L"Crossbow.png",L"Water.png",L"Pile.png",L"HolyCross.png",L"vampire.png" };//�±׸� ����� �Ǹ� �̰ɾ���? �Ƹ���.. �ٲ�����ִ°���.. 
	TowerName = {L"����Ÿ��", L"����Ÿ��", L"����Ÿ��", L"��Ÿ��" };

	renderOrder = 80;
	Factory().createObj<Image>(L"BigBack.png").setPosition(WinHalfSizeXY).setScale({ 2,2 }).setParent(this->transform);
	float LeftPadding = 700; 
	for (int i = 0; i < 5; i++)//������
		Icons.push_back(Factory().createObj<Image>(L"Crossbow.png").setPosition({ LeftPadding + i * 130 ,WinHalfSizeY - 200 }).setParent(this->transform).Get<Image>());
	for (int i = 0; i < 5; i++)//���� ��ױ�
		Factory().createObj<Button>(L"smallBack.png", [i, this]() { isLock[i] = !isLock[i]; }).setPosition({ LeftPadding + i * 130, WinHalfSizeY - 100 }).setParent(this->transform).AddText(L"Lock", 20);
	
	Factory().createObj<Button>(L"ImageBack.png", std::bind(&Shop::Reroll, this)).setPosition({ LeftPadding + 250, WinHalfSizeY + 100 }).setParent(this->transform).AddText(L"��ü����", 30).setRenderOrder(120);
	//���� �ؽ�Ʈ�ڽ� 
	compensationText = Factory().createObj<Image>(L"ImageBack.png").setPosition({ LeftPadding + 250, WinHalfSizeY + 200 }).setParent(this->transform).AddText(L"", 20).Get()->GetComponent<D2DFont>();//�ٵ� ��ģ������ ���ϴ� �ؽ�Ʈ�� ���󰡰�ʹܸ�����.. 
	//���Ѱ����� Ƚ���� ����ϴ� �ؽ�Ʈ�ڽ�
	rerollText = Factory().createObj<Image>(L"ImageBack.png").setPosition({ LeftPadding + 250, WinHalfSizeY + 300 }).setParent(this->transform).AddText(L"���� ���� Ƚ��" + std::to_wstring(reroll), 20).Get()->GetComponent<D2DFont>();
	//����ǥ Ȯ�� ��ư
	Factory().createObj<Button>(L"ImageBack.png", [this]() {combination->SetActive(true); }).setPosition({LeftPadding + 650, WinHalfSizeY + 100}).setParent(this->transform).AddText(L"���ս�", 30); //�� ���⿡�� ��� �־��ٱ�...  ������ ����ǥ�� �����ñ�?
	//��ȯ�ϱ� ��ư
	Factory().createObj<Button>(L"ImageBack.png", std::bind(&Shop::Spawn, this)).setPosition({ LeftPadding + 650, WinHalfSizeY + 200 }).setParent(this->transform).AddText(L"��ȯ�ϱ�", 30);

	SetActive(false); 
}//��� �����ϴ°͵� �������ѵ�.. �ʹ� �����ʳ�? 

Shop::~Shop() //�α����� ������� �ؽ�ƮŬ������ �������� �ؽ�Ʈ �ڽ��� ������ ��������.. Ư������ ����Ҽ��ְ� ���ø����� �������������? 
{
}

void Shop::Reroll() //��ó������ ��� ó���ϴ��� �ö�°� �þ��µ� �װŴ�� ó���Ҽ��ֵ�������.. 
{
	
	if (reroll <= 0)
		return;
	compensationList.clear();
	Text = L""; //�ؽ�Ʈ �ʱ�ȭ
	reroll--;
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
	//���⼭ ��� �������� 1�϶��� ����ó���ϰ� 
	if (count[0] == 1 && count[1] == 1 && count[2] == 1 && count[3] == 1 && count[4] == 1)
	{
		Text = L"��� Ÿ�� 2��";
		compensationText->SetDialog(Text);
		return; //������ �����ϱ�.. 
	}

	for (int i = 0; i < 4; i++)
	{
		MakeText(i, count[i]);
	}
	if (Text == L"")
		Text = L"��";
	compensationText->SetDialog(Text);
}

void Shop::Spawn() //���� �ؽ�Ʈ�� ���� ���� �̻ڰ� �����߰ڴ�.. 
{
	int inven = 0;
	for (auto var : compensationList)
	{	
		GameObject* tower = Pools::GetInstance().get()->PopPool(var);   // �������� ��ȯ�ϴ°Ծƴ϶�.Ÿ���� ��ȯ
		if (tower != nullptr) //���� ��� Ÿ���� �̿��̶� ������������ �ϴ� �̷��� ó����
			tower->transform->SetRelativeLocation(Containers[inven]->transform->GetWorldLocation()); //���丮ó�� ���鶧 �����Ҽ��ֵ���.. ������ƮǮ��? �׷��� �غ���? 
		inven++;
	}
	compensationList.clear(); 
	spawner->StartWave();
	SetActive(false);
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

int Shop::TowerNameToID(std::wstring name)
{
	for (int i = 0; i < TowerName.size(); i++)
	{
		if (TowerName[i] == name)
			return i * 3;
	}
}
