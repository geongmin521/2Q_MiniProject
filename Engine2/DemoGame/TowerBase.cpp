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
#include "Effect.h"
#include "CommonFunc.h"
#include "Pools.h"
#include "World.h"
#include "D2DRenderer.h"
#include "D2DEffectManager.h"
#include "ColorMatrixEffect.h"
#include "Music.h"
#include "PointSpecularEffect.h"
#include "DataManager.h"
#include "Map.h"	

TowerBase::TowerBase(TowerData data) //최대한위로빼고 달라지는 로직만 적용해야하고..  //오브젝트 풀에서도 init을하고 줘야할거같은데.. 
{
	renderOrder = 100;
	this->towerData = data; 
	name = "Tower"; //이름에서 태그로 변경하기
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
	knockBack = towerData.knockBack;
	AddComponent(new Bitmap(L"..\\Data\\Image\\Tower\\Holyaura" + to_wstring(towerData.level) + L".png"));
	if (towerData.Type == "Pile") // 애만 피격이 이상하네?
	{
		AddComponent(new Bitmap(L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(towerData.name) + L".png"));
		Bitmap* bitmapEffect = dynamic_cast<Bitmap*>(ownedComponents[2]);
		D2DEffectManager::GetInstance()->CreateColorMatrixEffect(Utility::convertFromString(towerData.name), bitmapEffect->bitmap, redEmphasis);
	}
	else if (towerData.Type == "Hidden")
	{
		AddComponent(new Animation(L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(towerData.name) + L".png", L"..\\Data\\CSV\\TowerAni\\" + Utility::convertFromString(towerData.name) + L".csv"));
		D2DEffectManager::GetInstance()->CreateColorMatrixEffect(Utility::convertFromString(towerData.name), GetComponent<Animation>()->bitmap, redEmphasis); // 히트 이펙트
		D2DEffectManager::GetInstance()->CreatePointSpecularEffect(L"HiddenSpecular", GetComponent<Animation>()->bitmap, 0, 0);
		D2DEffectManager::GetInstance()->FindIEffect<PointSpecularEffect>(L"HiddenSpecular")->LightZonter = 300;	
	}
	else
	{
		AddComponent(new Animation(L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(towerData.name) + L".png", L"..\\Data\\CSV\\TowerAni\\TowerBase.csv"));
		D2DEffectManager::GetInstance()->CreateColorMatrixEffect(Utility::convertFromString(towerData.name), GetComponent<Animation>()->bitmap, redEmphasis);
	}

	SetBoundBox(0, 0, 150,150);
	EventSystem::GetInstance().get()->Ui.insert(this);

	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), data.attackRange), CollisionType::Overlap, nullptr, CollisionLayer::Tower));
	TowerType type = (TowerType)(towerData.id / 3);

	if (type == TowerType::Crossbow || type == TowerType::Water || type == TowerType::Hidden) //같은 알고리즘 
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

	Make(HPBar)(curHP, maxHP,"Tower",true).setPosition({0 , -110}).setParent(transform).Get(hpbar);
	Make(HPBar)(curHP, maxHP,"Tower").setPosition({0 , -110}).setParent(transform).Get(hpbar);
	Make(TowerStar)(data.level).setPosition({ 0 , -130 }).setParent(transform);

	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");
}

void TowerBase::Init(MathHelper::Vector2F pos,bool isMerge)
{
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2000 + towerData.level));
	effect->Init({ pos.x - 10, pos.y + 15 }, 1.0f); //이펙트 생성
	if(isMerge)
			effect->Init({ pos.x - 10, pos.y + 65}, 1.0f); //이펙트 생성
	
	isDead = false;
	hitEffct = false;
	StatUpdate();
	transform->SetRelativeLocation(pos); 
	transform->SetRelativeScale({ 1.0f,1.0f });  //합칠떄 작아진 크기 다시복구 
	GetComponent<FiniteStateMachine>()->SetNextState("Idle");
}

