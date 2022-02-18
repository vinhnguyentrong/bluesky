#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <thread>

/******************************************************************************/
/* auto keyword
 *
 ******************************************************************************/
class foo
{
  int x;
public:

  foo(int const a = 0) : x{a} {}
  void set(int const a) { x = a;}
  const int& get() {return x;}
  void printfoo() {std::cout << "x = " << x << std::endl;}
};

auto proxy_get_auto(foo& f) {return f.get();}
decltype(auto) proxy_get(foo& f) {return f.get();}

// int& proxy_get(foo& f) {return f.get();}

const int& proxy_get_ref(foo& f) {return f.get();}

// C++11
auto func1 (int const i) -> int {return 2*i;}

// C++14
auto func2 (int const i) {return 2*i;}

// user-literals defined operator ""_s C++14
// std::string operator ""_s(const char* args, std::size_t) {return args;};
struct
{
  template<typename T, typename U>
  auto operator () (T const a, U const b) const {return a+b;}
} L;


int auto_main()
{

  auto f = foo{42};
  // cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
  const auto& x = proxy_get_auto(f); 

  std::cout << "x = " << x << std::endl;

  // decltype(auto) x = proxy_get(f);

  const int& a = proxy_get(f);
  std::cout << a << std::endl;

  f.set(10);

  std::cout << a << std::endl;


  // auto for lambda C++14
  auto ladd = [] (auto const a, auto const b) {return a+b;};

  auto i = ladd(20, 40);
  std::cout << "auto lambda i = " << i << std::endl;
  using namespace std::string_literals;
  auto s = ladd("Hello "s,
                "world\0 not end literals\n"s);
  std::string str1 = "Hello world\0 end string";
  std::cout << "str1: " << str1 << ", size: " << str1.size() << std::endl;

  std::string str2 = "Hello world\0 end string"s;
  std::cout << "str2: " << str2 << ", size: " << str2.size() << std::endl;

  std::cout << "auto literals add: " << s << std::endl;


  return 0;
}

/******************************************************************************/
/* Creating type aliases and alias templates
 *
 ******************************************************************************/
// template <typename T>
// class CustomAlocator {};

// template <typename T>
// using vec_t = std::vector<T, CustomAlocator<T>>;


/******************************************************************************/
/* using unamed namespace instead of static globals
 * Don't use static for class or struct.
 *
 ******************************************************************************/

namespace
{
  int a = 10;
  int b = 20;
  void unnamed_namespace_add(int x, int y) {
    std::cout << "total = " << x + y << std::endl;
  }

  void unnamed_namespace_add(std::initializer_list<int> const alist)
  {
    int sum = 0;
    for (auto const &e : alist)
    {
      sum += e;
    }
    std::cout << "sum list = " << sum << std::endl;
  }
}
/* what compiler do?
namespace __unique_compiler_generated_identifer0x42 {
  ...
}
using namespace __unique_compiler_generated_identifer0x42;
*/
int unnamed_namespace_main()
{
  unnamed_namespace_add(a, b);

  unnamed_namespace_add({1, 2, 3, 4, 5, 6, 7, 8, 9});
  return 0;
}


/******************************************************************************/
/* Using override and final for virtual methods
 * 
 *
 ******************************************************************************/

class AnimalBase
{
  virtual void sound() {};
  virtual void get_name() {};
};

class Animal
{
public:
  virtual void sound() = 0;
  virtual void get_name() = 0;
};

class Dog : public Animal
{
public:
  virtual void sound() override
  {
    std::cout << "Gau Gau" << std::endl;
  }
  virtual void get_name() override
  {
    std::cout << "This is a dog" << std::endl;
  }
};

class Shiba final : public Dog
{
public:
  virtual void get_name() override
  {
    std::cout << "This is a Shiba dog" << std::endl;
  }

};

