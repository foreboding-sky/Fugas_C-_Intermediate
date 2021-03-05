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

class HeroManager
{
public:
	vector<Hero> heroes;

	void CreateHero(int _id, string _name, int _hp = 0, int _damage = 0)
	{
		Hero new_hero(_id, _name, _hp, _damage);
		heroes.push_back(new_hero);
	}
	Hero GetHeroByName(string _name)
	{
		for (auto& elem : heroes)
		{
			if (_name == elem.name)
				return elem;
		}
		Hero empty(0, "Hero invalid");
		return empty;
	}
	Hero GetHeroById(int _id)
	{
		for (auto& elem : heroes)
		{
			if (_id == elem.id)
				return elem;
		}
		Hero empty(0, "Hero invalid");
		return empty;
	}
	void DeleteHero(int _id, string _name = "")
	{
		this->heroes;
		for (int i = 0; i < heroes.size(); i++)
		{
			if (_name == heroes[i].name || _id == heroes[i].id)
			{
				heroes.erase(heroes.begin() + i);
				break;
			}
		}
	}
	void ShowHeroInfo(string _name, int _id = 0)
	{
		for (int i = 0; i < heroes.size(); i++)
		{
			if (_name == heroes[i].name || _id == heroes[i].id)
			{
				cout << "\nName: "   << heroes[i].name <<
						"\tId: "     << heroes[i].id <<
						"\tHP: "     << heroes[i].hp <<
						"\tDamage: " << heroes[i].damage << "\n";
				break;
			}
		}
	}
};

class Team
{
public:
	struct PlayerHero
	{
		Player player;
		Hero hero;
		PlayerHero() : player(), hero()
		{
		}
	};

	string name;
	vector<PlayerHero> players;
};

class TeamManager
{
public:
	vector<Team> teams;

	void GenerateNewTeam(vector<Player> player, vector<Hero> hero, string _name = "")
	{
		this->teams;
		teams.resize(teams.size() + 1);
		for (int i = 0; i < 5; i++)
		{
			teams[teams.size() - 1].players.resize(i + 1);
			teams[teams.size() - 1].players[i].player = player[i];
			teams[teams.size() - 1].players[i].hero = hero[i];
		}
		teams[teams.size() - 1].name = _name;
	}
	void GetTeamInfo(PlayerManager pl_manager, HeroManager hero_manager)
	{
		for (const auto& elem : teams)
		{
			cout << elem.name << "\n";
			for (int i = 0; i < 5; i++)
			{
				cout << "Player " << i + 1 << ": ";
				pl_manager.ShowPlayerInfo(elem.players[i].player.name);
				cout << "Hero: ";
				hero_manager.ShowHeroInfo(elem.players[i].hero.name);
			}
			cout << "\n";
		}
	}
	void ClearTeams()
	{
		teams.clear();
	}
};

class Session
{
public:
	char start_time[26] = {};
	Team team_one;
	Team team_two;
	Team winner;

	Session(Team _team_one, Team _team_two)
		: team_one(_team_one), team_two(_team_two)
	{
		auto start = chrono::system_clock::now();
		time_t time = chrono::system_clock::to_time_t(start);
		ctime_s(start_time, 26, &time);
		winner = CalculateWinner(_team_one, _team_two);
	}
	Team CalculateWinner(Team _team_one, Team _team_two)
	{
		int team_one_damage = 0, team_two_damage = 0;
		int team_one_health = 0, team_two_health = 0;
		for (int i = 0; i < _team_one.players.size(); i++)
		{
			team_one_damage = _team_one.players[i].hero.damage;
			team_one_health = _team_one.players[i].hero.hp;
		}
		for (int i = 0; i < _team_two.players.size(); i++)
		{
			team_two_damage = _team_two.players[i].hero.damage;
			team_two_health = _team_two.players[i].hero.hp;
		}
		if (team_one_health - team_two_damage < team_two_health - team_one_damage)
			return _team_two;
		return _team_one;
	}
	void ShowSession()
	{
		cout << "Winner: " << winner.name << "\n";
		for (auto& elem : winner.players)
			cout << elem.player.name << "\n";
		cout << start_time;
	}
};

