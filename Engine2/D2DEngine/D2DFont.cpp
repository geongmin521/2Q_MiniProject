#include "pch.h"
#include "D2DFont.h"
#include "Helper.h"

#include "D2DRenderer.h"
#include "transform.h"

#pragma comment(lib,"dwrite.lib") // ��Ʈ
#pragma comment(lib,"dxgi.lib") // ��Ʈ

D2DFont::D2DFont()
{
	// ������ ���ÿ� �귯�� ���������� ����
	 HRESULT hr = D2DRenderer::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &FontBrush);
	 if (FAILED(hr)) { OutputDebugString(L"FontBrush ����"); }
}

D2DFont::~D2DFont()
{
	SAFE_RELEASE(FontBrush);
	SAFE_RELEASE(DWriteTextFormat);
	SAFE_RELEASE(DWriteTextLayout);
	if (transform) { delete transform; transform = nullptr; }
}

void D2DFont::LoadFont(std::wstring FontName)
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
}

void D2DFont::Update(float deltaTime)
{
	if (transform != nullptr)
	{
		transform->Update(deltaTime); // Ʈ������ ������Ʈ �ϱ� ���� �ϴ� �߰�
	}
	
}

void D2DFont::DrawFont(D2D1_COLOR_F color)
{
 	FontBrush->SetColor(color); // ���ϴ� �÷� ����
	if (IsTransform == false)
	{
#if(_DEBUG)
		D2D1_RECT_F FontRect = { Pos.x ,Pos.y, BoxSize.width + Pos.x , BoxSize.height + Pos.y };
		D2DRenderer::GetInstance()->GetRenderTarget()->DrawRectangle(FontRect, FontBrush, 3.f);
#endif
		D2DRenderer::GetInstance()->GetRenderTarget()->DrawTextLayout(Pos, DWriteTextLayout, FontBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
	else
	{
#if(_DEBUG)
		D2D1_RECT_F FontRect = {transform->worldTransform.dx , transform->worldTransform.dy, 
							    BoxSize.width + transform->worldTransform.dx , BoxSize.height + transform->worldTransform.dy };
		D2DRenderer::GetInstance()->GetRenderTarget()->DrawRectangle(FontRect, FontBrush, 3.f);
#endif
		D2DRenderer::GetInstance()->GetRenderTarget()->DrawTextLayout({ transform->worldTransform.dx,transform->worldTransform.dy }, DWriteTextLayout, FontBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
 
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
		OutputDebugString(L"CreateTextLayout ����");
	}

}

void D2DFont::SetSize(float _FontSize, DWRITE_TEXT_RANGE textRange)
{
	FontSize = _FontSize;
	DWriteTextLayout->SetFontSize(FontSize, textRange);
}

void D2DFont::Sort(Setting _Sort)
{
	if (_Sort == Setting::LEFT)
	{
		DWriteTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	}
	else if (_Sort == Setting::MIDDLE)
	{
		DWriteTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}
	else if (_Sort == Setting::RIGHT)
	{
		DWriteTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);	
	}
	else
	{
		DWriteTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}

}

void D2DFont::SetFontLocation(Setting _Sort)
{
	if (_Sort == Setting::TOP)
	{
		DWriteTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
	else if (_Sort == Setting::MIDDLE)
	{
		DWriteTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	else if (_Sort == Setting::BOTTOM)
	{
		DWriteTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
	}
	else
	{
		DWriteTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
}

void D2DFont::OnTransform()
{
	transform = new Transform();
	IsTransform = true;
}

// SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); // �ؽ�Ʈ ������ ���� https://learn.microsoft.com/ko-kr/windows/win32/api/dwrite/ne-dwrite-dwrite_text_alignment
// SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER); // �ؽ�Ʈ ���� ���� https://learn.microsoft.com/ko-kr/windows/win32/api/dwrite/ne-dwrite-dwrite_paragraph_alignment