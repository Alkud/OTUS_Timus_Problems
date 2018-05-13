/*  Timus, здача №1837, ЧИСЛО ИСЕНБАЕВА.
 *  Идея решения.
 *  1. Используем вспомоглательную функцию splitTeamString
 *     для преобразования строки из трёх фамилий в unordered_set.
 *  2. Считываем построчно списки команд.
 *  3. Преобразуем список-строку в список-множество.
 *     Заносим список-множество в список команд teams.
 *     3.1 Если в списке-строке встречается Isenbaev, поднимаем флаг mentionIsenbaev.
 *         Если Isenbaev не встретился, мы не можем определить числа Исинбаева
 *				 для остальных участников (все undefined). Тест №4 - как раз этот вариант.
 *  4. Если Isenbaev упоминается, заносим его в два словаря: participants и distances.
 *     В distances ключом является число Исинбаева (дистанция), значением - фамилия участника,
 *     в participants  - наоборот, ключ - фамилия, значение - дистанция до Исинбаева.
 *  5. Начинаем перебирать списки команд, выбрасывая их по определённому условию
 * 	   до опустошения списка. На каждой итерации увеличиваем текущую дистанцию
 *		 от Исинбаева currentDistance, начальное значение - 0.
 *     Идея: у Исинбаева дистанция 0, находим все кманды, где он играл, присваиваем участникам дистанцию 1,
 *           убираем из списка команд те, где встретился Исинбаев,
 *					 снова перебираем список команд, находим те, в которых встречаются фамилии тех,
 *					 у кого дистанция 1, присваиваем им дистанцию 2, убираем эти команды из общего списка,
 *           и т.д., пока список не опустеет.
 *     Для проверки используем список участников из словаря distances,
 *     distances[currentDistance], имеющих одинаковое текущее число Исинбаева.
 *     Начинаем с 0, т.е. с Исинбаева, если он упоминался в списках команд.
 *     5.1 Пробегаемся по спику очередной команды
 *         5.1.1 Если в текущей команде встречается фамилия из distances[currentDistance],
 *							 т.е. участника, для которого уже определена дистанция,
 *							 пробегаемся по списку этой команды,
 *               5.1.1.1 всем, кроме участника с уже определённой дистанцией присваиваем
 *                       дистанцию на 1 больше, т.е. заносим в словарь с ключом currentDistance + 1
 *               5.1.1.2 удаляем текущую команду из общего списка, переходим к следующей. std::list позволяет это делать
 *         5.1.2 В противном случае, переходим к следующей команде
 *    5.2 Перед переходом на следующую итерацию, увеличиваем текущую дистанцию.
 *        5.2.1 Если список distances[currentDistance] пуст, значит, на текущей итерации
 *              не встретились команды с участниками с известной дистанцией,
 *   						выходим из цикла.
 *    6. Пробегаемся по списку оставшихся команд
 *       6.1 Присваиваеим им дистанцию -1 (не определна), заносим в словарь
 * 					 distances с ключом -1.
 *     что соответствует критерию спамера, заносим его в spammers.
 *    7. Преобразуем словарь по дистанции в словарь по фамилии.
 *       Для этого пробегаем по словарю distances по значениям числа Исинбаева
 *       7.1 Пробегаем по множеству участников с данным числом Исинбаева,
 *           заносим в словарь participants с ключом 'фамилия' и значением дистанции
 *    8. Пробегаем по словарю participants,
 * 			 выводим фамилию и дистанцию,
 *       если дистанция равна -1, выводим undefined.
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <list>
#include <map>
#include <algorithm>

using teamSet = std::unordered_set<std::string>;

/* 1 */
teamSet splitTeamString(std::string teamString)
{
	teamSet result{};
	auto first{ 0U };
	auto last{ teamString.find_first_of(' ', 0) };
	while (last != std::string::npos)
	{
		result.insert(teamString.substr(first, last - first));
		first = last + 1;
		last = teamString.find_first_of(' ', first);
	}
	result.insert(teamString.substr(first));
	return result;
}

int main()
{
	unsigned int N{};
	std::string inputString{};
	std::getline(std::cin, inputString);
	N = std::stoul(inputString);
	std::list<teamSet> teams{};
	const std::string Isenbaev{ "Isenbaev" };
	bool mentionIsenbaev{false};
	for (size_t i{ 0 }; i < N; ++i)
	{
		/* 2 */
		std::getline(std::cin, inputString);
		/* 3 */
		teams.push_back(splitTeamString(inputString));
		if (mentionIsenbaev != true &&
			inputString.find(Isenbaev) != std::string::npos)
		{
			/* 3.1 */
			mentionIsenbaev = true;
		}
	}
	std::map<int, std::unordered_set<std::string>> distances{};
	std::map<std::string, int> participants{};
	if (mentionIsenbaev)
	{
		/* 4 */
		participants[Isenbaev] = 0;
		distances[0].insert(Isenbaev);
	}
	int currentDistance{ 0 };
	/* 5 */
	while (teams.empty() != true)
	{
		/* 5.1 */
		for (auto team{ teams.begin() }; team != teams.end();)
		{
			if (std::find_first_of(	team->begin(), team->end(),
									distances[currentDistance].begin(), distances[currentDistance].end())
				!= team->end())
			{
				/* 5.1.1 */
				for (const auto& member : *team)
				{
					if (distances[currentDistance].find(member) == distances[currentDistance].end())
					{
						/* 5.1.1.1 */
						distances[currentDistance + 1].insert(member);
					}
				}
				/* 5.1.1.2 */
				auto tmp{ team };
				std::advance(team, 1);
				teams.erase(tmp);
			}
			else
			{
				/* 5.1.2*/
				++team;
			}
		}
		/* 5.2 */
		++currentDistance;
		if (distances[currentDistance].empty() == true)
		{
			/* 5.2.1 */
			distances.erase(currentDistance);
			break;
		}
	}
	/* 6 */
	for (const auto& team : teams)
	{
		/* 6. 1 */
		for (const auto& member : team)
		{
			distances[-1].insert(member);
		}
	}
	/* 7 */
	for (const auto& distance : distances)
	{
		/* 7.1 */
		for (const auto& member : distance.second)
		{
			participants[member] = distance.first;
		}
	}
	/* 8 */
	for (const auto& participant : participants)
	{
		std::cout << participant.first << " " <<
			(participant.second > -1 ? std::to_string(participant.second) : "undefined") <<
			std::endl;
	}
    return 0;
}
