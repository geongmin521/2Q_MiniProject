#pragma once
class Utility
{
public:
	static int RandomBetween(int min, int max) //���ø����� �������? 
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(min, max);
		return dis(gen);
	}
	static float CalCul(std::string myType, std::string targetType, float damage)
	{
		if (myType == "������" && targetType == "�ӵ���")
		{
			return damage *= 1.25;
		}
		else if (myType == "������" && targetType == "�����")
		{
			return damage *= 0.75;
		}
		else
		{
			return damage;
		}

		if (myType == "������" && targetType == "�����")
		{
			return damage *= 1.25;
		}
		else if (myType == "������" && targetType == "�ӵ���")
		{
			return damage *= 0.75;
		}
		else
		{
			return damage;
		}
	}
};

