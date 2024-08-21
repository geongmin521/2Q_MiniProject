#include "pch.h"
#include "Bitmap.h"
#include "Transform.h"
#include "HPBar.h"
#include "Artifact.h"

HPBar::HPBar(float& curHp, float maxHp,std::string tag,bool isFrame) : curHp(curHp), maxHp(maxHp)
{
	if (isFrame)
	{
		if (tag == "Tower")
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\TowerHPFrame.png");
		else if (tag == "Boss")
		{
			Scale = 4.0f;
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\EnemyHPFrame.png");
			transform->SetRelativeScale({ Scale,1.f});
		}
		else
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\EnemyHPFrame.png");
	}
	else
	{
		if (tag == "Tower")
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\TowerHPBar.png");
		else if (tag == "Boss")
		{
			Scale = 4.0f;
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\EnemyHPBar.png");
			transform->SetRelativeScale({ Scale,1.f});
		}
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
		float scaleX = (curHp / maxHp);  // ü�� �ۼ�Ʈ
		float origin = hpBar->bitmap->GetSize().width * Scale;     // ���� ũ��
		float newOrigin = origin * scaleX;
		float move = (origin - newOrigin) / 2.0f;
		// 1. ������ ���� (�߾� ����)
		transform->SetRelativeScale({ scaleX * Scale, 1}); 
		// 2. ���� �������� ��ġ ����
		transform->SetRelativeLocation({ -move, transform->relativeLocation.y});
	}
}

void HPBar::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}
