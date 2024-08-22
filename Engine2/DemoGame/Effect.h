#pragma once
#include "GameObject.h"


enum class EffectId
{
	Place = 2000,
	Summon = 2001,
	Summon2 = 2002,
	Summon3 = 2003,
	Heal = 2004,
	Crossbow = 2005,
	Crossbow2 = 2006,
	Crossbow3= 2007,
	Water = 2008,
	Water2 = 2009,
	Water3 = 2010,
	BatBoom = 2011,
	BossKoong = 2012,
	
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
		case EffectId::Place: return L"Place";
		case EffectId::Summon: return L"Summon";
		case EffectId::Summon2: return L"Summon2";
		case EffectId::Summon3: return L"Summon3";
		case EffectId::Heal: return L"Heal";
		case EffectId::Crossbow: return L"Crossbow";
		case EffectId::Crossbow2: return L"Crossbow2";
		case EffectId::Crossbow3: return L"Crossbow3";
		case EffectId::Water: return L"Water";
		case EffectId::Water2: return L"Water2";
		case EffectId::Water3: return L"Water3";
		case EffectId::BatBoom: return L"BatBoom";
		case EffectId::BossKoong: return L"BossKoong";
		default: return L"Heal";
		}
	}
};




