#include "pch.h"
#include "AABB.h"
#include "Bitmap.h"
#include "GameObject.h"
#include "Transform.h"

Bitmap::Bitmap(const std::wstring strFilePath) : Renderer(strFilePath) 
{
	DstRect.right = bitmap->GetSize().width;
	DstRect.bottom = bitmap->GetSize().height;
	
	srcRect.right = bitmap->GetSize().width;
	srcRect.bottom = bitmap->GetSize().height;
}

Bitmap::~Bitmap() 
{

}


void Bitmap::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);
}

void Bitmap::Render(ID2D1RenderTarget* pRenderTarget,float Alpha)  
{
	assert(bitmap != nullptr);
	__super::Render(pRenderTarget); //����Ÿ���� Ʈ�������� ����� ���� ����Ʈ��Ʈ�� �������ʿ�¾�����.. 
	pRenderTarget->DrawBitmap(bitmap, DstRect, Alpha); //D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcRect);
}



