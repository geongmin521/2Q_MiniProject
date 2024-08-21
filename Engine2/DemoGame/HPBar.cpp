#include "pch.h"
#include "Bitmap.h"
#include "Transform.h"
#include "HPBar.h"
#include "Artifact.h"

HPBar::HPBar(float& curHp, float maxHp,std::string tag,bool isFrame) : curHp(curHp), maxHp(maxHp)
{
	this->tag = tag;
	if (tag == "Boss")
		scale = 4.0f;
	if (isFrame)
	{
		if (tag == "Tower")
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\TowerHPFrame.png");
		else
		{
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\EnemyHPFrame.png");
			transform->SetRelativeScale({ scale,1.f });
		}
	}
	else
	{
		if (tag == "Tower")
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\TowerHPBar.png");
		else
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\EnemyHPBar.png");
	}
	AddComponent(hpBar); 
	renderOrder = 101;
	this->isFrame = isFrame;
}



HPBar::~HPBar()
{
}

void HPBar::Init(float maxHp)
{
	this->maxHp = maxHp;
}

void HPBar::Update(float deltaTime) 
{
	__super::Update(deltaTime);

	if (!isFrame)
	{
		float scaleX = (curHp / maxHp);  // ü�� �ۼ�Ʈ 10
		float origin = hpBar->bitmap->GetSize().width * scale;     
		float newOrigin = origin * scaleX;                     
		float move = (origin - newOrigin) / 2.0f;                
		// 1. ������ ���� (�߾� ����)
		if(tag == "Boss")
		transform->SetRelativeScale({ scaleX * scale, 1.0f});        //�� �����ƴҋ� �̷����ϸ� Ʋ�������� �𸣰���
		else
		transform->SetRelativeScale({ scaleX , 1.0f });
		// 2. ���� �������� ��ġ ����
		transform->SetRelativeLocation({ -move, transform->relativeLocation.y});
	}
	
}

void HPBar::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}
