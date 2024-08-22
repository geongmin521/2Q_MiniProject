#include "pch.h"
#include "Bitmap.h"
#include "Transform.h"
#include "HPBar.h"
#include "Artifact.h"

HPBar::HPBar(float& curHp, float& maxHp,std::string tag,bool isFrame) : curHp(curHp), maxHp(maxHp)
{
	this->tag = tag;

	if (isFrame)
	{
		if (tag == "Tower")
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\TowerHPFrame.png");
		else if(tag == "Boss")
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\BossEnemyHP.png");
		else 
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\EnemyHPFrame.png");
	}
	else
	{
		if (tag == "Tower")
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\TowerHPBar.png");
		else if (tag == "Boss")
			hpBar = new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\BossEnemyHPBar.png");
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
		float origin = hpBar->bitmap->GetSize().width;     
		float newOrigin = origin * scaleX;                     
		float move = (origin - newOrigin) / 2.0f;                
		// 1. ������ ���� (�߾� ����)
		transform->SetRelativeScale({ scaleX , 1.0f});        //�� �����ƴҋ� �̷����ϸ� Ʋ�������� �𸣰���
		if(tag =="Boss")
			std::cout << scaleX;
		// 2. ���� �������� ��ġ ����
		if(tag == "Tower")
		transform->SetRelativeLocation({ -move, transform->relativeLocation.y});
		else
		transform->SetRelativeLocation({ -move+20, transform->relativeLocation.y });
	}
	
}

void HPBar::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}
