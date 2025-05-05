#include <memory.h>

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <memory>
#include <ranges>

#include "TestFinder.h"
#include "TestRunner.h"
#include "Types.h"
#include "gtest/gtest.h"

class TestFinderSuite : public testing::Test
{
   protected:
    void TestSetup() {
        auto currentPath = std::filesystem::current_path();
        m_testFinder = std::make_unique<TestFinder>(currentPath);
        m_testRunner = std::make_unique<TestRunner>();
    }

    void FindTests() {
        auto foundTests = m_testFinder->GetTestFiles();
        m_foundTests = std::move(foundTests);
        ASSERT_NE(m_foundTests.size(), 0);
    }

    std::unique_ptr<TestFinder> m_testFinder;
    std::unique_ptr<TestRunner> m_testRunner;
    std::vector<TestExe> m_foundTests;
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

TEST_F(TestFinderSuite, TestFinderIsFindingAllExecutablesInFakeFolder) {
    TestSetup();
    auto finderResults = m_testFinder->GetTestFiles();

    EXPECT_EQ(finderResults.size(), 3);

    auto filtered =
        std::views::filter(finderResults, [](TestExe currentTestExe) {
            return currentTestExe.name == "TestFake1" ||
                   currentTestExe.name == "TestFake2" ||
                   currentTestExe.name == "TestFake3";
        });

    auto size = std::ranges::distance(filtered.begin(), filtered.end());

    // all exes are here
    EXPECT_EQ(size, 3);
}

TEST_F(TestFinderSuite, TestFinderIsGettingProperAbsolutePath) {
    TestSetup();
    auto finderResults = m_testFinder->GetTestFiles();

    std::ranges::for_each(finderResults, [](TestExe currentTestExe) {
        EXPECT_TRUE(currentTestExe.path.is_absolute());
    });
}

TEST_F(TestFinderSuite, TestFinderIsFindingAllTests) {
    TestSetup();

    auto finderResults = m_testFinder->GetTestFiles();
    ASSERT_EQ(finderResults.size(), 3);

    std::ranges::sort(finderResults, [](TestExe& exe_a, TestExe& exe_b) {
        int lastCharA = *exe_a.name.end().base();
        int lastCharB = *exe_b.name.end().base();
        return lastCharA < lastCharB;
    });

    /*// INFO: this is a TestFake1 since they are sorted*/
    EXPECT_EQ(finderResults[0].name, "TestFake1");
    EXPECT_EQ(finderResults[0].tests[0].group, "FakeSuite1");
    EXPECT_EQ(finderResults[0].tests[0].name, "FakeTest1");
}

TEST_F(TestFinderSuite, TestConnectionToTestRunner) {
    TestSetup();
    FindTests();

    auto signalRecieved = false;

    m_testRunner->ConnectTestOutputAvailableSignal(
        [&](std::string message) { signalRecieved = true; });

    auto testToRun = m_foundTests[0];
    m_testRunner->RunTest(testToRun, testToRun.tests[0].name);

    EXPECT_TRUE(signalRecieved);
}

TEST_F(TestFinderSuite, TestRunnerRunningGoodTest) {
    TestSetup();
    FindTests();

    std::vector<std::string> recievedOutputLines;
    m_testRunner->ConnectTestOutputAvailableSignal([&](std::string lineRecieved){
        recievedOutputLines.push_back(lineRecieved);
    });

    // get data for simulated FakeTest1
    const auto testExe = m_foundTests[0];
    auto testName = testExe.tests[0].name;

    m_testRunner->RunTest(testExe, testName);
    const auto nRecieved = recievedOutputLines.size();

    EXPECT_TRUE(recievedOutputLines[0].starts_with("Running main() from"));
    EXPECT_TRUE(recievedOutputLines[1].starts_with("Note: Google Test filter = *FakeTest1*"));
    EXPECT_EQ(recievedOutputLines[nRecieved - 1],"[  PASSED  ] 1 test.\n");
}