void TowerBase::StatUpdate()
{
	// 일단 값 때려 넣기
	if (towerData.Type == "Water")
	{
		curHP = (prevHp + (artifact->WaterPower.hpLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::WaterHpUp)).power));
		maxHP = towerData.HP + (artifact->WaterPower.hpLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::WaterHpUp)).power);
		hpbar->Init(maxHP);
		curSpeed = (towerData.attackSpeed - (artifact->WaterPower.spdLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::WaterSpeedUp)).power));
		if (curSpeed < 0)
			curSpeed = 0;

	}
	else if (towerData.Type == "Pile")
	{
		curHP = (prevHp + (artifact->PilePower.hpLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::PileHpUp)).power));
		maxHP = towerData.HP + (artifact->PilePower.hpLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::PileHpUp)).power);
		hpbar->Init(maxHP);
		curSpeed = (towerData.attackSpeed - (artifact->PilePower.spdLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::PileSpeedUp)).power));
		if (curSpeed < 0)
			curSpeed = 0;

	}
	else if (towerData.Type == "Crossbow")
	{
		curHP = (prevHp + (artifact->CrossbowPower.hpLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::BowHpUp)).power));
		maxHP = towerData.HP + (artifact->CrossbowPower.hpLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::BowHpUp)).power);
		hpbar->Init(maxHP);
		curSpeed = (towerData.attackSpeed - (artifact->CrossbowPower.spdLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::BowSpeedUp)).power));
		if (curSpeed < 0)
			curSpeed = 0;

	}
	else if (towerData.Type == "HolyCross")
	{
		curHP = (prevHp + (artifact->HolyPower.hpLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::HolyHpUp)).power));
		maxHP = towerData.HP + (artifact->HolyPower.hpLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::HolyHpUp)).power);
		hpbar->Init(maxHP);
		curSpeed = (towerData.attackSpeed - (artifact->HolyPower.spdLevel * dataManager->getArtifactData(static_cast<int>(ArtifactId::HolySpeedUp)).power));
		if (curSpeed < 0)
			curSpeed = 0;
		
	}
	if (artifact->isOwned(static_cast<int>(ArtifactId::SilverRing)))
	{
		ArtifactData art = dataManager->getArtifactData(static_cast<int>(ArtifactId::SilverRing));
		GetComponent<CircleCollider>()->circle->radius = towerData.attackRange + art.power;
	}

	if (artifact->isOwned(static_cast<int>(ArtifactId::Laurel)))
	{
		ArtifactData art = dataManager->getArtifactData(static_cast<int>(ArtifactId::Laurel));
		knockBack = towerData.knockBack + art.power;
	}
}


