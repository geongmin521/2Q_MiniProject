#include "pch.h"
#include "D2DRenderer.h"
#include "Helper.h"
#include "ResourceManager.h"
#include "AABB.h"
#include "Circle.h"
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "Dwrite.lib")

D2DRenderer::D2DRenderer()
{
}

D2DRenderer::~D2DRenderer()
{

}

D2D1_MATRIX_3X2_F D2DRenderer::cameraTransform = D2D1::Matrix3x2F::Identity();
D2DRenderer* D2DRenderer::inst = nullptr;

D2DRenderer* D2DRenderer::GetInstance(HWND hWnd)
{
	if (inst == nullptr) {
		inst = new D2DRenderer();
		inst->Initialize(hWnd);
	}
	return inst;
}

void D2DRenderer::Initialize(HWND hWnd) 
{
	hWnd = hWnd;
	HRESULT hr = S_OK;
	// COM 사용 시작
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
			이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
			DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
		*/
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.
		Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
		리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
		*/
		RECT rc;
		GetClientRect(hWnd, &rc);

		ClientSize = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);
		// Create a Direct2D render target.
		hr = D2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, ClientSize),
			&RenderTarget);
	}

	if (SUCCEEDED(hr))
	{
		hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &Brush);
	}

	if (SUCCEEDED(hr))
	{
		// Create WIC factory
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&WICFactory)
		);
	}	

	if (SUCCEEDED(hr))
	{
		hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &greenBrush);
	}

	if (SUCCEEDED(hr))
	{
		// DirectWrite 팩터리를 만듭니다.
		hr = DWriteCreateFactory( 
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(DWriteFactory),
			reinterpret_cast<IUnknown**>(&DWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite 텍스트 형식 개체를 만듭니다.
		hr = DWriteFactory->CreateTextFormat(
			L"Cooper", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			50.0f,   // Font Size
			L"", //locale
			&DWriteTextFormat
		);
		// 텍스트를 수평 및 수직으로 중앙에 맞춥니다.
		DWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		DWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	// VRAM 정보얻기 위한 개체 생성
	if (SUCCEEDED(hr))
	{
		// Create DXGI factory
		hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&DXGIFactory); 
	}
	if (SUCCEEDED(hr))
	{
		DXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&DXGIAdapter));
	}

}

void D2DRenderer::Uninitialize()
{
	SAFE_RELEASE(Brush);
	SAFE_RELEASE(RenderTarget);
	SAFE_RELEASE(D2DFactory);
	SAFE_RELEASE(WICFactory);
	SAFE_RELEASE(DWriteFactory);
	SAFE_RELEASE(DWriteTextFormat);
	SAFE_RELEASE(DXGIFactory);
	SAFE_RELEASE(DXGIAdapter);
	SAFE_RELEASE(greenBrush);
	CoUninitialize();
}

size_t D2DRenderer::GetUsedVRAM()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	DXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
	return videoMemoryInfo.CurrentUsage / 1024 / 1024;
}

void D2DRenderer::DrawTextFunc(std::wstring text,int x,int y)
{
	D2D1_SIZE_F size = RenderTarget->GetSize();

	RenderTarget->DrawText(
		text.c_str(),	
		text.size(),
		DWriteTextFormat,
		D2D1::RectF(x, y, size.width + x, size.height + y),
		Brush
	);
}

void D2DRenderer::DrawBox(int left, int top, int right, int bottom)
{
	RenderTarget->DrawRectangle(
		D2D1::RectF(left, top, right, bottom), greenBrush);
}

void D2DRenderer::DrawLine(MathHelper::Vector2F start, MathHelper::Vector2F end)
{
	RenderTarget->DrawLine(
		{ start.x,start.y }, { end.x,end.y}, greenBrush);

	//RenderTarget.drawcircle
}

void D2DRenderer::DrawCircle(Circle& circle)
{
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(
		D2D1::Point2F(circle.Center.x, circle.Center.y),  // 원의 중심
		circle.radius, circle.radius  // 반지름
	);

	RenderTarget->DrawEllipse(&ellipse, greenBrush); //브러쉬가 또 몇개필요할려나.. 초록색? 중심도 그렸으면 좋겠어.. 
}

void D2DRenderer::DrawAABB(AABB& aabb)
{
	RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); //음 좌표계가 이상한거였군.. 어차피 이것들을 그릴때는 월드좌표계를 사용할테니.. 여기에 아이덴티티를 해주는게 맞겠네..
	RenderTarget->DrawRectangle(
		D2D1::RectF(aabb.GetMinX(), aabb.GetMinY(), aabb.GetMaxX(), aabb.GetMaxY()), greenBrush);
}
