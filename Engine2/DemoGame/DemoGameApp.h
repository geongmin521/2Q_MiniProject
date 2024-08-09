#pragma once
#include "WinGameApp.h" //아 설마 이거때문인가?

class DemoGameApp : public WinGameApp 
{
public: 
	virtual void Initialize(HINSTANCE hInstance, int nShowCmd) override;
	virtual void Run() override;
	virtual void Uninitialize() override;
	static void ChangeCurWorld(World* world); //아니면 프로퍼티로 이것의 변화만을감지하고있다가 바꿔도 되지않나? 

};
