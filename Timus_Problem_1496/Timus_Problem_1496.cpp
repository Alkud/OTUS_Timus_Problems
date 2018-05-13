#include <iostream>
#include <string>
#include <unordered_set>


int main()
{
	size_t N{};
	std::cin >> N;
	std::unordered_set<std::string> accounts{};
	std::string nextAccount{};
	std::unordered_set<std::string> spammers{};
	for (size_t i{ 0 }; i < N; ++i)
	{
		std::cin >> nextAccount;
		if (false == accounts.insert(nextAccount).second)
		{
			spammers.insert(nextAccount);
		}
	}
	for (const auto& spammer : spammers)
	{
		std::cout << spammer << std::endl;
	}
    return 0;
}

