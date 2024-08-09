#include "pch.h"
#include "Transform.h"
#include "InputSystem.h"
#include "EventSystem.h"
#include "Bitmap.h"
#include "D2DRenderer.h"
#include "Container.h"
#include "MoveIcon.h"

MoveIcon::MoveIcon(std::wstring filePath) 
{
	AddComponent(new Bitmap(filePath));
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize());//��.. 
	renderOrder = 50;
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
	if (container)
		container->Clear();//����ִ°����� ����ֱ�.. ���� ��ȣ�����ϰ��ִ°� ������? 
}

void MoveIcon::StayDrag(const MouseState& state)
{
	transform->SetRelativeLocation(state.GetMousePos());
}

void MoveIcon::EndDrag(const MouseState& state)
{
	std::cout << "EndDrag";
}
