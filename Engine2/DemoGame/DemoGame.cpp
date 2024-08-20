// DemoGame.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "DemoGame.h"
#include "DemoGameApp.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   // WNDCLASS wc;
   // wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    DemoGameApp App;
    App.Initialize(hInstance, nCmdShow);
    App.Run();
    App.Uninitialize(); 
}

