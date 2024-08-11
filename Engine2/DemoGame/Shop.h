#pragma once
#include "UIPanel.h"

class Image;
class Container;
class Combination;
class EnemySpawner;
class Shop: public UIPanel 
{
private:
	bool isLock[5];
	int Id[5]; 
	int reroll;
	std::vector<Image*> Icons;				
	std::vector<std::wstring> ImagePath;	
	std::vector<std::wstring> TowerName;	
	std::vector<int> compensationList; //�������� �޾ƾ��ϴ� Ÿ���� ���̵� �����ϱ�
	std::wstring Text;
	std::vector<Container*> Containers; //���⿡ ����������.. ������ �ܺο��� �ؾ��ҵ�? 
	Combination* combination;

	//���� ������Ű������.. ���߿� �̺�Ʈ�� �����ɷλ��� �˷��൵ �����Ű�����?
	
public:
	EnemySpawner* spawner;
	Shop();
	virtual ~Shop();
	void Reroll();
	void Spawn(); //���⼭ ���ս� ó���ϴ°͵� �������ϰ�.. 
	void MakeText(int order,int count); //����,����,����,���ڰ� // {L"����Ÿ��", L"����Ÿ��", L"����Ÿ��", L"��Ÿ��" };
	void SetOtherUI(std::vector<Container*> container, Combination* combination) { this->Containers = container; this->combination = combination;}
	int TowerNameToID(std::wstring name); //�����̷��� ������ ������ �����̾ȳ���.. 

};

