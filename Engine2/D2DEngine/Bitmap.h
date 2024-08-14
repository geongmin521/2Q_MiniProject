#pragma once
#include "Renderer.h"

class Bitmap : public Renderer 
{
public:
	Bitmap(const std::wstring strFilePath);
	virtual ~Bitmap();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1) override;
};

