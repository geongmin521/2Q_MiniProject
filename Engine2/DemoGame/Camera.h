#pragma once
#include "..//D2DEngine/GameObject.h"

class Camera : public GameObject
{
public:
	Camera(); //게임오브젝트의 생성자는 create object로 일관되기때문에 매개변수를 전달할수없음..
	~Camera();

	// 구체 클래스를 만드는게 좋을까? 아니면 그냥 게임오브젝트에 컴포넌트만 붙여주는게 나을까..
	//나중에 개발할때 뭐가 더 편한지 생각하면 되는데.. 
};

