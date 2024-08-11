#pragma once
#include "WinGameApp.h" //아 설마 이거때문인가?

class DemoGameApp : public WinGameApp 
{
public: 
	virtual void Initialize(HINSTANCE hInstance, int nShowCmd) override;
	virtual void Run() override;
	virtual void Uninitialize() override;
};
