#include "pch.h"
#include "D2DRenderer.h"
#include "Helper.h"
#include "ResourceManager.h"
#include "AABB.h"
#include "Circle.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "Dwrite.lib")

// ����Ʈ ����
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")

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
	this->hWnd = hWnd;
	HRESULT hr = S_OK;
	// COM ��� ����
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		/*	��ġ�� ���ε����� ���� ���ҽ��� ����ϴ�.������ ���� ���ӵǴ� ���� ȿ�������� ����˴ϴ�.
			�̷��� ���ҽ����� Direct2D �� DirectWrite ���͸���
			DirectWrite �ؽ�Ʈ ���� ��ü(Ư�� �۲� Ư���� �ĺ��ϴ� �� ����)�� ���Ե˴ϴ�.
		*/
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		/*
		Direct3D ��ġ�� ���ε��� ���ҽ��� ����ϴ�.
		Direct3D ��ġ�� �սǵ� ���(��: ���÷��� ����, ����, ���� ī�� ���� ��)
		���ҽ��� �ٽ� �����ؾ� �ϴ� ��츦 ����Ͽ� ��� ���⿡ �߾� ����ȭ�Ǿ� �ֽ��ϴ�.
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

	if (SUCCEEDED(hr)) // Ÿ���� ����̽�����Ʈ�� ����
	{
		hr = RenderTarget->QueryInterface(&DeviceContext);
	}

	if (SUCCEEDED(hr))
	{
		// DirectWrite ���͸��� ����ϴ�.
		hr = DWriteCreateFactory( 
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(DWriteFactory),
			reinterpret_cast<IUnknown**>(&DWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite �ؽ�Ʈ ���� ��ü�� ����ϴ�.
		hr = DWriteFactory->CreateTextFormat(
			L"Cooper", // FontName    ������-���������-�׸�-�۲�-Ŭ�� ���� �۲��̸� Ȯ�ΰ���
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			50.0f,   // Font Size
			L"", //locale
			&DWriteTextFormat
		);
		// �ؽ�Ʈ�� ���� �� �������� �߾ӿ� ����ϴ�.
		DWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		DWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	// VRAM ������� ���� ��ü ����
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
	SAFE_RELEASE(DeviceContext);
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
		D2D1::Point2F(circle.Center.x, circle.Center.y),  // ���� �߽�
		circle.radius, circle.radius  // ������
	);

	RenderTarget->DrawEllipse(&ellipse, greenBrush); //�귯���� �� ��ʿ��ҷ���.. �ʷϻ�? �߽ɵ� �׷����� ���ھ�.. 
}

void D2DRenderer::CreateGaussianBlurEffect(ID2D1Bitmap* _Bitmap, const float blurVal)
{  // https://learn.microsoft.com/ko-kr/windows/win32/direct2d/gaussian-blur#optimization-modes ����
	
	if (nullptr == DeviceContext) { return; }

	if (GaussianBlurEffect != nullptr) { GaussianBlurEffect->Release(); }
	DeviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &GaussianBlurEffect);
	if (GaussianBlurEffect == nullptr) { return; }

	GaussianBlurEffect->SetInput(0, _Bitmap); //�̹��� �ε��� https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1_1/nf-d2d1_1-id2d1effect-setinput
	GaussianBlurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, blurVal);

	GaussianBlurEffect->GetOutput(&D2D1Image); // ������ ȿ���� ���� https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1_1/nf-d2d1_1-id2d1effect-getoutput
}

void D2DRenderer::CreateColorMatrixEffect(ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix)
{
	if (nullptr == DeviceContext) { return; }

//	D2D1_MATRIX_5X4_F redEmphasis = {
//	0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
//	0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f
//	};

	if (ApplyColorEffect != nullptr) { ApplyColorEffect->Release(); }
	DeviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &ApplyColorEffect);
	if (ApplyColorEffect == nullptr) { return; }

	ApplyColorEffect->SetInput(0, _Bitmap);
	ApplyColorEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, _ColorMatrix);

	ApplyColorEffect->GetOutput(&D2D1Image);


	//	D2D1_MATRIX_5X4_F colorMatrix = {
//	  0.0f, 0.0f, 0.0f, 0.0f,			//targetColor.r,  // Red ä��
//	  0.0f, 0.0f, 0.0f, 0.0f,			//targetColor.g,  // Green ä��
//	  0.0f, 0.0f, 0.0f, 0.0f,			//targetColor.b,  // Blue ä��
//	  0.0f, 0.0f, 0.0f, 1.0f, 0.0f      // Alpha ä��
//	};
}

// | Red Multiplier | Green Multiplier | Blue Multiplier | Alpha Multiplier | Red Offset   |
// |-------------------- | -------------------- | -------------------- | -------------------- | --------------|
// | Green Multiplier | Red Multiplier | Blue Multiplier | Alpha Multiplier | Green Offset |
// | Blue Multiplier | Green Multiplier | Red Multiplier | Alpha Multiplier | Blue Offset  |
// | Alpha Multiplier | Green Multiplier | Blue Multiplier | Red Multiplier | Alpha Offset |

void D2DRenderer::DrawAABB(AABB& aabb)
{
	RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); //�� ��ǥ�谡 �̻��Ѱſ���.. ������ �̰͵��� �׸����� ������ǥ�踦 ������״�.. ���⿡ ���̵�ƼƼ�� ���ִ°� �°ڳ�..
	RenderTarget->DrawRectangle(
		D2D1::RectF(aabb.GetMinX(), aabb.GetMinY(), aabb.GetMaxX(), aabb.GetMaxY()), greenBrush);
}
