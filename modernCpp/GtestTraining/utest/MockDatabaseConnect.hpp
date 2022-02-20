
#ifndef __MOCK_DATABASECONNECT__
#define __MOCK_DATABASECONNECT__

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Database.hpp>

class MockDatabaseConnect : public DataBaseConnect
{
public:
	MOCK_METHOD0(FetchRecord, int());
	MOCK_METHOD1(Logout, bool (std::string aUsername));
	MOCK_METHOD2(Login, bool (std::string aUsername, std::string aPass));
};

#endif //__MOCK_DATABASECONNECT__