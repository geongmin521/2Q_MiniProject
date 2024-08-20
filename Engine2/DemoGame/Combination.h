#pragma once
#include "UI.h"

class Image;
class Combination :public UI
{
private:
	int curPage;
	Image* recipe;
public:
	Combination();
	~Combination();
	void NextPage(bool left);
};
