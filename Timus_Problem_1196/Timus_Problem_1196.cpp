/*  Timus, здача №1196, УРОК ИСТОРИИ.
 *  Идея решения.
 *  1. Считываем список дат преподавателя dates.
 *     Используем unordered_set: даты уже отсортированы,
 *     повторы игнорируются, вставка - за константное время.
 *  2. Считываем список дат студента.
 *     2.1 Каждый раз, когда дата встречается в списке студента,
 *         увеличиваем счётчик совпадение matchCount
 *  3. Выводим количество совпадений                               */

#include <iostream>
#include <unordered_set>
#include <algorithm>

int main()
{
	std::unordered_set<size_t> dates{};
	size_t n{}, d{};
	std::cin >> n;
	/* 1 */
	for (size_t i{ 0 }; i < n; ++i)
	{
		std::cin >> d;
		dates.insert(d);
	}
	std::cin >> n;
	size_t matchCount{};
	/* 2 */
	for (size_t i{ 0 }; i < n; ++i)
	{
		std::cin >> d;
		if (dates.find(d) != dates.end())
		{
			/* 2.1 */
			++matchCount;
		}
	}
	/* 3 */
	std::cout << matchCount;
	return 0;
}
