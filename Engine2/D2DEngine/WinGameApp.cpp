#include "pch.h"
#include "WinGameApp.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"

#include "TimeSystem.h"
#include "InputSystem.h"
#include "World.h"
#include "SceneManager.h"
#include "EventSystem.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")//디버거가 남겨져있어서그런듯? 
#endif


HWND WinGameApp::hWnd = nullptr;
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
	POINT startPoint{0,0};
	EventSystem* event = EventSystem::GetInstance().get();
	bool isDragging    = event->isDragging; //그냥 이걸로하면안될거같고.. 
	bool isClickValid  = event->isClickValid;
	int dragThresholdX = GetSystemMetrics(SM_CXDRAG);
	int dragThresholdY = GetSystemMetrics(SM_CYDRAG);
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

	case WM_LBUTTONDBLCLK:
		isClickValid = false; //일단 나쁘지 않은거 같으니 놔둬보자.. 엄.. 아까보다 업데이트는 편해졌지만 나머지는 그렇지않음.. 
		EventSystem::GetInstance().get()->DoubleClickEvent();
	case WM_LBUTTONDOWN:
		// 드래그 시작점 기록
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
		isDragging = false;
		isClickValid = true;
		event->isClickValid = true;
		break;

	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON) // 마우스 왼쪽 버튼이 눌린 상태
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			// 마우스 이동 거리가 드래그 임계값을 초과하는지 확인
			if (abs(x - startPoint.x) > dragThresholdX || abs(y - startPoint.y) > dragThresholdY)
			{
				isDragging = true;
				//EventSystem::GetInstance().get()->BeginDragEvent(); //근데 이게 움직일때만 이벤트가 발생하긴하는데 이렇게 하면되겠지? 
				isClickValid = false;
			}
			if(EventSystem::GetInstance().get()->isDragging != isDragging)
				EventSystem::GetInstance().get()->BeginDragEvent();
			if(isDragging)
				EventSystem::GetInstance().get()->StayDragEvent();
			event->isDragging = isDragging;
		}
		break;

	case WM_LBUTTONUP:
		if (isDragging)
		{
			// 드래그 종료 처리
			event->isDragging = false;
			EventSystem::GetInstance().get()->EndDragEvent();
		}
		else if (isClickValid)
		{
			EventSystem::GetInstance().get()->ClickEvent();
		}
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
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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
	D2DRenderer::GetInstance(hWnd);
}

void WinGameApp::Run() 
{
	MSG msg;

	while (true) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				delete SceneManager::GetInstance().get()->GetCurWorld(); //여기는 뭐든 월드를 지워야하고.. 
				break;
			}
			
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
	SceneManager::GetInstance().get()->GetCurWorld()->Update(fTimeElapsed);
}

void WinGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	D2DRenderer::GetInstance()->GetRenderTarget()->BeginDraw();
	D2DRenderer::GetInstance()->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	SceneManager::GetInstance().get()->GetCurWorld()->Render(pRenderTarget);
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




