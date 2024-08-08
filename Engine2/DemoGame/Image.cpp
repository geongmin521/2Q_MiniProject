#include "../D2DEngine/pch.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Bitmap.h"
#include "Image.h"

Image::Image(std::wstring ImagePath)
{
	AddComponent(new Bitmap(ImagePath));
}

Image::~Image()
{
}

void Image::ChangeImage(std::wstring path)
{
	GetComponent<Bitmap>()->LoadD2DBitmap(path);
}

void Image::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
