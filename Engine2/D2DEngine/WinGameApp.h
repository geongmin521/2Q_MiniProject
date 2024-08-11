#pragma once
//#include "D2DRenderer.h" //���� ���� ����
#include <windows.h>
#include "Resource.h"

class ResourceManager;
class World;
class WinGameApp
{
	HINSTANCE hInst;
public:
	static HWND hWnd;//���������� �����Ǵ°ɱ�?
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


