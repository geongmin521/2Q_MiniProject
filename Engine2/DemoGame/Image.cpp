#include "pch.h"
#include "Bitmap.h"
#include "Bitmap.h"
#include "Image.h"

Image::Image(std::wstring ImagePath)
{
	AddComponent(new Bitmap(L"../Data/Image/" + ImagePath));
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize());
}

Image::~Image()
{
}

void Image::ChangeImage(std::wstring path)
{
	GetComponent<Bitmap>()->LoadD2DBitmap(path);
}

void Image::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void Image::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}
