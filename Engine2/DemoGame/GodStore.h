#include "UI.h"

class Button;
class GodStore :public UI
{
private:
	int compensationId;
	int cost[3] = {20,50,60};
	Button* btn;
	Button* CompensationBtn[3];
public:
	GodStore();
	~GodStore();
	void GetCompensation();
	virtual void Enable() override;
	void TimeScaleIsClick(int num);
};
