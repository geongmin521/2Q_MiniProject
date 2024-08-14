#pragma once
#include "WinGameApp.h" 

class DemoGameApp : public WinGameApp 
{
public: 
	virtual void Initialize(HINSTANCE hInstance, int nShowCmd) override;
	virtual void Run() override;
	virtual void Uninitialize() override;
};
