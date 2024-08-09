#include "pch.h"
#include "TowerBase.h"
#include "D2DRenderer.h"
#include "InputSystem.h"
#include "Transform.h"
#include "Container.h"
#include "EventSystem.h"
#include "Artifact.h"
#include "Dotween.h" //�̰� �׷� ����°͵� �Ŵ������� �Ѱܾ߰ڳ�.. //�� ���������Դ�.. ���߿� �����.. 

TowerBase::TowerBase(TowerData data)
{
	this->towerData = data; 
	this->name = "Tower";
	EventSystem::GetInstance().get()->Ui.insert(this);
	//���ο� ����Ʈ�� �����? ���̵�� Ű������ ���������.. ������Ʈ�� �Ŵ������� �����鼭 
	//�ð��� duration�̳����� �ڵ� �Ҹ�ǰ�.. ������ �͵鵵 ���̵𿡼� 
	testEffect = 1;
	//�׷� ���⼭ ���� ���̵� �ް� ���̵�� �����ؼ� ���� �޴ٰ� �Ƴ� ���� �⺻������ �ϰ� ������ �� �Ҹ�Ǵ°� ���� ����Ʈ�� ���� �� 0,1 ������ ���� Ʈ������ �Ѱ��ִ½���������.. 
	new DOTween(testEffect, EasingEffect::InOutCirc, StepAnimation::StepLoopForward);//�̷��� Ʈ���� ����°ԾƴѰ�? 
	//���� ������ 0���� 1������ �ƴ� �̷��Ÿ�.. ���ø����� �����ʿ䰡�ֳ�? . ���������� ����������.. 
}

void TowerBase::Update(float deltaTime)
{
	__super::Update(deltaTime);
	if (isMoving)
	{
		transform->SetRelativeLocation(inputSystem->GetMouseState().GetMousePos());
	}
	perHP = (curHP / towerData.HP) * 100;
	if (target != nullptr && target->isActive == false)  
	{
		target = nullptr;
	}
	transform->SetRelativeScale({ testEffect,testEffect }); //���.. 

}

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	int mHp = static_cast<int>(curHP);
	std::wstring hp = std::to_wstring(mHp);
	pRenderTarget->DrawTextW(hp.c_str(), hp.length(), D2DRenderer::GetInstance()->DWriteTextFormat, D2D1::RectF(GetWorldLocation().x - 50, GetWorldLocation().y - 100, GetWorldLocation().x + 50, GetWorldLocation().y),
		D2DRenderer::GetInstance()->Brush);
}



void TowerBase::FindTarget(Collider* col, bool isTargets,bool isHeal)
{
	// Ÿ�� �ڷ� �Ѿ���� Ÿ�ٿ� �������� �����ʿ�


	std::vector<GameObject*> enemys;

	
		for (auto& col : col->collideStatePrev)
		{
			if (!isHeal)
			{
				if (col->owner->name == "Enemy" && col->owner->isActive == true)
				{
					if (std::abs(GetWorldLocation().x - col->owner->GetWorldLocation().x) <= towerData.attackRange &&
						std::abs(GetWorldLocation().y - col->owner->GetWorldLocation().y) <= towerData.attackRange)
					{
						enemys.push_back(col->owner);
					}
				}
			}
			else 
			{
				if (col->owner->name == "Tower" && col->owner->isActive == true)
				{
					if (std::abs(GetWorldLocation().x - col->owner->GetWorldLocation().x) <= towerData.attackRange &&
						std::abs(GetWorldLocation().y - col->owner->GetWorldLocation().y) <= towerData.attackRange)
					{
						enemys.push_back(col->owner);
					}
				}
			}
		}
	

	
	float min = 1000;
	float curMin;
	MathHelper::Vector2F distance;
	GameObject* curTarget = nullptr;
	if (!enemys.empty())
	{
		for (auto& enemy : enemys)
		{
			distance = MathHelper::Vector2F(GetWorldLocation()) - MathHelper::Vector2F(enemy->GetWorldLocation());
			curMin = distance.Length();

			if (min > curMin)
			{
				min = curMin;
				curTarget = enemy;
			}
		}
	}
	if (curTarget != nullptr)
	{
		target = curTarget;
	}
	if (isTargets == true)
	{
		this->targets = enemys;
	}
}

void TowerBase::Attack(float deltaTime)
{
}

void TowerBase::Hit(float damage)
{
	float plusArmor = Artifact::GetInstance().get()->towerPower.Armor;
	curHP -= damage * plusArmor;
}

void TowerBase::Heal(float heal)
{
	float healHP = curHP;
	healHP += heal;
	if (healHP >= towerData.HP)
		curHP = towerData.HP;
	else
		curHP += heal;
}


void TowerBase::BeginDrag(const MouseState& state) //�̰Ŵ� ���콺�� �ϴ°Ŵϱ� ���콺 ������ ��� �����������Ű�����? 
{
	std::cout << "BeginDrag";
	transform->SetRelativeLocation(state.GetMousePos());
	if (container)
		container->Clear();//����ִ°����� ����ֱ�.. ���� ��ȣ�����ϰ��ִ°� ������? 
}

void TowerBase::StayDrag(const MouseState& state)
{
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state)
{
	std::cout << "EndDrag";
}