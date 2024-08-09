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

	template<typename T>
	static void removeElements(std::list<T*>& origin, const std::list<T*>& remove) { //지울객체를 실제로 지우기 이걸 유틸의 템플릿으로 만들까?
		for (auto it = remove.begin(); it != remove.end(); ++it) {
			origin.remove(*it);
		}
	}
};