class Cat final : public Animal
{
public:
  virtual void sound() final
  {
    std::cout << "Meo meo" << std::endl;
  }
  virtual void get_name() override
  {
    std::cout << "This is a cat" << std::endl;
  }
};

int override_main()
{

  Dog adog;
  adog.get_name();
  adog.sound();

  Shiba aShiba;
  aShiba.get_name();
  aShiba.sound();

  Cat aCat;
  aCat.get_name();
  aCat.sound();
  return 0;
}


/******************************************************************************/
/* 1.8 Using a range-based for loops to iterate on a range
 * 
 *
 ******************************************************************************/
std::vector<int> getRates() 
{
  return std::vector<int> {1, 1, 2, 3, 5, 8, 13};
}
std::multimap<int , bool> getRates2()
{
  return std::multimap<int, bool> {
    {1, true},
    {1, true},
    {2, false},
    {3, true},
    {5, true},
    {8, false},
    {13, true}
  };
}

int main_18()
{

  auto rates = getRates();
  for (auto rate : rates)
  {
    std::cout << rate << std::endl;
    rate *= 2;
  }
  for (auto& rate : rates)
  {
    std::cout << rate << std::endl;
    rate *= 2;
  }
  for (auto rate : rates)
  {
    std::cout << rate << std::endl;
  }

  // C++17
  for (auto&& [rate, flag] : getRates2())
  {
    if (flag)
      std::cout << rate << std::endl;
  }
  return 0;
}


/******************************************************************************/
/* 1.9 Enabling range-based for loops for custom types
 *
 ******************************************************************************/

// Implementation of a simple array
template <typename T, size_t const Size>
class dummy_array
{
  T data[Size] = {};
public:
  T const & GetAt(size_t const index) const
  {
    if (index < Size) return data[index];
    throw std::out_of_range("Index out of range");
  }

  void SetAt(size_t const index, T const & value)
  {
    if (index < Size) data[index] = value;
    else throw std::out_of_range("Index out of range");
  }

  size_t GetSize() const { return Size;}
};


// Defined iterator class template
template <typename T, typename C, size_t const Size>
class dummy_array_iterator_type
{
public:
  dummy_array_iterator_type(C& acollection, size_t const aindex)
  : index(aindex), collection(acollection)
  {}

  bool operator!= (dummy_array_iterator_type const & other) const
  {
    return index != other.index;
  }

  T const & operator* () const
  {
    return collection.GetAt(index);
  }

  dummy_array_iterator_type const & operator++()
  {
    ++index;
    return *this;
  }

private:
  size_t index;
  C& collection;

};

// two alias templates
// alias templates for mutable and constant iterators:
template <typename T, size_t const Size>
using dummy_array_iterator =
    dummy_array_iterator_type<T, dummy_array<T, Size>, Size>;

template <typename T, size_t const Size>
using dummy_array_const_iterator =
    dummy_array_iterator_type<T, dummy_array<T, Size>, Size>;


// begin() and end() functions
template <typename T, size_t const Size>
inline dummy_array_iterator<T, Size> begin(dummy_array<T, Size>& collection)
{
  return dummy_array_iterator<T, Size>(collection, 0);
}

template <typename T, size_t const Size>
inline dummy_array_iterator<T, Size> end(dummy_array<T, Size>& collection)
{
  return dummy_array_iterator<T, Size> (collection, collection.GetSize());
}

template <typename T, size_t const Size>
inline dummy_array_const_iterator<T, Size> begin(dummy_array<T, Size> const & collection)
{
  return dummy_array_const_iterator<T, Size>(collection, 0);
}

template <typename T, size_t const Size>
inline dummy_array_const_iterator<T, Size> end(dummy_array<T, Size> const & collection)
{
  return dummy_array_const_iterator<T, Size>(collection, collection.GetSize());
}

