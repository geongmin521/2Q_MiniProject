#pragma once
#include "WinGameApp.h" //�� ���� �̰Ŷ����ΰ�?

class DemoGameApp : public WinGameApp 
{
public: 
	virtual void Initialize(HINSTANCE hInstance, int nShowCmd) override;
	virtual void Run() override;
	virtual void Uninitialize() override;
	static void ChangeCurWorld(World* world); //�ƴϸ� ������Ƽ�� �̰��� ��ȭ���������ϰ��ִٰ� �ٲ㵵 �����ʳ�? 

};
