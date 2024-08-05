#pragma once

class Collider;
class IClickAble // 드래그앤 드롭도 인터페이스로 만들던가.. 활용성이없다면 그냥 핸드를 만들어도가능
{
public:
	virtual void OnClick() = 0;

};

//싱글톤으로 이벤트시스템을 만들어서.. 연락을 받아오고 처리하기.. 