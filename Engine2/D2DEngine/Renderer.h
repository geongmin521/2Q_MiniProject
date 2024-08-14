#pragma once
#include "Component.h"

class Renderer : public Component
{
public:
	bool mirror;						// �¿� ���� ����
	D2D1_MATRIX_3X2_F	imageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f  
	std::wstring strBitmapFilePath;
	ID2D1Bitmap* bitmap = nullptr;
	D2D1_RECT_F DstRect;				// RenderTarget�� Destination ����		

	Renderer(const std::wstring strFilePath);
	Renderer() = default;
	virtual ~Renderer();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1) override;
	void LoadD2DBitmap(const std::wstring strFilePath);
	MathHelper::Vector2F GetSize();
	void SetMirror(bool mirror) { mirror = mirror; }
};

