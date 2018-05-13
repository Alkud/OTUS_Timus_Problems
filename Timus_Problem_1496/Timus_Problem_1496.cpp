/*  Timus, здача №1496, СПАМЕР.
 *  Идея решения.
 *  1. Считываем список аккаунтов accounts.
 *     Используем unordered_set: порядок вывода не важен,
 *     вставка - за константное время.
 *  2. Если вставка не происходит,аккаунт уже встречался в списке,
 *     т.е. за 10 минут с него загружали решение более одного раза,
 *     что соответствует критерию спамера, заносим его в spammers.
 *     Также используем unordered_set - по тем же причинам
 *  3. Выводим список спамеров                                     */

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
	/* 1 */
	for (size_t i{ 0 }; i < N; ++i)
	{
		std::cin >> nextAccount;
		if (false == accounts.insert(nextAccount).second)
		{
			/* 2 */
			spammers.insert(nextAccount);
		}
	}
	/* 3 */
	for (const auto& spammer : spammers)
	{
		std::cout << spammer << std::endl;
	}
    return 0;
}