void TowerBase::Update(float deltaTime)
{
	
	__super::Update(deltaTime);

	//transform->SetRelativeScale({ testEffect, testEffect });
	if (towerData.Type == "Hidden")
	{
		float X = GetComponent<Animation>()->CenterPos.x;
		float Y = GetComponent<Animation>()->CenterPos.y;
		D2DEffectManager::GetInstance()->FindIEffect<PointSpecularEffect>(L"HiddenSpecular")->SetLightPos(X + 5, Y - 10);
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
	if (isMerged == true)
	{
		new DOTween(alpha, EasingEffect::InOutCirc, StepAnimation::StepOnceForward, 3.f, 0.2f, 1.f);
		isMerged = false;
	}
}

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{


	if (towerData.Type == "Hidden")
	{
		Animation* animationComponent = GetComponent<Animation>();
		static_cast<Renderer*>(animationComponent);
	
		D2D1_MATRIX_3X2_F Transform = static_cast<Renderer*>(animationComponent)->imageTransform *
			transform->worldTransform *
			D2DRenderer::cameraTransform;

		pRenderTarget->SetTransform(Transform);
		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->
			FindEffect(L"HiddenSpecular"),
			{ 0 ,0 }, GetComponent<Animation>()->srcRect);
		__super::Render(pRenderTarget);

		if (AttackRangeCircle)
		{
			D2DRenderer::GetInstance()->DrawCircle(transform->worldTransform.dx, transform->worldTransform.dy, GetComponent<CircleCollider>()->circle->radius, 5.0f);
		}
	}

	if (hitEffct == false )
	{
		if(towerData.Type != "Hidden")
		__super::Render(pRenderTarget,alpha);
		
		if (AttackRangeCircle && towerData.Type != "Pile")
		{
			D2DRenderer::GetInstance()->DrawCircle(transform->worldTransform.dx, transform->worldTransform.dy, GetComponent<CircleCollider>()->circle->radius, 5.0f);
		}
	}
	else
	{
		if (towerData.Type == "Pile")
		{
			Bitmap* BitmapComponent = dynamic_cast<Bitmap*>(ownedComponents[2]);
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

	// 일단 여기에다 넣어보고 나중에 좋은 위치 생각
	if (towerData.Type == "Pile")
	{
		Music::soundManager->PlayMusic(Music::eSoundList::PileHitted, Music::eSoundChannel::TowerHitted);
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

void TowerBase::BeginDrag(const MouseState& state)//이 부분은 이동가능하게.. 
{
	if (gameManager->isBattle == true || isMerge == true) //전투중에는 드래그 불가 //아 여기만 막는다고 전체가 막히는게 아니지?
		return;
	if (container)
		container->Clear();

	// GetComponent<CircleCollider>()->circle->radius 이걸로 공격 범위 알 수 있고
	AttackRangeCircle = true;
}

void TowerBase::StayDrag(const MouseState& state) 
{
	if (gameManager->isBattle == true || isMerge == true) //시작을 못하면 이것도 아예안들어왔으면좋겠는데.. 흠.. //일단 전투시작이 늦게 들어와야하고.. 
		//ondrop 이벤트도 막아야함 .. 그게또 위치를 변경해주는거라.. 
		return;
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state) //드래그앤 드롭이니까.. 
{	
	Music::soundManager->PlayMusic(Music::eSoundList::TowerReplace, Music::eSoundChannel::Effect1);
	//container
	AttackRangeCircle = false;
}

void TowerBase::FailDrop()
{
	if (container != nullptr) //이거 널검사하는거 겁나 귀찮은데 define으로 만들까?
	{
		transform->SetRelativeLocation({ container->GetWorldLocation().x ,container->GetWorldLocation().y -50});
		container->isContain = true;
	}
}

void TowerBase::OnDoubleClick()
{
	if (gameManager->isBattle == true || isMerge == true || isMerged == true) //전투중이거나 합성재료타워거나 합성연출중인 타워일경우 스킵
		return;
	GameObject* newTower =nullptr;
	std::vector<TowerBase*> towers;
	int merageCount = 2; //합칠떄필요한 자신제외 같은 기물수
	int minDis = INT_MAX;
	float distance = 0;
	for (auto& tower : owner->m_GameObjects)
	{
		TowerBase* sameTower = dynamic_cast<TowerBase*>(tower);
		if(sameTower == nullptr) continue;  
		if(tower->GetActive() == true && sameTower != this && sameTower->towerData.id == this->towerData.id && sameTower->isMerge == false)
		{
			if (towers.size() == merageCount)
			{
				std::vector<TowerBase*>::iterator farTower; //뺼타워 위치 담아둘곳
				for (auto nearTower = towers.begin(); nearTower != towers.end(); ++nearTower)
				{
					distance = ((*nearTower)->GetWorldLocation() - this->GetWorldLocation()).Length(); //이미들어가있는것안에서 가장작은거 찾고
					if(distance < minDis)
					{
						minDis = distance; //여기서 minDis가 가장작은것의 거리가되고
						farTower = nearTower;
					}
				}
				distance = (sameTower->GetWorldLocation() - this->GetWorldLocation()).Length(); //다음 넣을것과의 거리
				if (distance > minDis) //이제넣을 타워가 가장먼타워보다 더 멀면 
					continue;
				towers.erase(farTower);
			}
			towers.push_back(sameTower);
		}
	}

	if(towers.size() == merageCount && towerData.level < 3)
	{
		newTower = Pools::GetInstance().get()->PopPool(towerData.id + 1);
		dynamic_cast<TowerBase*>(newTower)->Init(this->GetWorldLocation(),true);
		dynamic_cast<TowerBase*>(newTower)->isMerged = true;
		auto targetloca = GetWorldLocation();
		for(auto& sametower : towers)
		{
			auto& sameloca = sametower->transform->relativeLocation;
			new DOTween(sametower->transform->GetRelativeScale().x, EasingEffect::OutCirc, StepAnimation::StepOnceForward, 1.f, 1, 0.1f);
			new DOTween(sametower->transform->GetRelativeScale().y, EasingEffect::OutCirc, StepAnimation::StepOnceForward, 1.f, 1, 0.1f);
			new DOTween(sameloca.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 0.75f, sameloca.x, targetloca.x);
			new DOTween(sameloca.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 0.75f, sameloca.y, targetloca.y);
			sametower->isMerge = true;
			//Pools::GetInstance().get()->AddPool(sametower); //같은타워 풀에넣고
			if(sametower->container)
			sametower->container->Clear();
		}
		Pools::GetInstance().get()->AddPool(this); // 자기도 풀에넣고
		if (this->container)
		{
			dynamic_cast<TowerBase*>(newTower)->container = this->container;
			this->container->Clear();//여기서 컨테이너를 새타워에 넘겨주고 자기껀 없애고?
		}
	}
}

void TowerBase::OnMouse() 
{
	MathHelper::Vector2F pos = transform->GetWorldLocation();
	//모든 타워는 컨테이너 위에 존재함
	if (container == nullptr)
		return;
	if (container->id < 4)	
		gameManager->getObject("ToolTip")->transform->SetRelativeLocation({ pos.x + 200 , pos.y - 50 });	
	else	
		gameManager->getObject("ToolTip")->transform->SetRelativeLocation({ pos.x + 200 , pos.y });

	GameObject* tooltip = gameManager->getObject("ToolTip");
	tooltip->SetActive(true);
	tooltip->renderOrder = renderOrder + 1;
	std::wstring path = L"../Data/Image/UI/tooltip/" + Utility::convertFromString(towerData.name) + L".png";
	gameManager->getObject("ToolTip")->GetComponent<Bitmap>()->LoadD2DBitmap(path);
}

void TowerBase::OutMouse() 
{
	gameManager->getObject("ToolTip")->SetActive(false);
}
