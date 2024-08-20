#include "pch.h"
#include "TowerBase.h"
#include "InputSystem.h"
#include "Transform.h"
#include "Container.h"
#include "EventSystem.h"
#include "Artifact.h"
#include "Factory.h"
#include "Dotween.h" 
#include "Animation.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "TowerFunc.h"
#include "FiniteStateMachine.h"
#include "GameManager.h"
#include "TowerFsm.h"
#include "HPBar.h"
#include "TowerStar.h"
#include "ToolTip.h"
#include "Effect.h"
#include "CommonFunc.h"
#include "Pools.h"
#include "World.h"
#include "D2DRenderer.h"
#include "Dotween.h"
#include "D2DRenderer.h"
#include "D2DEffectManager.h"
#include "ColorMatrixEffect.h"
#include "Music.h"

TowerBase::TowerBase(TowerData data) //�ִ������λ��� �޶����� ������ �����ؾ��ϰ�..  //������Ʈ Ǯ������ init���ϰ� ����ҰŰ�����.. 
{
	renderOrder = 100;
	this->towerData = data; 
	name = "Tower"; //�̸����� �±׷� �����ϱ�
	id = towerData.id;
	curHP = towerData.HP;
	D2D1_MATRIX_5X4_F redEmphasis =
	{
		0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
		0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	id = towerData.id;
	curHP = towerData.HP;
	prevHp = towerData.HP;
	maxHP = towerData.HP;
	curSpeed = towerData.attackSpeed;


	if (towerData.Type == "Pile")
	{
		AddComponent(new Bitmap(L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(towerData.name) + L".png"));
		D2DEffectManager::GetInstance()->CreateColorMatrixEffect(Utility::convertFromString(towerData.name), GetComponent<Bitmap>()->bitmap, redEmphasis);
		transform->SetRelativeScale({ 0.8f,0.8f });
	}
	else if (towerData.Type == "Hidden")
	{
		AddComponent(new Animation(L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(towerData.name) + L".png", L"..\\Data\\CSV\\TowerAni\\" + Utility::convertFromString(towerData.name) + L".csv"));
		D2DEffectManager::GetInstance()->CreateColorMatrixEffect(Utility::convertFromString(towerData.name), GetComponent<Animation>()->bitmap, redEmphasis);
	}
	else
	{
		AddComponent(new Animation(L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(towerData.name) + L".png", L"..\\Data\\CSV\\TowerAni\\TowerBase.csv"));
		D2DEffectManager::GetInstance()->CreateColorMatrixEffect(Utility::convertFromString(towerData.name), GetComponent<Animation>()->bitmap, redEmphasis);
	}

	SetBoundBox(0, 0, 150,150);
	EventSystem::GetInstance().get()->Ui.insert(this);

	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), data.attackRange), CollisionType::Overlap, this, CollisionLayer::Tower));
	TowerType type = (TowerType)(towerData.id / 3);

	if (type == TowerType::Crossbow || type == TowerType::Water || type == TowerType::Hidden) //���� �˰��� 
	{
		Search = [this]() { CommonFunc::FindTarget(*GetComponent<CircleCollider>(), "Enemy", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::FireBullet(this,target[0], this->transform->GetWorldLocation(), towerData.id); };
	}
	if (type == TowerType::Pile)
	{
		Search = [this]() { CommonFunc::FindTargets(*GetComponent<CircleCollider>(), "Enemy", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::MeleeAttack(this,target); };
	}
	if (type == TowerType::HolyCross)
	{
		Search = [this]() { CommonFunc::FindTargets(*GetComponent<CircleCollider>(), "Tower", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::Heal(this ,target); };
	}

	FiniteStateMachine* fsm = new FiniteStateMachine();

	Make(HPBar)(curHP, maxHP).setPosition({ 0 , -90 }).setParent(transform).Get(hpbar);

	for (int i = 0; i < data.level; i++)//�����ǥ�� ����ϴµ��̰� �׳� ����ִ¹�������ұ�? 	
		Make(TowerStar)().setPosition({ 20.f * i , -115 }).setParent(transform);

	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");
	//testEffect = 1; //��Ʈ�� ���� ���� //���� ����ɸŰ������� �ϳ� �������ְ� �����ؼ� �־��ֱ�
	//new DOTween(testEffect, EasingEffect::InBounce, StepAnimation::StepOnceForward);

}

//������ƮǮ���� Ÿ���� ���ö�.. init�� ���ľ߰ڴµ�? �ʱ�ȭ ���¿� ���� �˰�����.. 

void TowerBase::Init(MathHelper::Vector2F pos)
{
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2003));
			effect->Init({ pos.x - 5, pos.y + 53}, 0.90f); //����Ʈ ����

	hitEffct = false;
	StatUpdate();
	transform->SetRelativeLocation(pos); 
	if (towerData.Type == "Pile")
		transform->SetRelativeScale({ 0.8f,0.8f });  //��ĥ�� �۾��� ũ�� �ٽú��� Ÿ��ũ�� ���氡�ɼ��־ �ϴ� �̷��� 
	else
		transform->SetRelativeScale({ 1.0f,1.0f });
	GetComponent<FiniteStateMachine>()->SetNextState("Idle");

	
}

