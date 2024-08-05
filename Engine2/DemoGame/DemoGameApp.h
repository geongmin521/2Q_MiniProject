#pragma once
#include "../D2DEngine/WinGameApp.h" //아 설마 이거때문인가?

class DemoGameApp : public WinGameApp 
{
public: 
	virtual void Initialize(HINSTANCE hInstance, int nShowCmd) override;
	virtual void Run() override;
	virtual void Uninitialize() override;
	static void ChangeCurWorld(World* world) { curWorld = world; }

};
