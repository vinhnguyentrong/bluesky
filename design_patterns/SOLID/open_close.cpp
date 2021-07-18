#include <iostream>
#include <vector>


enum class Color
{
	RED,
	GREEN,
	BLUE
};

enum class Size
{
	SMALL,
	MEDIUM,
	LARGE
};

struct Product
{
	std::string name;
	Color color;
	Size size;
};

struct ProductFilter
{
	std::vector<Product*> ByColor(std::vector<Product*> Items, Color color)
	{
		std::vector<Product*> result;
		for (auto& i : Items)
			if (i->color == color)
				result.push_back(i);
		return result;
	}
	std::vector<Product*> BySize(std::vector<Product*> Items, Size aSize)
	{
		std::vector<Product*> result;
		for (auto& i : Items)
			if (i->size == aSize)
				result.push_back(i);
		return result;
	}
	std::vector<Product*> BySizeColor(std::vector<Product*> Items,
									  Size aSize,
									  Color aColor)
	{
		std::vector<Product*> result;
		for (auto& i : Items)
			if (i->size == aSize && i->color == aColor)
				result.push_back(i);
		return result;
	}
};


/* new aproach */

template <typename T> struct Specification;
template <typename T> struct AndSpecification;

template <typename T> struct Specification {
	virtual bool is_satisfied(T* item) = 0;

	AndSpecification<T> operator&&(Specification<T>&& other) {
		return AndSpecification<T>(*this, other);
	}
};
template <typename T> struct AndSpecification : Specification<T>
{
	Specification<T>& first;
	Specification<T>& second;
	AndSpecification(Specification<T>& aFirst, Specification<T>& aSecond)
			: first(aFirst), second(aSecond) {};
	bool is_satisfied(T* item) override {
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

template <typename T> struct Filter {
	virtual std::vector<T*> filter(std::vector<T*> items,
								   Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
	std::vector<Product*> filter(std::vector<Product*> items,
								 Specification<Product> &spec) override
	{
		bool meet_spec = true;
		std::vector<Product*> result;
		for (auto& item : items)
		{
			if (spec.is_satisfied(item))
				result.push_back(item);
		}
		return result;
	}
};

struct SizeSpecification : Specification<Product>
{
	Size mSize;
	explicit SizeSpecification(const Size aSize) : mSize(aSize) {}
	bool is_satisfied(Product* item) override {
		return item->size == mSize;
	}
};

struct ColorSpecification : Specification<Product>
{
	Color color;
	ColorSpecification(Color aColor) : color(aColor) {}
	bool is_satisfied(Product* item) override {
		return item->color == color;
	}
};



int main()
{
	Product apple{"Apple", Color::GREEN, Size::SMALL};
	Product tree{"Tree", Color::GREEN, Size::LARGE};
	Product house{"House", Color::BLUE, Size::LARGE};

	std::vector<Product*> items {&apple, &tree, &house};
	ProductFilter pf;
	auto green_things = pf.ByColor(items, Color::GREEN);
	auto large_things = pf.BySize(items, Size::LARGE);
	auto large_and_green_things =
			pf.BySizeColor(items, Size::LARGE, Color::GREEN);

	for (auto item : green_things)
		std::cout << item->name << " is Green!" << std::endl;
	for (auto item : large_things)
		std::cout << item->name << " is large!" << std::endl;
	for (auto item : large_and_green_things)
		std::cout << item->name << " is large and green!" << std::endl;


	std::cout << "=============Better Filter=============" << std::endl;

	BetterFilter bf;
	ColorSpecification green{Color::GREEN};
	SizeSpecification large{Size::LARGE};

	for (auto& item : bf.filter(items, green))
		std::cout << item->name << " is green" << std::endl;

	for (auto& item : bf.filter(items, large))
		std::cout << item->name << " is large" << std::endl;

	// AndSpecification<Product> large_and_green(large, green);
	auto spec = ColorSpecification(Color::GREEN) &&
				SizeSpecification(Size::LARGE);

	for (auto& item : bf.filter(items, spec))
		std::cout << item->name << " is large and green" << std::endl;


	return 0;
}