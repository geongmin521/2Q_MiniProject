#pragma once
class Utility
{
public:
	static int RandomBetween(int min, int max) 
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(min, max);
		return dis(gen);
	}
	static float CalCul(std::string myType, std::string targetType, float damage)
	{
		

		if(targetType == "보스")
			return damage *= 0.75f;

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

	template<typename T>
	static void removeElements(std::list<T*>& origin, const std::list<T*>& remove) { 
		for (auto it = remove.begin(); it != remove.end(); ++it) {
			origin.remove(*it);
		}
	}

	static std::wstring convertFromString(const std::string& str) { //어뭐야.. wstring에서 string형변환하니까.. 한글이 들어오네? 
		std::wstring wstr;
		wstr.assign(str.begin(), str.end());
		return wstr;
	}
};