void TowerBase::StatUpdate()
{
	// �ϴ� �� ���� �ֱ�
	if (towerData.Type == "Water")
	{
		curHP = (prevHp + (artifact->WaterPower.hpLevel * 20));
		maxHP = towerData.HP + (artifact->WaterPower.hpLevel * 20);
		hpbar->Init(maxHP);
		curSpeed = (towerData.attackSpeed + (artifact->WaterPower.spdLevel * 0.2));
	}
	else if (towerData.Type == "Pile")
	{
		curHP = (prevHp + (artifact->PilePower.hpLevel * 20));
		maxHP = towerData.HP + (artifact->PilePower.hpLevel * 20);
		hpbar->Init(maxHP);
		curSpeed = (towerData.attackSpeed + (artifact->PilePower.spdLevel * 0.2));
	}
	else if (towerData.Type == "Crossbow")
	{
		curHP = (prevHp + (artifact->BowPower.hpLevel * 20));
		maxHP = towerData.HP + (artifact->BowPower.hpLevel * 20);
		hpbar->Init(maxHP);
		curSpeed = (towerData.attackSpeed + (artifact->BowPower.spdLevel * 0.2));
	}
	else if (towerData.Type == "HolyCross")
	{
		curHP = (prevHp + (artifact->HolyPower.hpLevel * 20));
		maxHP = towerData.HP + (artifact->HolyPower.hpLevel * 20);
		hpbar->Init(maxHP);
		curSpeed = (towerData.attackSpeed + (artifact->HolyPower.spdLevel * 0.2));
	}
	if (artifact->isOwned(static_cast<int>(ArtifactId::SilverRing)))
	{
		GetComponent<CircleCollider>()->circle->radius = towerData.attackRange + artifact->Range;
	}

	if (artifact->isOwned(static_cast<int>(ArtifactId::Laurel)))
	{

	}
}


void TowerBase::Update(float deltaTime)
{
	__super::Update(deltaTime);
	//transform->SetRelativeScale({ testEffect, testEffect });

	if (hitEffct)
	{
		hitEffctDelay += deltaTime * 10;

		if (hitEffctDelay > 2)
		{
			hitEffctDelay = 0;
			hitEffct = false;
		}
	}

	if (isMerge == true)
	{
		mergeTime += deltaTime;
		if (mergeTime >= 0.6f)
		{
			if(container)
				container->Clear();
			Pools::GetInstance().get()->AddPool(this);
			mergeTime = 0;
			isMerge = false;
		}
	}
}

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	int mHp = static_cast<int>(curHP);
	int mAtkspd = static_cast<int>(towerData.attackSpeed);
	std::wstring hp = std::to_wstring(mHp) + L" " + std::to_wstring(mAtkspd);
	pRenderTarget->DrawTextW(hp.c_str(), hp.length(), D2DRenderer::GetInstance()->DWriteTextFormat, D2D1::RectF(GetWorldLocation().x - 50, GetWorldLocation().y - 300, GetWorldLocation().x + 50, GetWorldLocation().y),
		D2DRenderer::GetInstance()->Brush);
	if (hitEffct == false)
	{
		__super::Render(pRenderTarget);
	}
	else
	{
		if (towerData.Type == "Pile")
		{
			Bitmap* BitmapComponent = GetComponent<Bitmap>();
			static_cast<Renderer*>(BitmapComponent);

			D2D1_MATRIX_3X2_F Transform = static_cast<Renderer*>(BitmapComponent)->imageTransform *
				transform->worldTransform *
				D2DRenderer::cameraTransform;

			pRenderTarget->SetTransform(Transform);

			D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->
				FindEffect(Utility::convertFromString(towerData.name)));
		}
		else
		{
			Animation* animationComponent = GetComponent<Animation>();
			static_cast<Renderer*>(animationComponent);

			D2D1_MATRIX_3X2_F Transform = static_cast<Renderer*>(animationComponent)->imageTransform *
				transform->worldTransform *
				D2DRenderer::cameraTransform;

			pRenderTarget->SetTransform(Transform);

			D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->
				FindEffect(Utility::convertFromString(towerData.name)),
				{ 0 ,0 }, GetComponent<Animation>()->srcRect);
		}		
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void TowerBase::Attack(float deltaTime)
{
	AttackFunc();
}

void TowerBase::Hit(float damage, float knockback)
{
	float damegelHP = curHP;
	damegelHP -= damage;
	if (damegelHP <= 0)
		curHP = 0;
	else
	curHP -= damage;
	hitEffct = true;

	// �ϴ� ���⿡�� �־�� ���߿� ���� ��ġ ����
	if (towerData.Type == "Pile")
	{
		Music::soundManager->PlayMusic(Music::eSoundList::PileHitted, Music::eSoundChannel::Effect2);
	}
}

void TowerBase::Heal(float heal)
{
	float healHP = curHP;
	healHP += heal;
	if (healHP >= maxHP)
		curHP = maxHP;
	else
		curHP += heal;
}