int main_19()
{
  dummy_array<int , 3> arr;
  arr.SetAt(0, 1);
  arr.SetAt(1, 2);
  arr.SetAt(2, 3);
  // arr.SetAt(3, 4);

  // for (auto e = arr.begin(), e != arr.end(), ++e)
  // {
  //   std::cout << e << << std::endl;
  // }
  for (auto&& e : arr)
  {
    std::cout << e << std::endl;
  }


  return 0;
}


/******************************************************************************/
/* 1.10 Using explicit constructors and conversion operators to avoid implicit
 * conversion
 ******************************************************************************/


/******************************************************************************/
/* 1.11 Using inline namespaces for symbol versioning
 *
 ******************************************************************************/

namespace modernlib
{
  #ifndef LIB_VERSION_2
  inline namespace version_1
  {
    template<typename T>
    int test(T value) {return 1;}
  }
  #endif

  #ifdef LIB_VERSION_2
  inline namespace version_2
  {
    template<typename T>
    int test(T value) {return 2;}
  }
  #endif
}


// client use
// The test function will be included to modernlib and override
struct foo111 {int a = 10;};
namespace modernlib
{
  template<>
  int test(foo111 value) {return value.a;}

}


int main_111()
{

  auto x = modernlib::test(42);
  std::cout << "x = " << x << std::endl;
  auto y = modernlib::test(foo111{42});
  std::cout << "y = " << y << std::endl;
  return 0;
}


/******************************************************************************/
/* main function
 *
 ******************************************************************************/
// template <typename T>
// void print_map(T & m)
// {
//   std::cout << "=================" std::endl;
//   for(auto& e : m)
//   {

//   }
// }
// template <typename Key, typename Value>
// using usermap = std::map<Key, Value>;

// template <>
// void print_map(usermap &m)
// {
//   std::cout << "print map:" << std::endl;
//   for (auto& e : m)
//   {
//     std::cout << "first: " << e.first << ", second: " << e.second << std::endl;
//   }
// }

int main_112()
{

  std::map<int, std::string> m;
  auto result = m.insert({5, "five"});
  // result = m.insert({2, "two"});
  std::cout << "inserted = " << result.second << std::endl
            << "value = " << result.first->second << std::endl
            << "number = " << result.first->first << std::endl;


  // C++17
  // std::map<int, std::string> m1;
  {
    auto [itr, inserted] = m.insert({3, "three"});
    std::cout << "inserted = " << inserted << std::endl
              << "value = " << itr->second << std::endl
              << "number = " << itr->first << std::endl;


    for(auto& e : m)
    {
      std::cout << "first: " << e.first << std::endl
                << "second: " << e.second << std::endl;
    }
  }
  return 0;
}

/******************************************************************************/
/* 8.1 Working with thread
 *
 ******************************************************************************/
#include <iomanip>
// #include <thread>

inline void print_time()
{
  auto now = std::chrono::system_clock::now();
  auto stime = std::chrono::system_clock::to_time_t(now);
  auto ltime = std::localtime(&stime);

  std::cout << std::put_time(ltime, "%c") << std::endl;
}

void thread1_func()
{
  std::cout << "thread func without params" << std::endl;
}

void thread_func2(int const i, double const d, std::string const s)
{
  std::cout << i << ", " << d << ", " << s << std::endl;
}

// thread pass function that passed params as a ref
void thread_func3(int &i)
{
  i *= 2;
}


void thread_func4()
{
  print_time();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  print_time();
  std::this_thread::sleep_until(std::chrono::system_clock::now() +
                                std::chrono::seconds(2));
  print_time();
}

void thread_func6(std::chrono::seconds timeout)
{
  // auto now = std::chrono::system_clock::now();
  auto dotimeout = std::chrono::system_clock::now() + timeout;
  // auto dotimeout = now + timeout;
  do {
    std::this_thread::yield();
  } while(std::chrono::system_clock::now() < dotimeout);

  std::cout << "do after timeout" << std::endl;
}


