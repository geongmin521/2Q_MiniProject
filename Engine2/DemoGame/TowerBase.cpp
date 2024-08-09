#include "pch.h"
#include "TowerBase.h"
#include "D2DRenderer.h"
#include "InputSystem.h"
#include "Transform.h"
#include "Container.h"
#include "EventSystem.h"
#include "Artifact.h"
#include "Dotween.h" //이거 그럼 만드는것도 매니저한테 넘겨야겠네.. //와 동민이형왔다.. 나중에 물어보자.. 

TowerBase::TowerBase(TowerData data)
{
	this->towerData = data; 
	this->name = "Tower";
	EventSystem::GetInstance().get()->Ui.insert(this);
	//새로운 이펙트를 만들면? 아이디랑 키값으로 만들어지고.. 업데이트는 매니저에서 돌리면서 
	//시간이 duration이끝나면 자동 소멸되고.. 생성한 것들도 아이디에서 
	testEffect = 1;
	//그럼 여기서 만들어서 아이디를 받고 아이디로 접근해서 값을 받다가 아냐 값을 기본값으로 하고 본인이 걍 소멸되는게 낫고 이펙트에 쓰일 값 0,1 까지의 값을 트윈한테 넘겨주는식으로하자.. 
	new DOTween(testEffect, EasingEffect::InOutCirc, StepAnimation::StepLoopForward);//이렇게 트윈을 만드는게아닌가? 
	//값은 무조건 0부터 1까지고 아니 이럴거면.. 템플릿으로 만들필요가있나? . 생성관리가 쉽지않은데.. 
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
	transform->SetRelativeScale({ testEffect,testEffect }); //됬다.. 

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
	// 타워 뒤로 넘어간적은 타겟에 안잡히게 수정필요


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


void TowerBase::BeginDrag(const MouseState& state) //이거는 마우스로 하는거니까 마우스 정보가 계속 들어오면좋을거같은데? 
{
	std::cout << "BeginDrag";
	transform->SetRelativeLocation(state.GetMousePos());
	if (container)
		container->Clear();//담겨있는공간에 비워주기.. 서로 상호참조하고있는게 맞을까? 
}

void TowerBase::StayDrag(const MouseState& state)
{
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state)
{
	std::cout << "EndDrag";
}