#pragma once
class IOnMouse
{
public:
	virtual void OnMouse() = 0; //오브젝트위로 마우스가 올라오면 한번호출 
	virtual void StayMouse() = 0; //오브젝트위로 마우스가 올라온중이면
	virtual void OutMouse() = 0; // 마우스가 오브젝트에서 떠날때 호출
};