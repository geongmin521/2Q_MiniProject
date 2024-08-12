#pragma once

class IDoubleClickAble
{
public:
	virtual void OnDoubleClick() = 0;
	virtual ~IDoubleClickAble() = default;
};
