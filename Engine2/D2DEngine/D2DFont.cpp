#include "pch.h"
#include "D2DFont.h"
#include "Helper.h"

#include "D2DRenderer.h"
#include "transform.h"
#include "GameObject.h"

#pragma comment(lib,"dwrite.lib") // ��Ʈ
#pragma comment(lib,"dxgi.lib") // ��Ʈ

D2DFont::D2DFont(const std::wstring _Dialog)
{
	HRESULT hr = D2DRenderer::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &FontBrush);
	if (FAILED(hr)) { OutputDebugString(L"FontBrush ����"); }
	Dialog = _Dialog;
	LoadFont(L"Arial");
	CreateLayoutText(Dialog);
}

D2DFont::~D2DFont()
{
	SAFE_RELEASE(FontBrush);
	SAFE_RELEASE(DWriteTextFormat);
	SAFE_RELEASE(DWriteTextLayout);
}

void D2DFont::SetDialog(std::wstring input)
{
	Dialog = input;
	CreateLayoutText(Dialog);
}

void D2DFont::LoadFont(std::wstring FontName) // �ܺ� ���� ������ �ֵ��� ������ �ʿ�
{
	HRESULT hr = D2DRenderer::GetInstance()->DWriteFactory->CreateTextFormat(
		FontName.c_str(), // FontName ������-���������-�׸�-�۲�-Ŭ�� ���� �۲��̸� Ȯ�ΰ��� �ű� �̸� ���� �ؾߵ�
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		FontSize,   // New Font Size
		L"", //locale
		&DWriteTextFormat
	);

	if (FAILED(hr)) 
	{
		OutputDebugString(L"CreateTextFormat ����");
	}

	CreateLayoutText(Dialog);
}

void D2DFont::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void D2DFont::Render(ID2D1RenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);

	D2D1_MATRIX_3X2_F Transform;
	pRenderTarget->GetTransform(&Transform);
	D2D1_MATRIX_3X2_F finalTransform = Transform * D2D1::Matrix3x2F::Translation(Pos.x, Pos.y);

#if(_DEBUG)
		D2D1_RECT_F FontRect = { Pos.x , Pos.y, BoxSize.width + Pos.x , BoxSize.height+ Pos.y };
		pRenderTarget->SetTransform(finalTransform); // ��λ���
		pRenderTarget->DrawRectangle(FontRect, FontBrush, 2.f);
#endif
		//pRenderTarget->SetTransform(finalTransform); // ��λ���
		pRenderTarget->DrawTextLayout(Pos, DWriteTextLayout, FontBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	
		//pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); // ���� ���ؼ� �ȱ׷��� �׷���?
}

void D2DFont::CreateLayoutText(std::wstring detail)
{
	if (DWriteTextLayout)
	{
		DWriteTextLayout->Release();
		DWriteTextLayout = nullptr;
	}

	HRESULT hr = D2DRenderer::GetInstance()->DWriteFactory->CreateTextLayout(
		detail.c_str(),
		static_cast<UINT32>(detail.length()),
		DWriteTextFormat,
		static_cast<float>(BoxSize.width),
		static_cast<float>(BoxSize.height),
		&DWriteTextLayout
	); // https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1/ne-d2d1-d2d1_draw_text_options
	SetSize(FontSize, { 0, (unsigned int)detail.length() }); //�ؽ�Ʈ�� �����ϴ��� ��������� ����
	//DWriteTextLayout.set
	if (FAILED(hr))
	{
		OutputDebugString(L"CreateTextLayout ����");
	}

	Sort(FontX, FontY);
}

void D2DFont::SetSize(float _FontSize, DWRITE_TEXT_RANGE textRange)
{
	FontSize = _FontSize;
	DWriteTextLayout->SetFontSize(FontSize, textRange);
}

void D2DFont::Sort(Setting _SortX, Setting _SortY)
{
	if (DWriteTextLayout == nullptr) { return; }

	if (_SortX == Setting::LEFT)
	{
		DWriteTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		FontX = LEFT;
	}
	else if (_SortX == Setting::MIDDLE)
	{
		DWriteTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		FontX = MIDDLE;
	}
	else if (_SortX == Setting::RIGHT)
	{
		DWriteTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);	
		FontX = RIGHT;
	}
	else
	{
		DWriteTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		FontX = MIDDLE;
	}

	if (_SortY == Setting::TOP)
	{
		DWriteTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		FontY = TOP;
	}
	else if (_SortY == Setting::MIDDLE)
	{
		DWriteTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		FontY = MIDDLE;
	}
	else if (_SortY == Setting::BOTTOM)
	{
		DWriteTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		FontY = BOTTOM;
	}
	else
	{
		DWriteTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
}
// SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); // �ؽ�Ʈ ������ ���� https://learn.microsoft.com/ko-kr/windows/win32/api/dwrite/ne-dwrite-dwrite_text_alignment
// SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER); // �ؽ�Ʈ ���� ���� https://learn.microsoft.com/ko-kr/windows/win32/api/dwrite/ne-dwrite-dwrite_paragraph_alignment

void D2DFont::SetBoxSize(MathHelper::Vector2F size)
{
	BoxSize.width = size.x; BoxSize.height = size.y;  CreateLayoutText(Dialog);
	DstRect.right = size.x;
	DstRect.bottom = size.y;
}

void D2DFont::SetBoxSize(float width, float height)
{
	BoxSize.width = width; BoxSize.height = height;  CreateLayoutText(Dialog);
	DstRect.right = width;
	DstRect.bottom = height;
}