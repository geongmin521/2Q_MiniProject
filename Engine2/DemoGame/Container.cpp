#include "../D2DEngine/pch.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/D2DRenderer.h"
#include "Container.h"
#include "MoveIcon.h"

Container::Container()
{
	boundBox->SetExtent(75,75); //�̰͵� �����ڿ��� ó���ؾ��ϴ°� �ƴѰ�? 
}

Container::~Container()
{

}

void Container::Clear()
{
	//containUi = nullptr;
}

void Container::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
}

void Container::OnDrop(GameObject* ui) //���⼭ �������� ��� ��������? moveicon�� �����̳ʸ��� ����־���ϳ�? //�ٸ� UI�鵵 ó���ϱ�.. �������� �巡�׾� ����� �ƴ϶��..
//�̰� Ȱ���Ҽ��ִ¹���� ���ݴ����� �ȶ�������.. 
{
	//��ģ���� �巡�׿� ����� �����Ⱦ�����?
	//Ŭ���ϸ� ����.. Ŭ���ϸ� �ٽÿø���?
	//�� Ÿ���� �巡�׾� ����̿����ϴµ� ��.. 
	//�׷� �� �����ϴ���� �Ұɱ׷���? ��ȯ�ؼ� �ٲ��ְ� �ٲ��ְ� ��ȯ�ϰ� ü���̳� �����ɷ��� �Դٰ����ϴ°͵� ���ξ�����.. 
	//�� �Ӹ��� ���� �ȵ��ư��� �����鼭 ��������.. 
}

void Container::OnClick()//��Ŭ���ϸ� ����ִ� �ָ� ���ۿ� �־��ְ�.. ���۴� ���콺�� ��� �������־�� �Ǵ°Ű� ���¼���.. �ٸ� �����̳ʸ� ã�°���? 
{ //�̰ſ���.. ��.. 
}
