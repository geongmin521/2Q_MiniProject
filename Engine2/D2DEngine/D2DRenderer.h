#pragma once
class AABB;
class Circle;
class D2DRenderer 
{
public:
	D2DRenderer();
	~D2DRenderer();

	static D2D1_MATRIX_3X2_F cameraTransform;

	static D2DRenderer* GetInstance(HWND hWnd = nullptr);
	void Initialize(HWND hWnd);
	void Uninitialize();
	
	ID2D1Factory* GetFactory() { return D2DFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return RenderTarget; }
	size_t GetUsedVRAM();
	void DrawTextFunc(std::wstring text,int x, int y);
	void DrawBox(int left, int top, int right, int bottom);
	void DrawAABB(AABB& aabb);
	void DrawLine(MathHelper::Vector2F start, MathHelper::Vector2F end);
	
	void DrawCircle(Circle& circle);
	void DrawCircle(float CenterX, float CenterY, float radius, float size);

	void DrawGradientCircle(const D2D1_POINT_2F& position, float radius, const D2D1_COLOR_F& color);

public:
	ID2D1Factory* D2DFactory;			// D2D 개체 인터페이스 포인터 변수
	ID2D1HwndRenderTarget* RenderTarget; //그리는 렌더타겟								//이미지 생성에필요
	IWICImagingFactory* WICFactory;		// D2D비트맵 생성을 위한 이미지 처리 인터페이스 //이미지 생성에필요 
	ID2D1SolidColorBrush* greenBrush;	//뭔가를 그리기위한 객체

	IDWriteFactory* DWriteFactory;		// TextFormat생성을 위한 팩토리
	IDWriteTextFormat* DWriteTextFormat; // 기본 텍스트 출력을 위한 Format
	ID2D1SolidColorBrush* Brush;			// 렌더타겟이 생성하는 리소스 역시 장치의존
	ID2D1RadialGradientBrush* RadialBrush; // 방사형 브러쉬 그래디언트

	IDXGIFactory4* DXGIFactory;			// DXGI팩토리 
	IDXGIAdapter3* DXGIAdapter;			// 비디오카드 정보에 접근 가능한 인터페이스 
	HWND hWnd;							// 렌더타겟을 생성할 윈도우 핸들
	D2D_SIZE_U	ClientSize;				// 렌더타겟의 크기

	ID2D1DeviceContext* DeviceContext; // 이펙트 https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1_1/nn-d2d1_1-id2d1devicecontext

private:
	static D2DRenderer* inst;

};




