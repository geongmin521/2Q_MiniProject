#pragma once
#include "../D2DEngine/UI.h"

class Image;
class Container;
class Combination;
class Shop: public UI //��Ŭ����? ��� �׳� UI������Ʈ���� �������� ������ �ʿ��� �Լ����� ������
{
private:
	bool isLock[5];
	int Id[5]; 
	int reroll;
	std::vector<GameObject*> subUi;			
	std::vector<Image*> Icons;				
	std::vector<std::wstring> ImagePath;	
	std::vector<std::wstring> TowerName;	
	std::vector<int> compensationList; //�������� �޾ƾ��ϴ� Ÿ���� ���̵� �����ϱ�
	std::wstring Text;
	std::vector<Container*> Containers; //���⿡ ����������.. ������ �ܺο��� �ؾ��ҵ�? 
	Combination* combination;
public:

	Shop();
	virtual ~Shop();
	void Reroll();
	void Spawn(); //���⼭ ���ս� ó���ϴ°͵� �������ϰ�.. 
	void MakeText(std::wstring name,int count);
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	void SetOtherUI(std::vector<Container*> container, Combination* combination) { this->Containers = container; this->combination = combination;}
	int TowerNameToID(std::wstring name); //�����̷��� ������ ������ �����̾ȳ���.. 

};

