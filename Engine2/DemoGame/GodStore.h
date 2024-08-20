#include "UI.h"

class Button;
class GodStore :public UI
{
private:
	int compensationId;
	int cost[3] = {20,40,50};
	Button* btn;
	Button* CompensationBtn[3];
public:
	GodStore();
	~GodStore();
	void GetCompensation();
	void TimeScaleIsClick(int num);
};
