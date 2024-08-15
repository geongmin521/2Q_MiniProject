#include "UI.h"

class Button;
class GodStore :public UI
{
private:
	int compensationId;
	int cost[3] = {10,30,50};
	Button* btn;
public:
	GodStore();
	~GodStore();
	void GetCompensation();
};
