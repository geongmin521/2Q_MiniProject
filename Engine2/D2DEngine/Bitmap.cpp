#include "pch.h"
#include "AABB.h"
#include "Bitmap.h"

Bitmap::Bitmap(const std::wstring strFilePath) : Renderer(strFilePath) 
{
	DstRect.right = bitmap->GetSize().width;
	DstRect.bottom = bitmap->GetSize().height;
}

Bitmap::~Bitmap() 
{

}


void Bitmap::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);
}

void Bitmap::Render(ID2D1RenderTarget* pRenderTarget)  
{
	assert(bitmap != nullptr);
	__super::Render(pRenderTarget);
	pRenderTarget->DrawBitmap(bitmap);
}

