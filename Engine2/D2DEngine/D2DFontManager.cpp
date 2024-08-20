#include "pch.h"
#include "D2DFontManager.h"
#include "Helper.h"

D2DFontManager::~D2DFontManager()
{
	SAFE_RELEASE(FontSetBuilder);
	SAFE_RELEASE(DWriteFactory);

	for (auto& font : fontMap)
	{
		if (font.second != nullptr) font.second->Release();
	}
}

void D2DFontManager::InitializeDWrite()
{
	HRESULT hresult = S_OK;

	hresult = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory5),
		reinterpret_cast<IUnknown**>(&DWriteFactory)
	);

	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create DWrite factory.", L"Error", MB_OK);
		return;
	}

	hresult = DWriteFactory->CreateFontSetBuilder(&FontSetBuilder);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create font set builder.", L"Error", MB_OK);
		return;
	}
}

void D2DFontManager::LoadFont(std::wstring fontFilePath, std::wstring fontName)
{
	HRESULT hresult = S_OK;

	if (fontMap.find(fontName) != fontMap.end())
	{
		MessageBoxW(nullptr, L"Font with the specified name already exists.", L"Error", MB_OK);
		return;
	}

	IDWriteFontFile* FontFile{ nullptr };
	IDWriteFontSet* FontSet{ nullptr };
	IDWriteFontCollection1* FontCollection{ nullptr };
	IDWriteFontFamily* FontFamily{ nullptr };
	IDWriteLocalizedStrings* FontFamilyNames{ nullptr };

	// 폰트 파일 참조 생성
	hresult = DWriteFactory->CreateFontFileReference(
		fontFilePath.c_str(),
		nullptr,
		&FontFile);

	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create font file reference.", L"Error", MB_OK);
		return;
	}

	// 폰트 파일을 FontSetBuilder에 추가
	FontSetBuilder->AddFontFile(FontFile);

	BOOL isSupported;
	DWRITE_FONT_FILE_TYPE fileType;
	UINT32 numberOfFonts;

	FontSetBuilder->CreateFontSet(&FontSet); // 폰트 세트를 생성합니다. 이 세트는 추가된 폰트 파일들을 포함합니다.

	// 폰트 세트에서 폰트 컬렉션 생성
	hresult = DWriteFactory->CreateFontCollectionFromFontSet(FontSet,&FontCollection);

	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create font collection from font set.", L"Error", MB_OK);
		return;
	}

	hresult = FontCollection->GetFontFamily(index, &FontFamily);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to get font family.", L"Error", MB_OK);
		return;
	}

	// 폰트 패밀리 얻기
	hresult = FontFamily->GetFamilyNames(&FontFamilyNames);  // FontFamilyNames 초기화
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to get font family names.", L"Error", MB_OK);
		return;
	}

	// 폰트 패밀리의 이름을 얻기 위해 로컬라이즈된 문자열 컬렉션을 가져옵니다.
	WCHAR familyName[MAX_PATH];
	hresult = FontFamilyNames->GetString(0, familyName, MAX_PATH);
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to get string.", L"Error", MB_OK);
		return;
	}

#if( _DEBUG)
	wprintf(L"Loaded Font: %s\n", familyName);  // 디버깅 출력
#endif

	IDWriteTextFormat* NewFont = nullptr;
	AddFont(familyName, FontCollection, &NewFont);

	fontMap.insert(std::make_pair(fontName, NewFont));

	FontFile->Release();
	FontSet->Release();
	FontCollection->Release();
	FontFamily->Release();
	index++;
}

void D2DFontManager::AddFont(std::wstring fontName, IDWriteFontCollection1* pFontCollection, IDWriteTextFormat** ppTextFormat)
{
	HRESULT hresult = S_OK;

	 DWriteFactory->CreateTextFormat(
		fontName.c_str(),
		pFontCollection,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		10.f,
		L"en-us",
		ppTextFormat
	);

	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to create text format.", L"Error", MB_OK);
		return;
	}
}

IDWriteTextFormat* D2DFontManager::FindFont(const std::wstring& keyName)
{
	auto it = fontMap.find(keyName);

	if (it != fontMap.end())
	{
		return it->second; 
	}

	return nullptr;  
}
