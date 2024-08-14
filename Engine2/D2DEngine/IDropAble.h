#pragma once
class UI;
class IDropAble
{
public:
	virtual bool OnDrop(GameObject* ui) = 0; //drag오브젝트의 enddrag가 호출될때 호출
	virtual ~IDropAble() = default;
};
