
#ifndef __DATABASE_HPP_
#define __DATABASE_HPP_

#include <string>
#include <iostream>


class DataBaseConnect
{
public:
	virtual bool Login(std::string aUserName, std::string aPass);

	virtual bool Logout(std::string aUserName);

	virtual int FetchRecord();

};

class MyDataBase
{
	DataBaseConnect & _dbC;
public:
	MyDataBase(DataBaseConnect & aDatabase) : _dbC(aDatabase) {};

	int Init(std::string aUsername, std::string aPass);

	~MyDataBase() = default;
};

#endif //__DATABASE_HPP__