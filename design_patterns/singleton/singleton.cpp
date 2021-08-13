#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>

class Database
{
public:
	virtual long get_population(const std::string& city) = 0;
};


class SingletonDatabase : public Database
{

	SingletonDatabase() {
		std::ifstream ifs("capitals.txt");

		std::string s, s2;
		long pop;
		std::stringstream ss;

		while (getline(ifs, s))
		{
			getline(ifs, s2);
			ss << s2;
			ss >> pop;
			capitals[s] = pop;
		}
	}

	std::map<std::string, long> capitals;

public:

	SingletonDatabase(SingletonDatabase const&) = delete;
	void operator=(SingletonDatabase const&) = delete;

	static SingletonDatabase& get()
	{
		static SingletonDatabase db;
		return db;
	}

	long get_population(const std::string& city)
	{
		return capitals[city];
	}
};

/*
* Problem with the singleton:
* When test for the SingletonRecordFinder the real data (production data)
* is changeable or unpredictable.
* 
* Suggestion:
* Use singleton in dependence injection.
* 	- Define a DataBase base class
*	- The production database inherit from the base class
*	- When test: create a dumyDatabase also inherit from the base class
* 
*/

class DumyDatabase : public Database
{

	std::map<std::string, long> capitals;

public:

	DumyDatabase()
	{
		capitals["a"] = 1000;
		capitals["b"] = 2000;
		capitals["c"] = 3000;
	}

};
///////////////////////////////////////////////////////////////////////////
// notes: the way to use ConfigurableRecordFinder and SingletonRecordFinder
struct ConfigurableRecordFinder
{
	Database& db;
	ConfigurableRecordFinder(Database& db) : db(db) {}
	long total_population(std::vector<std::string> cities)
	{
		long result{0};
		for (auto& name : cities)
			result += db.get_population(name);
		return result;
	}
};

struct SingletonRecordFinder
{
	long total_population(std::vector<std::string> names)
	{
		long result{0};
		for (auto&  name : names)
			result += SingletonDatabase::get().get_population(name);
		return result;
	}
};
///////////////////////////////////////////////////////////////////////
int main()
{
	std::string city = "Hanoi";
	std::vector<std::string> cities{"Hanoi", "Newyork"};

	std::cout << "The population of " << city
			  << " is " << SingletonDatabase::get().get_population(city)
			  << std::endl;

	SingletonRecordFinder Record;
	std::cout << "The population of Hanoi and NewYork: "
			  << Record.total_population(cities)
			  << std::endl;
}