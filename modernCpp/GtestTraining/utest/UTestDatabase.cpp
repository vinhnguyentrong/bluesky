#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MockDatabaseConnect.hpp"
#include <Database.hpp>

using ::testing::AtLeast;
using ::testing::Return;
// using ::testing::_;


TEST(MyDatabaseTest, LoginTest)
{
	// Arrange
	MockDatabaseConnect lDBConnect;
	MyDataBase lDB(lDBConnect);

	// Set behavior
	EXPECT_CALL(lDBConnect, Login("Terminator", "I'm back"))
	.Times(1)
	.WillOnce(Return(true));

	// Act
	int retVal = lDB.Init("Terminator", "I'm back");

	// Assert
	EXPECT_EQ(retVal, 1);
}




int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);


	return RUN_ALL_TESTS();
}