void TowerBase::BeginDrag(const MouseState& state)//�� �κ��� �̵������ϰ�.. 
{
	if (gameManager->isBattle == true || isMerge == true) //�����߿��� �巡�� �Ұ� //�� ���⸸ ���´ٰ� ��ü�� �����°� �ƴ���?
		return;
	if (container)
		container->Clear();
}

void TowerBase::StayDrag(const MouseState& state) 
{
	if (gameManager->isBattle == true || isMerge == true) //������ ���ϸ� �̰͵� �ƿ��ȵ����������ڴµ�.. ��.. //�ϴ� ���������� �ʰ� ���;��ϰ�.. 
		//ondrop �̺�Ʈ�� ���ƾ��� .. �װԶ� ��ġ�� �������ִ°Ŷ�.. 
		return;
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state) //�巡�׾� ����̴ϱ�.. 
{	
	//container
}

void TowerBase::FailDrop()
{
	if (container != nullptr) //�̰� �ΰ˻��ϴ°� �̳� �������� define���� �����?
		transform->SetRelativeLocation(container->GetWorldLocation());

}

void TowerBase::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void TowerBase::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void TowerBase::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void TowerBase::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void TowerBase::OnDoubleClick()
{
	GameObject* newTower =nullptr;
	std::vector<TowerBase*> towers;
	int merageCount = 2; //��ĥ���ʿ��� �ڽ����� ���� �⹰��
	int minDis = INT_MAX;
	float distance = 0;
	for (auto& tower : owner->m_GameObjects)
	{
		TowerBase* sameTower = dynamic_cast<TowerBase*>(tower);
		if(sameTower != nullptr && tower->GetActive() == true && sameTower != this && sameTower->towerData.id == this->towerData.id)
		{
			if (towers.size() == merageCount)
			{
				std::vector<TowerBase*>::iterator farTower; //�EŸ�� ��ġ ��ƵѰ�
				for (auto nearTower = towers.begin(); nearTower != towers.end(); ++nearTower)
				{
					distance = ((*nearTower)->GetWorldLocation() - this->GetWorldLocation()).Length(); //�̵̹��ִ°;ȿ��� ���������� ã��
					if(distance < minDis)
					{
						minDis = distance; //���⼭ minDis�� ������������ �Ÿ����ǰ�
						farTower = nearTower;
					}
				}
				distance = (sameTower->GetWorldLocation() - this->GetWorldLocation()).Length(); //���� �����Ͱ��� �Ÿ�
				if (distance > minDis) //�������� Ÿ���� �����Ÿ������ �� �ָ� 
					continue;
				towers.erase(farTower);
			}
			towers.push_back(sameTower);
		}
	}

	if(towers.size() == merageCount && towerData.level < 3)
	{
		newTower = Pools::GetInstance().get()->PopPool(towerData.id + 1);
		dynamic_cast<TowerBase*>(newTower)->Init(this->GetWorldLocation());
		auto targetloca = GetWorldLocation();
		for(auto& sametower : towers)
		{
			auto& sameloca = sametower->transform->relativeLocation;
			new DOTween(sametower->transform->GetRelativeScale().x, EasingEffect::OutCirc, StepAnimation::StepOnceForward, 1.f, 1, 0.1f);
			new DOTween(sametower->transform->GetRelativeScale().y, EasingEffect::OutCirc, StepAnimation::StepOnceForward, 1.f, 1, 0.1f);
			new DOTween(sameloca.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 0.75f, sameloca.x, targetloca.x);
			new DOTween(sameloca.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 0.75f, sameloca.y, targetloca.y);
			sametower->isMerge = true;
			//Pools::GetInstance().get()->AddPool(sametower); //����Ÿ�� Ǯ���ְ�
			if(sametower->container)
			sametower->container->Clear();
		}
		Pools::GetInstance().get()->AddPool(this); // �ڱ⵵ Ǯ���ְ�
		if (this->container)
		{
			dynamic_cast<TowerBase*>(newTower)->container = this->container;
			this->container->Clear();//���⼭ �����̳ʸ� ��Ÿ���� �Ѱ��ְ� �ڱⲫ ���ְ�?
		}
	}
}

void TowerBase::OnMouse() 
{
	MathHelper::Vector2F pos = transform->GetWorldLocation();
	gameManager->getObject("ToolTip")->transform->SetRelativeLocation({ pos.x + 200 , pos.y });
	GameObject* tooltip = gameManager->getObject("ToolTip"); //�� ��¥ �̰� �𸣰ڳ�.. ���߿� ã�ƺ���.
	tooltip->SetActive(true); //�ƴ� �̰Ŷ� ���� �������? 
	std::wstring path = L"../Data/Image/UI/tooltip/" + Utility::convertFromString(towerData.name) + L".png";
	gameManager->getObject("ToolTip")->GetComponent<Bitmap>()->LoadD2DBitmap(path);
}

void TowerBase::OutMouse() 
{
	gameManager->getObject("ToolTip")->SetActive(false);
}
