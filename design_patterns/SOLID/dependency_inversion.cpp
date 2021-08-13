#include <iostream>
#include <tuple>
#include <string>
#include <vector>

/*
* A. High-level modules should not depend on low-level modules.
*    Both shoud depend on abstractions.
* B. Abstractions should nod depend on details.
*    Details should not depend on abstractions.
*/


enum class Relationship{
  PARRENT,
  CHILD,
  SIBLING
};

std::ostream& operator<<(std::ostream& os, const Relationship aRel)
{
  switch (aRel)
  {
    case Relationship::PARRENT:
      os << "parrent";
      break;
    case Relationship::CHILD:
      os << "child";
      break;
    case Relationship::SIBLING:
      os << "sibling";
      break;
    default:
      std::cout << "Error relationship: " << aRel << std::endl;
  }
  return os;
}

struct Person
{
  std::string name;
};

struct Relationships // low-level
{
  std::vector<std::tuple<Person, Relationship, Person>> mRelations;
  void AddRelationship(const Person& aPerson1,
                       const Relationship rel,
                       const Person& aPerson2)
  {
    switch (rel)
    {
      case Relationship::CHILD: // aPerson1 is a child of aPerson2
      {
        mRelations.push_back({aPerson1, rel, aPerson2});
        mRelations.push_back({aPerson2, Relationship::PARRENT, aPerson1});
      }
        break;
      case Relationship::PARRENT: // aPerson1 is a parrent of aPerson2
      {
        mRelations.push_back({aPerson1, rel, aPerson2});
        mRelations.push_back({aPerson2, Relationship::CHILD, aPerson1});
      }
        break;
      case Relationship::SIBLING: // aPerson1 is a sibling of aPerson2
      {
        mRelations.push_back({aPerson1, rel, aPerson2});
        mRelations.push_back({aPerson2, rel, aPerson1});
      }
        break;
      default:
        std::cout << "Add relationship error: " << rel << std::endl;
    }
  }
};

struct SearchEngine // High-level
{
  void Search(Relationships& aRelationships, Person& aPerson,
           const Relationship& aRel)
  {
    bool match = false;
    auto& relations = aRelationships.mRelations;
    for (auto& entry : relations)
    {
      // std::cout << std::get<0>(entry).name << std::endl;
      // std::cout << std::get<1>(entry) << std::endl;
      if (std::get<0>(entry).name == aPerson.name && 
          std::get<1>(entry) == aRel)
      {
        std::cout << aPerson.name << " is the "
                  << aRel << " of "
                  << std::get<2>(entry).name << std::endl;
        match = true;
      }
    }
    if (!match)
      std::cout << "Don't match any relationships." << std::endl;
  }
};

int main()
{
  Person parrent{"John"};
  Person child1{"Chris"}, child2{"Matt"};

  Relationships relationships;
  relationships.AddRelationship(parrent, Relationship::PARRENT, child1);
  relationships.AddRelationship(parrent, Relationship::PARRENT, child2);
  relationships.AddRelationship(child1, Relationship::SIBLING, child2);

  SearchEngine lSearchEngine;
  lSearchEngine.Search(relationships, parrent, Relationship::PARRENT);
  lSearchEngine.Search(relationships, child1, Relationship::CHILD);
  lSearchEngine.Search(relationships, child1, Relationship::SIBLING);

  return 0;
}