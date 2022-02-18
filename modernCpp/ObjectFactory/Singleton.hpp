
#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

template <typename F>
class Singleton
{
public:
	static F* GetInstance()
	{
		if (!_instance)
		{
			_instance = new F;
		}
		return _instance;
	}

	virtual ~Singleton() { _instance = 0;}

private:
	static F* _instance;
	Singleton(const Singleton<F>&) = default;
	Singleton& operator=(const Singleton<F>&) = default;
}

// static member initialize in template class
// https://stackoverflow.com/questions/3229883/static-member-initialization-in-a-class-template
template <typename F>
F* Singleton<C>::_instance = 0;

#endif // __SINGLETON_HPP__