#include <iostream>
#include <unordered_set>
#include <algorithm>

int main()
{	
	std::unordered_set<size_t> dates{};
	size_t n{}, d{};
	std::cin >> n;
	for (size_t i{ 0 }; i < n; ++i)
	{
		std::cin >> d;
		dates.insert(d);
	}
	std::cin >> n;
	size_t matchCount{};
	for (size_t i{ 0 }; i < n; ++i)
	{
		std::cin >> d;		
		if (dates.find(d) != dates.end())
		{
			++matchCount;
		}
	}
	std::cout << matchCount;
	return 0;
}
