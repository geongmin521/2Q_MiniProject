#include "../D2DEngine/pch.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/D2DRenderer.h"
#include "MoveIcon.h"

MoveIcon::MoveIcon(std::wstring filePath) 
{
	AddComponent(new Bitmap(filePath));
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize());//음.. 
}

MoveIcon::~MoveIcon()
{
}

void MoveIcon::Update(float deltaTime) //콜라이더가 없을수도있는데.. 바운드 박스를 콜라이더에서만 업데이트하는건 에바지.. 
{
	__super::Update(deltaTime); //그냥 게임오브젝트의 업데이트로 돌리자.. 
}

void MoveIcon::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
#ifdef _DEBUG
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
#endif
}

void MoveIcon::BeginDrag(const MouseState& state) //이거는 마우스로 하는거니까 마우스 정보가 계속 들어오면좋을거같은데? 
{
	std::cout << "BeginDrag";
	transform->SetRelativeLocation(state.GetMousePos());
}

void MoveIcon::StayDrag(const MouseState& state)
{
	transform->SetRelativeLocation(state.GetMousePos());
}

void MoveIcon::EndDrag(const MouseState& state)
{
	std::cout << "EndDrag";
}
