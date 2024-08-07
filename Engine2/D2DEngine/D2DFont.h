#pragma once

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
class D2DFont // 원래 이름 Font였는데 구조체가 이미 있어서 수정함
{
public:
	D2DFont();
	~D2DFont();

private:
	float FontSize = 10; 
	D2D1_POINT_2F Pos = {0.f , 0.f};
	D2D_SIZE_F BoxSize = { 100.f, 50.f };

	ID2D1SolidColorBrush* FontBrush = nullptr;
	IDWriteTextFormat* DWriteTextFormat = nullptr;;
	IDWriteTextLayout* DWriteTextLayout = nullptr;;

	Transform* transform = nullptr;
	bool IsTransform = false; 
public:
	void Update(float deltaTime);
	void DrawFont(D2D1_COLOR_F color);  // 작성된 내용을 그림

	void SetPos(float _X, float _Y) { Pos = { _X , _Y }; } // 위치 조정 로컬좌표일때 사용
	void SetBoxSize(float width, float height) { BoxSize.width = width; BoxSize.height = height;} // 텍스트박스 사이즈 

	void LoadFont(std::wstring FontName); // 용도 제어판 글꼴에 있는 폰트를 로드하는 것

	void CreateLayoutText(std::wstring detail); // 텍스트 내용을 작성
	void SetSize(float _FontSize , DWRITE_TEXT_RANGE textRange); // DWRITE_TEXT_RANGE 사용법 {0 , 9 } 이렇게 했을때 0부터 9번째 까지의 글자 크기를 변경
	
	// 폰트 정렬 잘못 넣어졌을 경우 중앙으로 정렬되게 예외함
	void Sort(Setting _Sort); // 왼쪽, 가운데, 오른쪽 정렬
	void SetFontLocation(Setting _Sort); // 문단 위쪽, 중간, 아래쪽 정렬

	void OnTransform(); // 트랜스폼을 이용한 렌더일 경우 사용
	Transform* GetTransform() { return transform; }
};

/// 사용 설명서 /// 
// 아래의 2개를 먼저 설정을 하고선 LoadFont(L"제어판의 글꼴");을 하면 된다.
// D2D1_POINT_2F Pos = { 0.f , 0.f };
// D2D_SIZE_F BoxSize = { 100.f, 50.f };
// 생성법 D2DFont test; test.CreateLayoutText(L"안녕하세요");
// 폰트 정렬 및 사이즈 변경은 랜더가 되기전에 하면 문제 없이 적용이 된다.

// 트랜스폼을 사용하는 경우는 OnTransform() 함수를 사용하고선 이후 GetTransform()->SetParent(오브젝트의 트랜스폼을 하면 된다.)