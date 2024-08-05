#include "pch.h"
#include "WinGameApp.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"

#include "TimeSystem.h"
#include "InputSystem.h"
#include "World.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")//디버거가 남겨져있어서그런듯? 
#endif

WinGameApp::WinGameApp()
{
	m_pResourceManager = new ResourceManager;
}

WinGameApp::~WinGameApp()
{
	if (m_pResourceManager)
	{
		delete m_pResourceManager;
		m_pResourceManager = nullptr;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		inputSystem->UpdateKey();
		break;
	case WM_KEYUP:
		inputSystem->UpdateKey();
		break;
	case WM_SETFOCUS:
		timeManager->SetTimeScale(1); 
		break;
	case WM_KILLFOCUS:
		timeManager->SetTimeScale(0);
		break;
	case WM_ENTERSIZEMOVE:
		timeManager->SetTimeScale(0);
		break;
	case WM_EXITSIZEMOVE:
		timeManager->InitTime(); 
		timeManager->SetTimeScale(1);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void WinGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	// 공통으로 사용하는 윈도우 설정,생성부분을 작성한다.
	WNDCLASSEXW wcex;
	timeManager->InitTime();
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMOGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOGAME);
	wcex.lpszClassName = L"Test";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);
	InitInstance(hInstance, nShowCmd);

	D2DRenderer::GetInstance(hWnd); //이거 구조 너무 맘에 안드니까 수정바람
	world = new World;
}

void WinGameApp::Run() 
{
	MSG msg;

	while (true) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//메세지 중에 윈도우 포커스가 떠나는 메세지확인하기
		}
		else
		{
			timeManager->UpdateTime();
			inputSystem->UpdateKey();
			inputSystem->UpdateMouse(hWnd);

			Update(timeManager->GetDeltaTime());
			Render(D2DRenderer::GetInstance()->GetRenderTarget());
			inputSystem->ResetInput();
		}	
	}
	
}

void WinGameApp::Update(float fTimeElapsed)
{
	world->Update(fTimeElapsed);
}

void WinGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	D2DRenderer::GetInstance()->GetRenderTarget()->BeginDraw();
	D2DRenderer::GetInstance()->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	world->Render(pRenderTarget);
	D2DRenderer::GetInstance()->GetRenderTarget()->EndDraw();
}


void WinGameApp::Uninitialize()
{
	D2DRenderer::GetInstance()->Uninitialize(); //지워야하는거 맞지않나?
}

bool WinGameApp::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; 

	RECT rt = { 0, 0, WinSizeX , WinSizeY }; //원도우 창크기

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, 0);

	hWnd = CreateWindowW(L"Test", L"test", WS_OVERLAPPEDWINDOW,
		50, 50, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}




