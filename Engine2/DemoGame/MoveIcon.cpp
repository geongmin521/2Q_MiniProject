#include "../D2DEngine/pch.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/D2DRenderer.h"
#include "MoveIcon.h"

MoveIcon::MoveIcon() //�θ� �����ڴ� ������ ȣ����״ϱ�.. �ڵ����� ��ϵɵ�?
{

	//�̰Ŵ� �ݶ��̴��� �ƴϰ� �׳� ó���ϸ�ɵ�? 
	AddComponent(new Bitmap(L"..\\Data\\Image\\castle.png"));
	transform->SetRelativeScale({ 0.1f, 0.1f });
	transform->SetRelativeLocation({500,100});
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize());//��.. 
}

MoveIcon::~MoveIcon()
{
}

void MoveIcon::Update(float deltaTime) //�ݶ��̴��� ���������ִµ�.. �ٿ�� �ڽ��� �ݶ��̴������� ������Ʈ�ϴ°� ������.. 
{
	__super::Update(deltaTime); //�׳� ���ӿ�����Ʈ�� ������Ʈ�� ������.. 
}

void MoveIcon::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
#ifdef _DEBUG
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
#endif
}

void MoveIcon::BeginDrag(const MouseState& state) //�̰Ŵ� ���콺�� �ϴ°Ŵϱ� ���콺 ������ ��� �����������Ű�����? 
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
