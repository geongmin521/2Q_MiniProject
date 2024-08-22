#pragma once
#include "Renderer.h"
enum Setting // 용도 정렬 선택 하기 위해서
{
	LEFT,
	MIDDLE,
	RIGHT,
	TOP,
	BOTTOM,
	EXIT
};

class Transform;
class Component;
class D2DFont : public Renderer 
{
public:
	D2DFont() = default;		 // 배틀 월드에서 어디선가 사용하고 있는듯 일단 만들어 놓음 
	D2DFont(const std::wstring _Dialog); // 최초 생성의 폰트 위치는 왼쪽 정렬에 단락은 가운데
	virtual ~D2DFont();

private:
	float FontSize = 10; 
	D2D1_POINT_2F Pos = {0.f , 0.f};   // 로컬 좌표
	D2D_SIZE_F BoxSize = { 100.f, 50.f }; // 텍스트 박스 사이즈
	std::wstring Dialog; // public으로 해놓고 사용자가 직접 내용 작성하는게 더 좋을가?

	ID2D1SolidColorBrush* FontBrush = nullptr;
	IDWriteTextFormat* DWriteTextFormat = nullptr;;
	IDWriteTextLayout* DWriteTextLayout = nullptr;;

	Setting FontX = MIDDLE;
	Setting FontY = MIDDLE;
public:
	virtual void Update(float deltaTime); // 컴포넌트면 이게 필요할가? 고민사항
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1);  // 작성된 내용을 그림

	void SetColor(D2D1_COLOR_F color) { FontBrush->SetColor(color); } // 컬러 변경 주의사항 : 렌더 하기전에 색을 변경해야 됨
	void SetPos(float _X, float _Y) { Pos = { _X , _Y }; } // 위치 조정 로컬좌표일때 사용
	void SetBoxSize(float width, float height);
	void SetBoxSize(MathHelper::Vector2F size);
	void SetDialog(std::wstring input); // 내용 변경

	void LoadFont(std::wstring FontName); // 용도 제어판 글꼴에 있는 폰트를 로드하는 것
	void SetSize(float _FontSize , DWRITE_TEXT_RANGE textRange); // DWRITE_TEXT_RANGE 사용법 {0 , 9 } 이렇게 했을때 0부터 9번째 까지의 글자 크기를 변경
	
	// 폰트 정렬 잘못 넣어졌을 경우 중앙으로 정렬되게 예외함 
	void Sort(Setting _SortX, Setting _SortY); // 왼쪽, 가운데, 오른쪽 정렬
	
	// IDWriteTextFormat 변경 사용 용도  
	void SetWriteTextFormat(IDWriteTextFormat* _IDWriteTextFormat);

private:
	void CreateLayoutText(std::wstring detail); // 텍스트 내용을 작성
};
