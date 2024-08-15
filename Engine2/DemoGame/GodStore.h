#include "UI.h"

class Button;
class GodStore :public UI
{
private:
	int compensationId;
	Button* btn;
public:
	GodStore();
	~GodStore();
	void GetCompensation();
};
