#include "gtest/gtest.h"
#include "Logger.h"

TEST(MainTest, Test1){
	EXPECT_EQ(1, 1);
}

TEST(MainTest, GetLogger)
{
	auto log = UTIL::Log();

	log << std::string("bla");
}
