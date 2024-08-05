#pragma once
#include "../D2DEngine/World.h"
class TitleWorld : public World //월드는 그냥 오브젝트의 집합이라고 만 생각하고.. 
{
private:
public:
	TitleWorld(); //사실 상속받은 월드들이 달라지는거는 그냥 월드에 필요한 오브젝트들이 다른것밖에없음
	//즉 업데이트랑 렌더를 재정의할필요없고 오브젝트를 각 월드의 생성에서처리하는걸로하자..
	~TitleWorld();
	
};

