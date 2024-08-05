#pragma once
#include "Renderer.h"

class Bitmap : public Renderer //이렇게 되면 그릴지말지에 대한 aabb도 렌더가 들고있어야겠지? 
{
public:
	Bitmap(const std::wstring strFilePath);
	virtual ~Bitmap();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
};
