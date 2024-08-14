#pragma once

class IEffect  // 순수 가상 함수
{
private:

public:
	virtual ~IEffect() = default;
	virtual void EffectUpdate(float deltaTime) = 0;
	virtual void EffectRender() = 0;  // 여기에 있어야 될가 고민중
};
