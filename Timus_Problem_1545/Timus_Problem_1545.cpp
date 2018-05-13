#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main()
{
	std::unordered_map<char, std::unordered_set<char>> vocabulary;
	size_t N{};	
	std::string hieroglyphName{};
	std::getline(std::cin, hieroglyphName);
	N = std::stoull(hieroglyphName);
	for (size_t i{ 0 }; i < N; ++i)
	{
		std::getline(std::cin, hieroglyphName);
		vocabulary[hieroglyphName[0]].insert(hieroglyphName[1]);
	}
	char letter{};
	std::cin >> letter;
	for (const auto& ch : vocabulary[letter])
	{
		std::cout << letter << ch << std::endl;
	}
    return 0;
}

