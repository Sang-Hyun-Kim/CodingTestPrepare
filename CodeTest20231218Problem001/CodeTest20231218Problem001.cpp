//
#include <iostream>
#include <set>

int main()
{
	auto func = [](const int& x, const int& y)
		{
			return x > y;
		};
	std::set<int, decltype(func)> s(func);
	s.insert(1);
	s.insert(2);
	s.insert(3);
	for (int num : s)
	{
		std::cout << num << std::endl;
	}
}