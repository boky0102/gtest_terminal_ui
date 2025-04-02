#include "gtest/gtest.h"
#include "TestFinder.h"

TEST(MainTest, Test1){
	TestFinder();
	EXPECT_EQ(1, 1);
}
