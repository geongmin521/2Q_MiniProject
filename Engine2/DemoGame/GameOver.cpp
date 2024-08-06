#include "../D2DEngine/pch.h"
#include "Factory.h"
#include "GameOver.h"

GameOver::GameOver()
{
	Fac->CreateImage(L"BigBack.png", WinHalfSizeXY, { 2,2 }, &subUi);

	Fac->CreateButton(L"ImageBack.png", [this]() {}, { WinHalfSizeX, WinHalfSizeY + 100 }, &subUi);//다시시작
	//어떻게 처리할까.. 씬을 다시 로드하면될듯?
	Fac->CreateButton(L"ImageBack.png", [this]() {}, { WinHalfSizeX, WinHalfSizeY + 300 }, &subUi);//메인으로
	//메인으로 씬을 변환하면되고.. 
}

//씬매니저로 따로 뺄거고.. 
//신로드하면 현재씬을 제거하고 새로운 씬을 만들기만하면됨.. 

GameOver::~GameOver()
{
}

void GameOver::Update(float deltaTime)
{
}

void GameOver::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