class GameManager
{
	vector<Session> GameSessions;
	PlayerManager pl_manager;
	HeroManager hero_manager;
	TeamManager team_manager;
public:
	GameManager(PlayerManager _pl_manager, HeroManager _hero_manager)
		: pl_manager(_pl_manager), hero_manager(_hero_manager)
	{
	}

	void PerformGameSession(PlayerManager& pl_manager)
	{
		vector<Player> random_players;
		vector<Hero> random_heroes;

		int p_it;
		int rnd_player_it;
		vector<int> players_buffer(pl_manager.players.size());
		iota(players_buffer.begin(), players_buffer.end(), 0);

		int h_it;
		int rnd_hero_it;
		vector<int> heroes_buffer(hero_manager.heroes.size());
		iota(heroes_buffer.begin(), heroes_buffer.end(), 0);

		team_manager.ClearTeams();

		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 5; i++)
			{
				p_it = rand() % players_buffer.size();
				rnd_player_it = players_buffer[p_it];
				players_buffer.erase(players_buffer.begin() + p_it);
				random_players.push_back(pl_manager.players[rnd_player_it]);

				h_it = rand() % heroes_buffer.size();
				rnd_hero_it = heroes_buffer[h_it];
				heroes_buffer.erase(heroes_buffer.begin() + h_it);
				random_heroes.push_back(hero_manager.heroes[rnd_hero_it]);
			}
			team_manager.GenerateNewTeam(random_players, random_heroes, "Team " + to_string(j + 1));
			random_players.clear();
			random_heroes.clear();
		}

		for (int j = 0; j < team_manager.teams.size() - 1; j++)
		{
			Session temp(team_manager.teams[j], team_manager.teams[j + 1]);

			for (int i = 0; i < temp.team_one.players.size(); i++)
			{
				pl_manager.ChangeRank(temp.team_one.players[i].player.id, -25);
				pl_manager.ChangeRank(temp.team_two.players[i].player.id, -25);
				pl_manager.ChangeRank(temp.winner.players[i].player.id, 50);
				temp.winner.players[i].player.rank += 25;
			}
			GameSessions.push_back(temp);
		}
	}
	void ShowSessions(PlayerManager pl_manager)
	{
		for (int i = 0; i < GameSessions.size(); i++)
		{
			cout << "Session " << i + 1 << "\n\n";
			team_manager.GetTeamInfo(pl_manager, hero_manager);
			GameSessions[i].ShowSession();
			cout << "\n";
		}
	}
};

void InitializeUnits(PlayerManager& players, HeroManager& heroes)
{
	vector<string> player_names = { "Demka", "Demonoid", "Dumka", "Andrain", "Androker", "Antoniu", "Antroll", "Dimkrat", "Gleboomer", "Glibov", "Domestos", "Deamon", "Andrel"};
	vector<string> hero_names = { "Pudge", "Hasagi", "Seledka", "Riven", "Stylish", "Sniper", "Kapinos", "Bariga", "Groshi", "Invokler", "Genji", "Abatur", "Ezreal", "Nikita"};
	int random;
	string temp_name;
	for (int i = 0; i < 10; i++)
	{
		random = rand() % player_names.size();
		temp_name = player_names[random];
		player_names.erase(player_names.begin() + random);

		players.CreatePlayer(i + 1, temp_name, 0);
	}
	for (int i = 0; i < 10; i++)
	{
		random = rand() % hero_names.size();
		temp_name = hero_names[random];
		hero_names.erase(hero_names.begin() + random);

		heroes.CreateHero(i + 1, temp_name, rand() % 60 + 10, rand() % 60 + 10);
	}
}

int main()
{
	srand(time(NULL));

	PlayerManager pl_manager;
	HeroManager hero_manager;

	InitializeUnits(pl_manager, hero_manager);

	GameManager game_manager(pl_manager, hero_manager);

	for (int i = 0; i < 5; i++)
		game_manager.PerformGameSession(pl_manager;);

	game_manager.ShowSessions(pl_manager;);
	return 0;
}