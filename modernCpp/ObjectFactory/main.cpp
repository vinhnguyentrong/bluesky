
#include <iostream>

#include "ObjectFactory.hpp"
#include "Singleton.hpp"


class Base 
{

};

class Child : public Base
{

};

using BaseConstructor = std::function<Base * ()>;

using FactoryBase =
			Singleton< ObjectFactory< Base, unsigned int, BaseConstructor, BaseDestructor> >;


