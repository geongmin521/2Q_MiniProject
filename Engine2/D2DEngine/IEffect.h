#pragma once

class IEffect  // ���� ���� �Լ�
{
private:

public:
	virtual ~IEffect() = default;
	virtual void EffectUpdate(float deltaTime) = 0;
	virtual void EffectRender() = 0;  // ���⿡ �־�� �ɰ� �����
};
