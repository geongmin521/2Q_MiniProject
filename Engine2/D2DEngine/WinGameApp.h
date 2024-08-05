#pragma once
//#include "D2DRenderer.h" //교차 참조 오류
#include <windows.h>
#include "Resource.h"

class ResourceManager;
class World;
class WinGameApp
{
	HINSTANCE hInst;
public:
	static World* curWorld; //씬매니저를 만들어야할까.. 이걸 스태틱으로 처리할수있을까.. 
	HWND hWnd;  
	WinGameApp();
	virtual ~WinGameApp();
	virtual void Initialize(HINSTANCE hInstance, int nShowCmd);
	virtual void Run();
	virtual void Uninitialize();
	bool InitInstance(HINSTANCE hInstance, int nCmdShow);
	void Update(float fTimeElapsed);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
	ResourceManager* m_pResourceManager = nullptr;
};


