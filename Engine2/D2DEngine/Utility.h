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
};

