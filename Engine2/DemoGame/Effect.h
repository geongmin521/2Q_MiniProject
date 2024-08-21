#pragma once
#include "GameObject.h"


enum class EffectId
{
	Heal = 2000,
	Crossbow = 2001,
	Water = 2002,
	Summon = 2003,
	BatBoom = 2004,
	BossKoong = 2005,
	Place = 2006,
	
};
class Effect : public GameObject
{

public:
	int id;
	Effect(int id);
	virtual ~Effect();
	
	void Init(MathHelper::Vector2F location, float _scale,bool loop = false);
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
	std::wstring idtoString(EffectId id)
	{
		switch (id) {
		case EffectId::Heal: return L"Heal";
		case EffectId::Crossbow: return L"Crossbow";
		case EffectId::Water: return L"Water";
		case EffectId::Summon: return L"Summon";
		case EffectId::BatBoom: return L"BatBoom";
		case EffectId::BossKoong: return L"Boss";
		case EffectId::Place: return L"Place";
		default: return L"";
		}
	}
};




