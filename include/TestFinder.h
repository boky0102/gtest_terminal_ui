#pragma once

#include "ITestFinder.h"

class TestFinder : public ITestFinder
{
   public:
    TestFinder(std::string rootPath);
    ~TestFinder() = default;

    std::vector<TestInfo> GetTestNames(std::string searchStr) override;

    // TODO: Find a better way to handle path data
   private:
    // TODO: Implement method for Getting test data from the root folder
    void GatherTestData();

    std::vector<TestInfo> m_foundTestData;
    std::string m_rootPath;
};
