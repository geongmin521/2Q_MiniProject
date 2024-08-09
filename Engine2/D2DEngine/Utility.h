#pragma once
class Utility
{
public:
	static int RandomBetween(int min, int max) //템플릿으로 만들수도? 
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(min, max);
		return dis(gen);
	}
	static float CalCul(std::string myType, std::string targetType, float damage)
	{
		if (myType == "석궁형" && targetType == "속도형")
		{
			return damage *= 1.25;
		}
		else if (myType == "석궁형" && targetType == "방어형")
		{
			return damage *= 0.75;
		}
		else
		{
			return damage;
		}

		if (myType == "성수형" && targetType == "방어형")
		{
			return damage *= 1.25;
		}
		else if (myType == "성수형" && targetType == "속도형")
		{
			return damage *= 0.75;
		}
		else
		{
			return damage;
		}
	}
};

