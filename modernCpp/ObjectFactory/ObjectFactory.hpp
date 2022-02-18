#ifndef __OBJECT_FACTORY__
#define __OBJECT_FACTORY__

#include <set>
#include <functional>
#include <vector>
#include <type_traits>
#include <algorithm>

template <
	typename OBJECT,
	typename ID_TYPE 	= unsigned int,
	// typename ID_LIST 	= std::set<unsigned int>,
	typename MAKE_FUNC 		= std::function<typename std::remove_pointer<OBJECT>::type *()>,
	typename DELETE_FUNC 	= std::function<void ()>
	>
class ObjectFactory
{
	using Object_t = std::remove_pointer<OBJECT>::type;
public:
	class MakeDel
	{
	public:
		MAKE_FUNC 	_make_func;
		DELETE_FUNC _delete_func;
		MakeDel(MAKE_FUNC aMakeFunc, DELETE_FUNC aDelFunc) 
				: _make_func(aMakeFunc)
				, _delete_func(aDelFunc)
				{}
	};


	bool Register(ID_TYPE aIdType, MAKE_FUNC aMakeFunc, DELETE_FUNC aDelFunc)
	{
		MakeDel lMakeDelPair(aMakeFunc, aDelFunc);
		_factory_map.insert(std::pair(aIdType, lMakeDelPair));
		return true;
	}

	Object_t* CreateObject(ID_TYPE aIdType)
	{
		auto it = _factory_map.find(aIdType);
		if (it != _factory_map.end())
		{
			return it->second()._make_func();
		}
		return nullptr;
	}

	void DeleteObject(ID_TYPE aIdType)
	{
		auto it = _factory_map.find(aIdType);
		if (it != _factory_map.end())
		{
			it->second()._delete_func();
		}
	}

private:
	std::map<ID_TYPE, MakeDel> _factory_map;

};


#endif // __OBJECT_FACTORY__