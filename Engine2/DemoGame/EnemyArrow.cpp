#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Music.h"
#include "TowerBase.h"
#include "EnemyArrow.h"
#include "Bitmap.h"

EnemyArrow::EnemyArrow()
{
	SetBoundBox(0, 0, 40, 36);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Arrow"));
	AddComponent(new Movement(transform));
	renderOrder = 100;
}

EnemyArrow::~EnemyArrow()
{
}

void EnemyArrow::Init(GameObject* target, MathHelper::Vector2F location)
{
	this->target = target;
	transform->SetRelativeLocation({ location.x + 50.0f,location.y - 20.f });

	position[2] = target->GetWorldLocation();
	position[0] = transform->GetRelativeLocation();
	MathHelper::Vector2F mid = (position[2] + position[0]) / 2;
	if (position[2].x - position[0].x > 800.f)
	{
		sec = 3.0f;
		height = 300.f;
	}
	else if (position[2].x - position[0].x > 200.f)
	{
		sec = 1.0f;
		height = 80.f;
	}
	else
	{
		sec = 0.15f;
		height = 5.f;
	}
	mid.y += -height;
	position[1] = mid;
}

void EnemyArrow::Update(float deltaTime)
{
	preDir = curDir;
	__super::Update(deltaTime);

	curDir = GetWorldLocation();

	float moveX = curDir.x - preDir.x;
	float moveY = curDir.y - preDir.y;
	float moveR = atan2(moveY, moveX) * (180.0f / PI);
	if (target->isActive == true)
	{

		position[2] = target->GetWorldLocation();
		ellipsedTime += deltaTime;
		t = ellipsedTime / sec;
		if (t >= 1.0f)
		{
			t = 1;
		}
		MathHelper::Vector2F rotate = (QuadraticBezierPoint(t, position));

		transform->SetRelativeRotation(moveR);
		transform->SetRelativeLocation(QuadraticBezierPoint(t, position));
	}
	else
	{
		isActive = false;
	}

	if (std::abs(target->GetWorldLocation().x - GetWorldLocation().x) <= 1.0f ||
		std::abs(target->GetWorldLocation().y - GetWorldLocation().y) <= 1.0f)
	{
		TowerBase* tower = dynamic_cast<TowerBase*>(target);
		tower->Hit(30);
		isActive = false;
	}
}

void EnemyArrow::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

MathHelper::Vector2F EnemyArrow::QuadraticBezierPoint(float t, MathHelper::Vector2F position[])
{
	MathHelper::Vector2F p0 = LinearInterpolate(t, position[0], position[1]);
	MathHelper::Vector2F p1 = LinearInterpolate(t, position[1], position[2]);

	return MathHelper::Vector2F((1 - t) * p0.x, (1 - t) * p0.y) + MathHelper::Vector2F(t * p1.x, t * p1.y);
}

MathHelper::Vector2F EnemyArrow::LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1)
{
	return MathHelper::Vector2F((1 - t) * p0.x, (1 - t) * p0.y) + MathHelper::Vector2F(t * p1.x, t * p1.y);
}
