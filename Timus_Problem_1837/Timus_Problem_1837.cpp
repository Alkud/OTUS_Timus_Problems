#include <iostream>
#include <string>
#include <unordered_set>
#include <list>
#include <map>
#include <algorithm>

using teamSet = std::unordered_set<std::string>;

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
		std::getline(std::cin, inputString);
		teams.push_back(splitTeamString(inputString));
		if (mentionIsenbaev != true &&
			inputString.find(Isenbaev) != std::string::npos)
		{
			mentionIsenbaev = true;
		}
	}
	std::map<int, std::unordered_set<std::string>> distances{};
	std::map<std::string, int> participants{};
	if (mentionIsenbaev)
	{
		participants[Isenbaev] = 0;
		distances[0].insert(Isenbaev);
	}
	int currentDistance{ 0 };
	while (teams.empty() != true)
	{		
		for (auto team{ teams.begin() }; team != teams.end();)
		{
			if (std::find_first_of(	team->begin(), team->end(),
									distances[currentDistance].begin(), distances[currentDistance].end())
				!= team->end())
			{				
				for (const auto& member : *team)
				{
					if (distances[currentDistance].find(member) == distances[currentDistance].end())
					{
						distances[currentDistance + 1].insert(member);
					}
				}
				auto tmp{ team };
				std::advance(team, 1);
				teams.erase(tmp);
			}
			else
			{
				++team;
			}			
		}		
		++currentDistance;
		if (distances[currentDistance].empty() == true)
		{
			distances.erase(currentDistance);
			break;
		}
	}
	for (const auto& team : teams)
	{
		for (const auto& member : team)
		{
			distances[-1].insert(member);
		}
	}
	for (const auto& distance : distances)
	{
		for (const auto& member : distance.second)
		{
			participants[member] = distance.first;
		}
	}
	for (const auto& participant : participants)
	{
		std::cout << participant.first << " " <<
			(participant.second > -1 ? std::to_string(participant.second) : "undefined") <<
			std::endl;
	}
    return 0;
}

