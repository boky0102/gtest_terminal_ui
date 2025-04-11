#include "Logger.h"
#include "gtest/gtest.h"
#include "TestFinder.h"
#include <memory.h>
#include <filesystem>
#include <iterator>
#include <memory>
#include <ranges>

class TestFinderSuite : public testing::Test
{
protected:
    void TestSetup(){
        auto currentPath = std::filesystem::current_path();
        m_testFinder = std::make_unique<TestFinder>(currentPath);

    }

    std::unique_ptr<TestFinder> m_testFinder;
};

// INFO: This tests use fake folder with gtest executables
//          Folder consits of the following executables:
//              TestFake1
//                  FakeSuite1
//                      FakeTest1 
//              TestFake2
//                  FakeSuite2
//                      FakeTest2
//                      FakeTest3
//              TestFake3
//                  FakeSuite3
//                      FakeTest5
//                  FakeSuite4
//                      FakeTest6
//                  FakeSuite4
//                      FakeTest7
//              

TEST_F(TestFinderSuite, TestFinderIsFindingAllExecutablesInFakeFolder){
    TestSetup();
    auto finderResults = m_testFinder->GetTestFiles();
 
    UTIL::Log(finderResults);

    auto filtered = std::views::filter(finderResults, [](TestExe currentTestExe){
       return currentTestExe.name == "TestFake1"; 
    });

    auto size = std::ranges::distance(filtered.begin(), filtered.end());

    EXPECT_EQ(size, 1);
}
