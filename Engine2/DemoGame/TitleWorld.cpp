#include "../D2DEngine/pch.h"
#include "TitleWorld.h" 
#include "BattleWorld.h" //�̰͵� ���Ŵ������� ó���ϸ� ���⼭ ó�� ���ص��ɰ���.. 
#include "DemoGameApp.h"
#include "Factory.h"

TitleWorld::TitleWorld()
{
}

TitleWorld::~TitleWorld()
{

}

void TitleWorld::MakeObject() //���尡 ����ɶ� ������ ���忡 �ִ��Ŵ� �����ϵ��� �����.. 
{
	Fac->CreateImage(L"title.png", WinHalfSizeXY);
	Fac->CreateButton(L"GameStart.png", []() { DemoGameApp::ChangeCurWorld(new BattleWorld); } ,{ WinHalfSizeX, WinHalfSizeY + 200 }); //���ӽ���
	Fac->CreateButton(L"GameStart.png", []() {  } ,{ WinHalfSizeX, WinHalfSizeY + 300 }); //ȯ�漳��
	Fac->CreateButton(L"GameStart.png", []()  { SendMessage(DemoGameApp::hWnd, WM_CLOSE, 0, 0); }, { WinHalfSizeX, WinHalfSizeY + 400 }); //��������
	//������� �ߵǴµ� .. �� ���������� ����ȴ�.. 
	//�� �� ª�� ����;�.. �׷����� �̹�������.. ��ư�� ��� ���� �׷� ������Ʈ �������� �������߾����ٵ�..
	//�ƴѰ�? 
}
//���ٽ��� ��ģ���� ��Ű����� ���� ������? 

//�������� ��� �������� ����̰�..    