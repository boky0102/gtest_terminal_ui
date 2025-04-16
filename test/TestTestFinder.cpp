#include "gtest/gtest.h"
#include "TestFinder.h"
#include <memory.h>
#include <algorithm>
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

    EXPECT_EQ(finderResults.size(), 3);

    auto filtered = std::views::filter(finderResults, [](TestExe currentTestExe){
       return currentTestExe.name == "TestFake1" || currentTestExe.name == "TestFake2" || currentTestExe.name == "TestFake3"; 
    });

    auto size = std::ranges::distance(filtered.begin(), filtered.end());

    // all exes are here
    EXPECT_EQ(size, 3);
}

TEST_F(TestFinderSuite, TestFinderIsGettingProperAbsolutePath){
   TestSetup();
    auto finderResults = m_testFinder->GetTestFiles();

    std::ranges::for_each(finderResults, [](TestExe currentTestExe){
        EXPECT_TRUE(currentTestExe.path.is_absolute());
    });
}

TEST_F(TestFinderSuite, TestFinderIsFindingAllTests){
    TestSetup();

    auto finderResults = m_testFinder->GetTestFiles();
    ASSERT_EQ(finderResults.size(), 3);

    std::ranges::sort(finderResults, [](TestExe& exe_a, TestExe& exe_b){
        int lastCharA = *exe_a.name.end().base();
        int lastCharB = *exe_b.name.end().base();
        return lastCharA < lastCharB;
    });

    for(const auto& elem: finderResults){
        std::cout << elem.name << " -------- "<< std::endl;
        for (const auto& test: elem.tests){
            std::cout << test.name << " .. " << test.group << std::endl;
        }
    }

    /*// INFO: this is a TestFake1 since they are sorted*/
    EXPECT_EQ(finderResults[0].name, "TestFake1");
    EXPECT_EQ(finderResults[0].tests[0].group, "FakeSuite1");
    EXPECT_EQ(finderResults[0].tests[0].name, "FakeTest1");
}


