/*  Timus, здача №1545, ИЕРОГЛИФЫ.
 *  Идея решения.
 *  1. Считываем список иероглифов.
 *     Используем unordered_map: порядок вывода не важен,
 *     вставка - за константное время, повторы игнорируются.
 *     1.1 Вставка происходит в словарь vocabulary,
 *         в котором ключ - первая буква названия иероглифа,
 *         а множество из вторых букв образует значение.
 *  2. Считываем первую букву названия иероглифа letter.
 *  3. Используя первую букву как ключ, находим множество вторых букв,
 			 пробегаемся по этому множеству.
  		 Выодим названия иероглифов в таком виде:
			 "первая буква(letter)+вторая буква(ch - из множества по ключу letter)" */

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
	/* 1 */
	for (size_t i{ 0 }; i < N; ++i)
	{
		std::getline(std::cin, hieroglyphName);
		/* 1.1 */
		vocabulary[hieroglyphName[0]].insert(hieroglyphName[1]);
	}
	char letter{};
	/* 2 */
	std::cin >> letter;
	/* 3 */
	for (const auto& ch : vocabulary[letter])
	{
		std::cout << letter << ch << std::endl;
	}
    return 0;
}
