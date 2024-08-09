#include "pch.h"
#include "D2DFont.h"
#include "Helper.h"

#include "D2DRenderer.h"
#include "transform.h"
#include "GameObject.h"

#pragma comment(lib,"dwrite.lib") // 폰트
#pragma comment(lib,"dxgi.lib") // 폰트

D2DFont::D2DFont(const std::wstring _Dialog)
{
	// 생성과 동시에 브러쉬 검은색으로 조정
	 HRESULT hr = D2DRenderer::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &FontBrush);
	 if (FAILED(hr)) { OutputDebugString(L"FontBrush 실패"); }
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

void D2DFont::LoadFont(std::wstring FontName) // 외부 파일 읽을수 있도록 수정이 필요
{
	HRESULT hr = D2DRenderer::GetInstance()->DWriteFactory->CreateTextFormat(
		FontName.c_str(), // FontName 제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능 거기 이름 다음 해야됨
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
		OutputDebugString(L"CreateTextFormat 실패");
	}

	CreateLayoutText(Dialog);
}

void D2DFont::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void D2DFont::Render(ID2D1RenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);

	D2D1_RECT_F FontRect;

	// 로컬 좌표계로의 변환 매트릭스를 정의
	D2D1_MATRIX_3X2_F localTransform = D2D1::Matrix3x2F::Translation(Pos.x, Pos.y);

	D2D1_MATRIX_3X2_F Transform;
	pRenderTarget->GetTransform(&Transform);
	D2D1_MATRIX_3X2_F finalTransform = Transform * localTransform;

#if(_DEBUG)
		FontRect = { Pos.x , Pos.y, BoxSize.width + Pos.x , BoxSize.height+ Pos.y };
		pRenderTarget->SetTransform(finalTransform); // 고민사항
		pRenderTarget->DrawRectangle(FontRect, FontBrush, 2.f);
#endif
		pRenderTarget->SetTransform(finalTransform); // 고민사항
		pRenderTarget->DrawTextLayout(Pos, DWriteTextLayout, FontBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); // 렌더 통해서 안그려서 그런가?
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

	//DWriteTextLayout.set
	if (FAILED(hr))
	{
		OutputDebugString(L"CreateTextLayout 실패");
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
// SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); // 텍스트 정렬을 변경 https://learn.microsoft.com/ko-kr/windows/win32/api/dwrite/ne-dwrite-dwrite_text_alignment
// SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER); // 텍스트 정렬 관련 https://learn.microsoft.com/ko-kr/windows/win32/api/dwrite/ne-dwrite-dwrite_paragraph_alignment



