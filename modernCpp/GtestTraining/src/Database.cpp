#include <string>
#include <iostream>
#include "Database.hpp"




bool DataBaseConnect::Login(std::string aUserName, std::string aPass)
{
	return true;
}

bool DataBaseConnect::Logout(std::string aUserName)
{
	return true;
}

int DataBaseConnect::FetchRecord()
{
	return -1;
}


int MyDataBase::Init(std::string aUsername, std::string aPass)
{
	if (_dbC.Login(aUsername, aPass) != true)
	{
		std::cout << "DataBase FAILURE" << std::endl;
		return -1;
	} 
	else {
		std::cout << "DataBase SUCCESS" << std::endl;
	}
	return 1;
}
