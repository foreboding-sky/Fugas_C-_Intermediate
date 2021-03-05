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