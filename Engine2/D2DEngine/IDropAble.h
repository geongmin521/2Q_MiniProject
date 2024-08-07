#pragma once
class UI;
class IDropAble
{
public:
	virtual void OnDrop(UI* ui) = 0; //드래그 에이블 오브젝트의 endDrag가 호출될때 이게 호출
};