int main_81()
{

  std::thread t1(thread1_func);
  std::thread t2([] () {
    std::cout << "thread func without params" << std::endl;
  });

  t1.join();
  t2.join();

  std::thread t3(thread_func2, 40, 12.3, "nguyen trong vinh");

  t3.join();

  int n = 50;

  std::thread t4(thread_func3, std::ref(n));

  std::cout << "n = " << n << std::endl;
  t4.join();

  std::cout << "n = " << n << std::endl;

  std::thread t5(thread_func4);

  t5.join();

  std::thread t6(thread_func6, std::chrono::seconds(2));

  t6.join();


  return 0;
}


/******************************************************************************/
/* 8.2 handling exception from thread function
 *
 ******************************************************************************/


/******************************************************************************/
/* 8.3 Synchronizing access to shared data with mutexs and locks
 *
 ******************************************************************************/
template <auto X, auto Y>
struct IntSum {
  static constexpr auto value = X + Y;
};

#include <mutex>

std::mutex g_mutex;

void thread_mutex()
{
  // using namespace std::chrono_literals;
  {
    std::lock_guard<std::mutex> lock(g_mutex);
    std::cout << "running thread "
              << std::this_thread::get_id() << std::endl;
  }

  std::this_thread::yield();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  {
    std::lock_guard<std::mutex> lock(g_mutex);
    std::cout << "done in thread "
              << std::this_thread::get_id() << std::endl;
  }
}

// #include <vector>
#include <algorithm>
// #include <iostream>

template <typename T>
struct container
{
  std::mutex m_mutex;
  std::vector<T> m_data;
};

class Doge
{
  std::string m_name;

public:
  Doge(std::string const & name): m_name(name) {};

  const std::string& get_name() const {return m_name;};

  friend std::ostream& operator<<(std::ostream& os, Doge const &a)
  {
    os << a.get_name() << std::endl;
    return os;
  }
};

template <typename T>
void move_between(container<T> & c1, container<T> & c2, T const value)
{

  std::lock(c1.m_mutex, c2.m_mutex);
  std::lock_guard<std::mutex> l1(c1.m_mutex, std::adopt_lock);
  std::lock_guard<std::mutex> l2(c2.m_mutex, std::adopt_lock);

  c1.m_data.erase(
        std::remove(c1.m_data.begin(), c1.m_data.end(), value),
        c1.m_data.end());
  c2.m_data.push_back(value);
}

template <typename T>
void printContainer(container<T> &c1)
{
  std::cout << "container print: " << std::endl;
  for(auto &e : c1.m_data)
  {
    std::cout << e << std::endl;
  }
}


int main_83()
{
  static_assert(60 == IntSum<40, 20>::value);
  std::cout << "Sum: " << IntSum<40,20>::value;

  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i)
  {
    threads.emplace_back(thread_mutex);
  }

  for (auto &t : threads)
  {
    t.join();
  }

  container<int> c1;
  c1.m_data.push_back(1);
  c1.m_data.push_back(2);
  c1.m_data.push_back(3);

  container<int> c2;
  c2.m_data.push_back(4);
  c2.m_data.push_back(5);
  c2.m_data.push_back(6);

  std::thread tc1(move_between<int>, std::ref(c1), std::ref(c2), 3);
  std::thread tc2(move_between<int>, std::ref(c2), std::ref(c1), 6);

  tc1.join();
  tc2.join();

  container<Doge> A1;
  // container<Animal> A2;
  Doge floki("floki");
  Doge shib("Shiba");
  A1.m_data.push_back(floki);
  A1.m_data.push_back(shib);
  printContainer(A1);
  printContainer(c1);
  printContainer(c2);
  return 0;
}

/******************************************************************************/
/* main function
 *
 ******************************************************************************/


int main()
{
  return main_83();
  // return main_81();
  // return main_112();
  // return auto_main();
  // return unnamed_namespace_main();
  // return override_main();
  // return main_18();
  // return main_19();
  // return main_111();
}