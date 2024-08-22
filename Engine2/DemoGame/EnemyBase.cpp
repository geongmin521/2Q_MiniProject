#include "pch.h"
#include "HPBar.h"
#include "EnemyBase.h"
#include "Artifact.h"
#include "D2DRenderer.h"
#include "Animation.h"
#include "FiniteStateMachine.h"
#include "Factory.h"
#include "EnemyFSM.h"
#include "Movement.h"
#include "EnemyFunc.h"
#include "Transform.h"
#include "TowerBase.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Artifact.h"
#include "D2DEffectManager.h"
#include "ColorMatrixEffect.h"
#include "World.h"
#include "ProductionCamera.h"

EnemyBase::EnemyBase(EnemyData data)
{
	renderOrder = 100;
	this->enemyData = data;
	name = "Enemy";
	id = 1001;
	curHP = enemyData.HP;
	curMaxHP = enemyData.HP;
	SetBoundBox(0, 0, 50, 50); 
	if (artifact->isOwned(static_cast<int>(ArtifactId::Wine)))
	{
		this->enemyData.attackSpeed *= 0.75f;
	}
	if (artifact->isOwned(static_cast<int>(ArtifactId::Mirror)))
	{
		this->enemyData.speed *= 0.75f;
	}
	
	if(enemyData.Type =="Boss")  //일단 넣긴해야되서 나중에수정
		AddComponent(new Bitmap(L"..\\Data\\Image\\Enemy\\DarkauraBoss.png" ));
	else
		AddComponent(new Bitmap(L"..\\Data\\Image\\Enemy\\DarkauraNormal.png"));



	AddComponent(new Animation(L"..\\Data\\Image\\Enemy\\" + Utility::convertFromString(enemyData.name) + L".png", L"..\\Data\\CSV\\EnemyAni\\" + Utility::convertFromString(enemyData.name) + L".csv"));

	transform->SetRelativeScale({ 0.5f,0.5f });
	AddComponent(new CircleCollider(boundBox,new Circle(transform->GetWorldLocation(), enemyData.detectRange), CollisionType::Overlap, this, CollisionLayer::Enemy));
	Make(HPBar)(curHP, curMaxHP,enemyData.Type,true).setPosition({ 20 , -200}).setParent(transform).Get<HPBar>();
	Make(HPBar)(curHP, curMaxHP,enemyData.Type).setPosition({ 0 , -200}).setParent(transform).Get<HPBar>();
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<EnemyIdle>("Idle");
	fsm->CreateState<EnemyShared>("Shared");
	fsm->CreateState<EnemyAttack>("Attack");
	fsm->CreateState<EnemyDead>("Death");
	fsm->CreateState<EnemyAbility>("Ability");
	fsm->SetNextState("Idle");
	SetAbility(data.ability);
	AddComponent(new Movement(transform));
	
	D2D1_MATRIX_5X4_F redEmphasis =
	{
		0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
		0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	D2DEffectManager::GetInstance()->CreateColorMatrixEffect(Utility::convertFromString(enemyData.name), GetComponent<Animation>()->bitmap, redEmphasis);
	if (enemyData.Type == "Deffend") // 방어형일 경우 크기 수정 및 레이어 순서 변경 (적 레이어는 속도> 보스> 방어> 일반 순)
	{
		transform->SetRelativeScale({ 0.65f, 0.65f });
		renderOrder = 101;
	}
	if (enemyData.Type == "Boss") { renderOrder = 102; transform->SetRelativeScale({ 1.0f, 1.0f });}
	if (enemyData.Type == "Speed") { renderOrder = 103; }
}

void EnemyBase::SetAbility(std::string ability)
{
	if (ability == "None") //노말
	{
		attack = [this]() {EnemyFunc::NormalAttack(target[0], curATK); };
	}
	else if (ability == "Throw") //원거리
	{
		attack = [this]() {EnemyFunc::RangedAttack(target[0], this->GetWorldLocation(), curATK); };
	}
	else if (ability == "Destroy") //폭발
	{
		attack = [this]() {EnemyFunc::BombAttack(this, target[0], curATK); };
	}
	else if (ability == "SpawnVat") //박쥐소환 보스
	{
		attack = [this]() {EnemyFunc::BossAttack(this ,target[0], curATK); };
		Ability = [this]() {EnemyFunc::spawnBat(this->GetWorldLocation()); };
	}
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float deltaTime) 
{	
	__super::Update(deltaTime);
	if (isHited) //맞았을경우
	{
		elapsedTime += deltaTime;
		if (elapsedTime > hitedTime)
		{
			isHited = false;
			elapsedTime = 0;
		}
	}
	if (artifact->isOwned(static_cast<int>(ArtifactId::Garlic)) && isGalric == true)
	{

		ticTime += deltaTime;
		damageTimer += deltaTime;

		if (damageTimer >= 1.f)
		{
			Hit(dataManager->getArtifactData(static_cast<int>(ArtifactId::Garlic)).power);
			damageTimer = 0.f;
		}
		if (ticTime > 5.f)
		{
			isGalric = false;
			ticTime = 0.f;
		}
	}

	if (hitEffct)
	{
		hitEffctDelay += deltaTime * 10;

		if (hitEffctDelay > 2)
		{
			hitEffctDelay = 0;
			hitEffct = false;
		}
	}

	if (enemyData.Type == "Boss")
	{
		if (transform->GetWorldLocation().x < 1700 && isStoppage == false)
		{
			isProduction = true;
		}
	}

}

void EnemyBase::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	if (hitEffct == false)
	{
		__super::Render(pRenderTarget);
	}
	else if(hitEffct == true)
	{
		Animation* animationComponent = GetComponent<Animation>();
		static_cast<Renderer*>(animationComponent);

		D2D1_MATRIX_3X2_F Transform = static_cast<Renderer*>(animationComponent)->imageTransform *
			transform->worldTransform *
			D2DRenderer::cameraTransform;

		pRenderTarget->SetTransform(Transform);

		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->
			FindEffect(Utility::convertFromString(enemyData.name)),
			{ 0 ,0 }, GetComponent<Animation>()->srcRect);

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

}

void EnemyBase::Hit(float damage, float knockback)
{
	if (enemyData.Type == "Boss") knockback = 0;
	float Hpdame = curHP - damage;  
	if (Hpdame <= 0)
	{
		curHP = 0;
	}
	else
	{
		curHP = Hpdame;
	}
	if(knockback !=0)
	isHited = true;
	GetComponent<Movement>()->SetVelocity({ knockback,0 });
	if (artifact->isOwned(static_cast<int>(ArtifactId::Garlic)))
	{
		isGalric = true;
	}
	hitEffct = true;
}

void EnemyBase::Heal(float heal)
{
	float healHP = curHP;
	healHP += heal;
	if (healHP >= enemyData.HP)
		curHP = enemyData.HP;
	else
		curHP += heal;
}

void EnemyBase::Attack()
{
	attack();
}

void EnemyBase::ability()
{
	Ability();
}

void EnemyBase::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void EnemyBase::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void EnemyBase::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void EnemyBase::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
