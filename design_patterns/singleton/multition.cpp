#include <map>
#include <memory>
#include <string>
#include <iostream>


enum class Importance
{
	primary,
	secondary,
	tertiary
};

template <typename T, typename Key = std::string>
class Multition
{
public:
	static std::shared_ptr<T> get(const Key& key)
	{
		const auto it = instances.find(key);

		if (it != instances.end())
		{
			return it->second;
		}


		auto instance = std::make_shared<T>();
		instances[key] = instance;
		return instance;
	}
protected:
	Multition() = default;
	virtual ~Multition() = default;
private:
	static std::map<Key, std::shared_ptr<T>> instances;
};


template <typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multition<T, Key>::instances;

class Printer
{
public:
	Printer()
	{

		++totalInstanceCount;
		std::cout << "A total of " << Printer::totalInstanceCount
				  << " instances are created." << std::endl;

	}
private:
	static int totalInstanceCount;
};

int Printer::totalInstanceCount = 0;


int main()
{
	typedef Multition<Printer, Importance> mt;

	auto main = mt::get(Importance::primary);

	auto second = mt::get(Importance::secondary);
	auto main2 = mt::get(Importance::primary);


	return 0;
}