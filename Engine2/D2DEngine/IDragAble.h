#pragma once

class MouseState;
class IDragAble
{
public:
	virtual void BeginDrag(const MouseState& state) = 0; 
	virtual void StayDrag( const MouseState & state) = 0;
	virtual void EndDrag(  const MouseState  & state) = 0;
	virtual ~IDragAble() = default;
};