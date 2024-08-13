#include "pch.h"
#include "Transform.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "Container.h"
#include "MoveIcon.h"
#include "TowerBase.h"
#include "GameManager.h"

Container::Container(int id): id(id)
{
	renderOrder += id -1000; //�굵 UI�� �س����ߴµ� �׸��� ������ ����������
	boundBox->SetExtent(75,75); //�̰͵� �����ڿ��� ó���ؾ��ϴ°� �ƴѰ�? 
}

Container::~Container()
{

}

void Container::Clear()
{
	isContain = false;
}

void Container::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
}

void Container::OnDrop(GameObject* ui) 
{
	TowerBase* tower = dynamic_cast<TowerBase*>(ui);
	if (tower == nullptr)
		return;
	if (isContain == true|| gameManager->isBattle == true) //�� ���⼭ ���ӸŴ����� �˻��ϱ� ������.. ���ʿ�.. ��� �巡�׸� ���ϸ� ���İ� ��������ʰԸ����.. 
		return;
	tower->container = this;
	isContain = true;
	ui->transform->SetRelativeLocation(transform->GetWorldLocation());//��ģ���� ������ġ�� �����ϱ�.. 
}

void Container::OnClick()//��Ŭ���ϸ� ����ִ� �ָ� ���ۿ� �־��ְ�.. ���۴� ���콺�� ��� �������־�� �Ǵ°Ű� ���¼���.. �ٸ� �����̳ʸ� ã�°���? 
{ //�̰ſ���.. ��.. 
}
