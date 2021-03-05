#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <numeric>

using namespace std;

class Hero
{
public:
	int id, hp, damage;
	string name;

	Hero(int _id = 0, string _name = "", int _hp = 0, int _damage = 0)
		: id(_id), name(_name), hp(_hp), damage(_damage)
	{
	}
};

class Player
{
public:
	int id, rank;
	string name;

	Player(int _id = 0, string _name = "", int _rank = 0)
		: id(_id), name(_name), rank(_rank)
	{
	}
};

class PlayerManager
{
public:
	vector<Player> players;

	void CreatePlayer(int _id, string _name, int _rank = 0)
	{
		Player new_player(_id, _name, _rank);
		players.push_back(new_player);
	}
	Player GetPlayerByName(string _name)
	{
		for (auto& elem : players)
		{
			if (_name == elem.name)
				return elem;
		}
		Player empty(0, "Player invalid");
		return empty;
	}
	Player GetPlayerById(int _id)
	{
		for (auto& elem : players)
		{
			if (_id == elem.id)
				return elem;
		}
		Player empty(0, "Player invalid");
		return empty;
	}
	void DeletePlayer(int _id, string _name = "")
	{
		this->players;
		for (int i = 0; i < players.size(); i++)
		{
			if (_id == players[i].id || _name == players[i].name)
			{
				players.erase(players.begin() + i);
				break;
			}
		}
	}
	void ChangeRank(int _id, int rank_change = 0)
	{
		this->players;
		players[_id - 1].rank += rank_change;
	}
	void ShowPlayerInfo(string _name, int _id = 0)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (_name == players[i].name || _id == players[i].id)
			{
				cout << "\nName: " << players[i].name <<
						"\tId: "   << players[i].id <<
						"\tRank: " << players[i].rank << "\n";
				break;
			}
		}
	}
};