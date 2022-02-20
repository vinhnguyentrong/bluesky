#include <iostream>
#include <gtest/gtest.h>
// #include <gmock/gmock.h>


using namespace std;

class MyClass
{
	int baseValue;
public:
	MyClass(int aBaseVal) : baseValue(aBaseVal) {}
	void Increment(int byVal)
	{
		baseValue += byVal;
	}

	int GetValue() {return baseValue;}

};


// Test fixture

struct MyClassTest : public testing::Test
{
	MyClass *mc;
	void SetUp() {
		mc = new MyClass(100);
	}


	void TearDown() { delete mc;}

};


TEST_F(MyClassTest, Increment_5) 
{
	// Arrange
	// MyClass mc(100);

	// Act
	mc->Increment(5);

	// Assert
	ASSERT_EQ(mc->GetValue(), 105);

}

TEST_F(MyClassTest, Increment_10)
{
	mc->Increment(10);
	ASSERT_EQ(mc->GetValue(), 110);
}




int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);


	return RUN_ALL_TESTS();
}